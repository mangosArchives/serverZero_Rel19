/*
 * Copyright (C) 2005-2011 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "Common.h"
#include "WardenDaemon.h"

#include "Config/Config.h"
#include "Log.h"
#include "WardenSocket.h"
#include "SystemConfig.h"
#include "revision.h"
#include "revision_nr.h"
#include "Util.h"

#include <ace/Get_Opt.h>
#include <ace/Dev_Poll_Reactor.h>
#include <ace/TP_Reactor.h>
#include <ace/ACE.h>
#include <ace/Acceptor.h>
#include <ace/SOCK_Acceptor.h>

#include "ServiceWin32.h"
char serviceName[] = "wardend";
char serviceLongName[] = "MaNGOS wardend service";
char serviceDescription[] = "Massive Network Game Object Server";
/*
 * -1 - not in service mode
 *  0 - stopped
 *  1 - running
 *  2 - paused
 */
int m_ServiceStatus = -1;

void UnhookSignals();
void HookSignals();

bool stopEvent = false;                                     ///< Setting it to true stops the daemon

/// Print out the usage string for this program on the console.
void usage(const char *prog)
{
    sLog.outString("Usage: \n %s [<options>]\n"
        "    -v, --version            print version and exist\n\r"
        "    -c config_file           use config_file as configuration file\n\r"
        "    Running as service functions:\n\r"
        "    -s run                   run as service\n\r"
        "    -s install               install service\n\r"
        "    -s uninstall             uninstall service\n\r"
        ,prog);
}

