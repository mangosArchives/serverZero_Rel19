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

#ifndef __WARDEND_H
#define __WARDEND_H

#include "Common.h"
#include "WardendProtocol.h"

#define WARDEN_MAX_MODULES  20

class ByteBuffer;

typedef struct _WardenFuncList WardenFuncList;
struct InstanceS;

//Input
typedef VOID (__stdcall *fnSendPacket)(BYTE* pPacket, DWORD dwSize);
typedef BOOL (__stdcall *fnCheckModule)(BYTE* pModName, DWORD _2);
typedef WardenFuncList** (__stdcall *fnLoadModule)(BYTE* pRC4Key, BYTE* pModule, DWORD dwModSize);
typedef LPVOID (__stdcall *fnAllocateMemory)(DWORD dwSize);
typedef VOID (__stdcall *fnReleaseMemory)(LPVOID lpMemory);
typedef VOID (__stdcall *fnSetRC4Data)(LPVOID lpKeys, DWORD dwSize);
typedef DWORD (__stdcall *fnGetRC4Data)(LPVOID lpBuffer, LPDWORD dwSize);
typedef struct _FuncList
{
    void *fpSendPacket;     //0x00
    void *fpCheckModule;    //0x04
    void *fpLoadModule;     //0x08
    void *fpAllocateMemory; //0x0C
    void *fpReleaseMemory;  //0x10
    void *fpSetRC4Data;     //0x14
    void *fpGetRC4Data;     //0x18
} FuncList;

//output
typedef VOID (__thiscall *fnGenerateRC4Keys)(WardenFuncList** ppFncList, LPVOID lpData, DWORD dwSize);
typedef VOID (__thiscall *fnUnloadModule)(WardenFuncList** ppFncList);
typedef VOID (__thiscall *fnPacketHandler)(WardenFuncList** ppFncList, BYTE* pPacket, DWORD dwSize, DWORD* dwBuffer);
typedef VOID (__thiscall *fnTick)(WardenFuncList** ppFncList, DWORD _2); // _2 is sum dwOldTick - GetTickCount(); shit ..
typedef struct _WardenFuncList
{
    fnGenerateRC4Keys * fpGenerateRC4Keys;  //0x00
    fnUnloadModule * fpUnload;              //0x04 - Before it frees everything it will call FuncList:fpSetRC4Data and store the RC4 key
    fnPacketHandler * fpPacketHandler;      //0x08
    fnTick * fpTick;                        //0x0C
} WardenFuncList;

typedef struct _WardenChkFuncList
{
    uint32 FctAddr[15]; // we may need to init one of them to use the Tick function
} WardenChkFuncList;

typedef struct _WardenInitData
{
    _WardenFuncList* pFct;
    uint8 seed[16];
    uint32 unknown1;
    uint32 callbacks_ptr;
    uint32 unknown2;
    uint8 keys[0x204];
    uint32 packetSkipBytes;
    _WardenChkFuncList *pCheckFct;
    // and so on, but I need only the seed 1st byte
} WardenInitData;

typedef struct _KeyPair
{
    uint8 client[0x102];
    uint8 server[0x102];
} KeyPair;

typedef WardenFuncList** (__fastcall *fnInitializeModule)(DWORD* lpPtr2Table);

class CWardenLoader
{
    class CLibraryEntry
    {
    public:
        DWORD dwFileName;
        DWORD dwImports;
    };
    class CHeader
    {
    public:
        DWORD dwModuleSize;
        DWORD dwDestructor;
        DWORD dwSizeOfCode;
        DWORD dwRelocationCount;
        DWORD dwProcedureTable;
        DWORD dwProcedureCount;
        DWORD dwProcedureAdjust;
        DWORD dwLibraryTable;
        DWORD dwLibraryCount;
        DWORD dwChunkCount;
    };

    PDWORD pdwModule;
    DWORD dwModuleSize, dwLibraryCount;
public:
    template< class T >
    T GetAddress( DWORD dwOffset )
    {
        return reinterpret_cast< T >( reinterpret_cast<DWORD>( pdwModule ) + dwOffset );
    }

    template<>
    unsigned long GetAddress<DWORD>( DWORD dwOffset )
    {
        return reinterpret_cast<DWORD>( pdwModule ) + dwOffset;
    }

    inline CHeader * GetHeader( PDWORD pdwNewModule = 0 )
    {
        return reinterpret_cast<CHeader*>( pdwNewModule ? pdwNewModule : pdwModule );
    }

    void UnloadWarden();
    bool LoadWarden( PDWORD pdwNewModule, DWORD dwSize );
    PDWORD GetModule() { return pdwModule; }

    template<class T>
    T GetEntryPoint( DWORD dwIndex )
    {
        if( pdwModule )
        {
            dwIndex -= GetHeader()->dwProcedureAdjust;
            if( dwIndex < GetHeader()->dwProcedureCount )
                return GetAddress<T>( GetAddress<PDWORD>( GetHeader()->dwProcedureTable )[ dwIndex ] );
        }
        return 0;
    }
    WardenFuncList **InitializeWarden(InstanceS *instance);
    void PrintHeader( PDWORD pdwHeader );
};

struct fPointers
{
    void *f1;
    void *f2;
    void *f3;
    void *f4;
};

struct InstanceS
{
    FuncList dwTable;
    FuncList *tableptr;
    fPointers pointers;
    WardenFuncList **list;
    CWardenLoader *loader;
};

struct Wardend
{
    public:
        static Wardend& Instance();
        Wardend();
        ~Wardend() {}
        void Initialize();
        bool LoadModuleAndExecute(uint32 accountId, uint32 modLen, uint8 *module, uint8 *sessionKey, uint8 *packet, ByteBuffer *returnPacket);
    private:
        uint8 *GenerateNewKeys(InstanceS *instance, uint8 *sessionKey/*[40]*/, uint8 *packet/*[17]*/);
};

#define sWardend Wardend::Instance()

#endif