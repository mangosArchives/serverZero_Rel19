################################################################################
# ScriptDev2 configuration file                                                #
################################################################################

[ScriptDev2Conf]
ConfVersion=2012112301

################################################################################
# DATABASE CONNECTIONS
#
#    ScriptDev2DatabaseInfo
#    Connection settings for the script library database
#        Default: hostname;port;username;password;database
#                 Use named pipes at Windows
#                 .;somenumber;username;password;database
#
#                 Use Unix sockets on Unix/Linux
#                 .;/path/to/unix_socket;username;password;database
#
################################################################################
ScriptDev2DatabaseInfo     = "127.0.0.1;3306;mangos;mangos;scriptdev2"

################################################################################
# LOGGING
#
#    SD2ErrorLogFile
#        File name for logging errors
#        Default: "scriptdev2-error.log"
#                 "" - Empty name disable creating log file
################################################################################
SD2ErrorLogFile = "scriptdev2-errors.log"