/// Launch the warden server
extern int main(int argc, char **argv)
{
    ///- Command line parsing to get the configuration file name
    char const* cfg_file = _WARDEND_CONFIG;

    char const *options = ":c:s:";

    ACE_Get_Opt cmd_opts(argc, argv, options);
    cmd_opts.long_option("version", 'v');

    int option;
    while ((option = cmd_opts()) != EOF)
    {
        switch (option)
        {
            case 'c':
                cfg_file = cmd_opts.opt_arg();
                break;
            case 'v':
                printf("%s\n", _FULLVERSION(REVISION_DATE,REVISION_TIME,REVISION_NR,REVISION_ID));
                return 0;
            case 's':
            {
                const char *mode = cmd_opts.opt_arg();

                if (!strcmp(mode, "install"))
                {
                    if (WinServiceInstall())
                        sLog.outString("Installing service");
                    return 1;
                }
                else if (!strcmp(mode, "uninstall"))
                {
                    if (WinServiceUninstall())
                        sLog.outString("Uninstalling service");
                    return 1;
                }
                else if (!strcmp(mode, "run"))
                    WinServiceRun();
                else
                {
                    sLog.outError("Runtime-Error: -%c unsupported argument %s", cmd_opts.opt_opt(), mode);
                    usage(argv[0]);
                    Log::WaitBeforeContinueIfNeed();
                    return 1;
                }
                break;
            }
            case ':':
                sLog.outError("Runtime-Error: -%c option requires an input argument", cmd_opts.opt_opt());
                usage(argv[0]);
                Log::WaitBeforeContinueIfNeed();
                return 1;
            default:
                sLog.outError("Runtime-Error: bad format of commandline arguments");
                usage(argv[0]);
                Log::WaitBeforeContinueIfNeed();
                return 1;
        }
    }

    if (!sConfig.SetSource(cfg_file))
    {
        sLog.outError("Could not find configuration file %s.", cfg_file);
        Log::WaitBeforeContinueIfNeed();
        return 1;
    }
    sLog.Initialize();

    sLog.outString( "%s [warden-daemon]", _FULLVERSION(REVISION_DATE,REVISION_TIME,REVISION_NR,REVISION_ID) );
    sLog.outString( "<Ctrl-C> to stop.\n" );
    sLog.outString("Using configuration file %s.", cfg_file);

    ///- Check the version of the configuration file
    uint32 confVersion = sConfig.GetIntDefault("ConfVersion", 0);
    if (confVersion < _WARDENDCONFVERSION)
    {
        sLog.outError("*****************************************************************************");
        sLog.outError(" WARNING: Your wardend.conf version indicates your conf file is out of date!");
        sLog.outError("          Please check for updates, as your current default values may cause");
        sLog.outError("          strange behavior.");
        sLog.outError("*****************************************************************************");
        Log::WaitBeforeContinueIfNeed();
    }

    DETAIL_LOG("Using ACE: %s", ACE_VERSION);

    ACE_Reactor::instance(new ACE_Reactor(new ACE_TP_Reactor(), true), true);

    sLog.outBasic("Max allowed open files is %d", ACE::max_handles());

    /// wardend PID file creation
    std::string pidfile = sConfig.GetStringDefault("PidFile", "");
    if (!pidfile.empty())
    {
        uint32 pid = CreatePIDFile(pidfile);
        if( !pid )
        {
            sLog.outError( "Cannot create PID file %s.\n", pidfile.c_str() );
            Log::WaitBeforeContinueIfNeed();
            return 1;
        }

        sLog.outString( "Daemon PID: %u\n", pid );
    }

    ///- Launch the listening network socket
    ACE_Acceptor<WardenSocket, ACE_SOCK_Acceptor> acceptor;

    uint16 rmport = sConfig.GetIntDefault("WardenServerPort", DEFAULT_WARDENSERVER_PORT);
    std::string bind_ip = sConfig.GetStringDefault("BindIP", "0.0.0.0");

    ACE_INET_Addr bind_addr(rmport, bind_ip.c_str());

    if (acceptor.open(bind_addr, ACE_Reactor::instance(), ACE_NONBLOCK) == -1)
    {
        sLog.outError("MaNGOS wardend can not bind to %s:%d", bind_ip.c_str(), rmport);
        Log::WaitBeforeContinueIfNeed();
        return 1;
    }

    ///- Catch termination signals
    HookSignals();

    ///- Handle affinity for multiple processors and process priority on Windows
    HANDLE hProcess = GetCurrentProcess();

    uint32 Aff = sConfig.GetIntDefault("UseProcessors", 0);
    if (Aff > 0)
    {
        DWORD appAff;
        DWORD sysAff;

        if(GetProcessAffinityMask(hProcess,&appAff,&sysAff))
        {
            DWORD curAff = Aff & appAff;                // remove non accessible processors

            if (!curAff)
            {
                sLog.outError("Processors marked in UseProcessors bitmask (hex) %x not accessible for wardend. Accessible processors bitmask (hex): %x",Aff,appAff);
            }
            else
            {
                if (SetProcessAffinityMask(hProcess,curAff))
                    sLog.outString("Using processors (bitmask, hex): %x", curAff);
                else
                    sLog.outError("Can't set used processors (hex): %x", curAff);
            }
        }
        sLog.outString();
    }

    bool Prio = sConfig.GetBoolDefault("ProcessPriority", false);

    if(Prio)
    {
        if(SetPriorityClass(hProcess,HIGH_PRIORITY_CLASS))
            sLog.outString("wardend process priority class set to HIGH");
        else
            sLog.outError("ERROR: Can't set wardend process priority class.");
        sLog.outString();
    }

    sWardend.Initialize();

    ///- Wait for termination signal
    while (!stopEvent)
    {
        // dont move this outside the loop, the reactor will modify it
        ACE_Time_Value interval(0, 100000);

        if (ACE_Reactor::instance()->run_reactor_event_loop(interval) == -1)
            break;

        if (m_ServiceStatus == 0) stopEvent = true;
        while (m_ServiceStatus == 2) Sleep(1000);
    }

    ///- Remove signal handling before leaving
    UnhookSignals();

    sLog.outString( "Halting process..." );

    // Cleaning up objects in memory
    ACE_Reactor::instance()->close_singleton();
    return 0;
}

/// Handle termination signals
/** Put the global variable stopEvent to 'true' if a termination signal is caught **/
void OnSignal(int s)
{
    switch (s)
    {
        case SIGINT:
        case SIGTERM:
            stopEvent = true;
            break;
        case SIGBREAK:
            stopEvent = true;
            break;
    }
    signal(s, OnSignal);
}

/// Define hook 'OnSignal' for all termination signals
void HookSignals()
{
    signal(SIGINT, OnSignal);
    signal(SIGTERM, OnSignal);
    signal(SIGBREAK, OnSignal);
}

/// Unhook the signals before leaving
void UnhookSignals()
{
    signal(SIGINT, 0);
    signal(SIGTERM, 0);
    signal(SIGBREAK, 0);
}