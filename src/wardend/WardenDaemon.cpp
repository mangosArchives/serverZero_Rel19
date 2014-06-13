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
#include "zlib/zlib.h"
#include "Policies/SingletonImp.h"
#include "ByteBuffer.h"

// === Warden Daemon internal module management ===

INSTANTIATE_SINGLETON_1(Wardend);

void CWardenLoader::UnloadWarden()
{
    if (pdwModule)
    {
        CLibraryEntry* pLibraryList = GetAddress<CLibraryEntry*>(GetHeader()->dwLibraryTable);
        while (dwLibraryCount)
        {
            dwLibraryCount--;
            DEBUG_LOG("Unloading lib %s...", GetAddress<const char*>(pLibraryList[dwLibraryCount].dwFileName));
            FreeLibrary(GetModuleHandleA(GetAddress<const char*>(pLibraryList[dwLibraryCount].dwFileName)));
        }
        VirtualFree(pdwModule, /*dwModuleSize*/ 0, MEM_RELEASE); // No size when VirtualFree with MEM_RELEASE!!

        pdwModule = 0;
        dwModuleSize = 0;
    }
}

bool CWardenLoader::LoadWarden(PDWORD pdwNewModule, DWORD dwSize)
{
    bool bUnload = true;

    dwModuleSize = GetHeader(pdwNewModule)->dwModuleSize;
    if (dwModuleSize < 0x80000000)
    {
        pdwModule = reinterpret_cast<PDWORD>(VirtualAlloc(0, dwModuleSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE));
        if (pdwModule)
        {
            // Writing code begin
            memcpy(pdwModule, pdwNewModule, sizeof(CHeader));

            PDWORD pdwChunk = &pdwNewModule[(sizeof(CHeader) / sizeof(DWORD)) + GetHeader()->dwChunkCount * 3];
            DWORD dwChunkDest = GetAddress<DWORD>(pdwNewModule[sizeof(CHeader) / sizeof(DWORD)]);
            DWORD dwModuleEnd = GetAddress<DWORD>(dwModuleSize);
            bool bCopyChunk = true;

            while (dwChunkDest < dwModuleEnd)
            {
                DWORD dwCurrentChunkSize = ((WORD*)pdwChunk)[0];
                pdwChunk = (PDWORD)((DWORD)pdwChunk + (DWORD)2);

                if (bCopyChunk)
                {
                    memcpy((void*)dwChunkDest, pdwChunk, dwCurrentChunkSize);
                    pdwChunk = (PDWORD)((DWORD)pdwChunk + dwCurrentChunkSize);
                }

                dwChunkDest  += dwCurrentChunkSize;
                bCopyChunk = !bCopyChunk;
            }
            // Writing code end
            // Relocations begin
            PBYTE pbRelocationTable = GetAddress<PBYTE>(GetHeader()->dwSizeOfCode);
            DWORD dwRelocationIndex = 0, dwLastRelocation = 0;

            while (dwRelocationIndex < GetHeader()->dwRelocationCount)
            {
                DWORD dwValue = pbRelocationTable[0];
                if (dwValue < 0)
                {
                    dwValue = (dwValue & 0x7F) << 8;
                    dwValue = (dwValue + pbRelocationTable[1]) << 8;
                    dwValue = (dwValue + pbRelocationTable[2]) << 8;
                    dwValue += pbRelocationTable[3];

                    pbRelocationTable = (PBYTE)((DWORD)pbRelocationTable + 4);
                    *GetAddress<DWORD*>(dwValue) += reinterpret_cast<DWORD>(pdwModule);
                }
                else
                {
                    dwValue = (dwValue << 8) + dwLastRelocation + pbRelocationTable[1];

                    pbRelocationTable = (PBYTE)((DWORD)pbRelocationTable + 2);
                    *GetAddress<DWORD*>(dwValue) += reinterpret_cast<DWORD>(pdwModule);
                }

                dwRelocationIndex++;
                dwLastRelocation = dwValue;
            }
            // Relocations end
            // Imports begin
            CLibraryEntry * pLibraryTable = GetAddress<CLibraryEntry*>(GetHeader()->dwLibraryTable);
            dwLibraryCount = 0;
            DWORD dwLibraryIndex = 0;
            while (dwLibraryIndex < GetHeader()->dwLibraryCount)
            {
                DEBUG_LOG("Loading lib %s...", GetAddress<const char*>(pLibraryTable[dwLibraryIndex].dwFileName));
                HMODULE hModule = LoadLibraryA(GetAddress<const char*>(pLibraryTable[dwLibraryIndex].dwFileName));
                if (hModule)
                {
                    PDWORD pdwImports = GetAddress<PDWORD>(pLibraryTable[dwLibraryIndex].dwImports), dwLastImport = 0;
                    while (*pdwImports)
                    {
                        DWORD & dwCurrent = *pdwImports;

                        if( dwCurrent <= 0 )
                            dwCurrent = reinterpret_cast<DWORD>(GetProcAddress(hModule, (char*)(dwCurrent & 0x7FFFFFFF)));
                        else
                            dwCurrent = reinterpret_cast<DWORD>(GetProcAddress(hModule, GetAddress<const char*>(dwCurrent)));

                        pdwImports++;
                    }
                }
                dwLibraryIndex++;
                dwLibraryCount++;
            }
            // Imports end
            // Chunk protection flags begin
            DWORD dwIndex = 0;
            while (dwIndex < GetHeader()->dwChunkCount)
            {
                PDWORD pdwChunk = &pdwModule[10 + dwIndex * 3];

                DWORD dwOldProtect = 0;
                VirtualProtect(GetAddress<void*>(pdwChunk[0]), pdwChunk[1], pdwChunk[2], &dwOldProtect);

                if( pdwChunk[2] & 0xF0) // execute flag
                    FlushInstructionCache(GetCurrentProcess(), GetAddress<void*>(pdwChunk[0]), pdwChunk[1]);

                dwIndex++;
            }
            // Chunk protection flags end
            // Code size check begin
            if (GetHeader()->dwSizeOfCode < dwModuleSize)
            {
                DWORD dwOffset = ((GetHeader()->dwSizeOfCode + 0xFFF) & 0xFFFFF000);
                if (dwOffset >= GetHeader()->dwSizeOfCode && dwOffset > dwModuleSize)
                    VirtualFree(GetAddress<void*>(dwOffset), dwModuleSize - dwOffset, MEM_DECOMMIT);

                bUnload = false;
            }
            // Code size check end
            if (bUnload)
                UnloadWarden();
        }
        else
            return false;
    }
    else
        return false;

    return true;
}

// === Module callback functions ===

void __stdcall cSendPacket(LPVOID pPacket, DWORD dwSize)
{
    DEBUG_LOG("Callback cSendPacket called. Packet at 0x%08X size %u.", (PDWORD)pPacket, dwSize);
}

BOOL __stdcall cCheckModule(BYTE* pModName, DWORD _2)
{
    DEBUG_LOG("Callback cCheckModule called.");
    return 0;
}

WardenFuncList** __stdcall cLoadModule(BYTE* pRC4Key, BYTE* pModule, DWORD dwModSize)
{
    DEBUG_LOG("Callback cLoadModule called.");
    return 0;
}

LPVOID __stdcall cAllocateMemory(DWORD dwSize)
{
    LPVOID res = (LPVOID)malloc(dwSize);
    DEBUG_LOG("Callback cAllocateMemory called. Allocated %u bytes at 0x%08X", dwSize, res);
    return res;
}

VOID __stdcall cReleaseMemory(LPVOID lpMemory)
{
    DEBUG_LOG("Callback cReleaseMemory called. Memory at 0x%08X", lpMemory);
    free(lpMemory);
}

VOID __stdcall cSetRC4Data(LPVOID lpKeys, DWORD dwSize)
{
    DEBUG_LOG("Callback cSetRC4Data called. Keys at 0x%08X, key size 0x%04X (%u).", lpKeys, dwSize, dwSize);
}

DWORD __stdcall cGetRC4Data(LPVOID lpBuffer, LPDWORD dwSize)
{
    DEBUG_LOG("Callback cGetRC4Data called. Buffer at 0x%08X, key size 0x%04X (%u).", (PDWORD)lpBuffer, *(DWORD*)dwSize, *(DWORD*)dwSize);
    memset(lpBuffer, 0, *(DWORD*)dwSize);
    return 1;
}

WardenFuncList **CWardenLoader::InitializeWarden(InstanceS *instance)
{
    DWORD A, B, C, D;

    DEBUG_LOG("Warden module mapped to: 0x%08X", pdwModule);

    C = GetHeader()->dwProcedureAdjust;
    B = 1 - C;

    if (B > GetHeader()->dwProcedureCount)
        return FALSE;

    A = GetHeader()->dwProcedureTable; // offsetWardenSetup
    D = *(DWORD*)&pdwModule[A / 4 + B * 4];
    A = D + (DWORD)pdwModule;

    fnInitializeModule fpInitializeModule;
    fpInitializeModule = (fnInitializeModule)A;
    DEBUG_LOG("Initialize Function mapped to: 0x%08X (0x%04X)", (PDWORD)A ,PDWORD((PDWORD)A - pdwModule));

    // initialize callbacks
    memset(&instance->dwTable, 0, sizeof(FuncList));
    instance->dwTable.fpSendPacket        = cSendPacket;
    instance->dwTable.fpCheckModule       = cCheckModule;
    instance->dwTable.fpLoadModule        = cLoadModule;
    instance->dwTable.fpAllocateMemory    = cAllocateMemory;
    instance->dwTable.fpReleaseMemory     = cReleaseMemory;
    instance->dwTable.fpSetRC4Data        = cSetRC4Data;
    instance->dwTable.fpGetRC4Data        = cGetRC4Data;
    instance->tableptr = &instance->dwTable;

    char * szCallbacksDesc[] = {
        "SendPacket",
        "CheckModule",
        "LoadModule",
        "AllocateMemory",
        "ReleaseMemory",
        "SetRC4Data",
        "GetRC4Data"
    };

    DEBUG_LOG("Warden callbacks:");
    for (int i = 0; i < 7; ++i)
        DEBUG_LOG("Callback: %s at: 0x%08X" ,szCallbacksDesc[i], ((PDWORD*)&instance->dwTable)[i]);

    // warden functions pointers
    DEBUG_LOG("Calling Warden::Initialize");
    WardenFuncList **list = fpInitializeModule((DWORD*)&instance->tableptr);

    char * szInitReturnDesc[] = {
        "GenerateRC4Keys",
        "UnloadModule",
        "PacketHandler",
        "Tick"
    };

    DEBUG_LOG("Warden::Initialize returns:");
    for (int i = 0; i < 4; ++i)
        DEBUG_LOG("Init: Warden::%s at: 0x%08X",szInitReturnDesc[i] ,((PDWORD*)*list)[i]);

    return list;
}

void CWardenLoader::PrintHeader( PDWORD pdwHeader )
{
    char * szHeaderDescription[] = {
        "Module size",
        "Destructor",
        "SizeOfCode",
        "RelocationCount",
        "ProcedureTable",
        "ProcedureCount",
        "ProcedureAdjust",
        "LibraryTable",
        "LibraryCount",
        "ChunkCount"
    };

    for (int i = 0; i < 10; i++)
    {
        DEBUG_LOG( "%u .+ 0x%02X %s -> %u", i ,i * 4, szHeaderDescription[i], pdwHeader[i]);
    }
}

// === Module maped functions ===

void GenerateRC4Keys(LPVOID lpData, DWORD dwSize, InstanceS *instance)
{
    DEBUG_LOG("Warden::GenerateRC4Keys called");
    ((fnGenerateRC4Keys)instance->pointers.f1)(instance->list, lpData, dwSize);
}

void UnloadModule(InstanceS *instance)
{
    DEBUG_LOG("Warden::UnloadModule called");
    ((fnUnloadModule)instance->pointers.f2)(instance->list);
}

void PacketHandler(BYTE *pPacket, DWORD dwSize, DWORD *dwBuffer, InstanceS *instance)
{
    DEBUG_LOG("Warden::PacketHandler called");
    ((fnPacketHandler)instance->pointers.f3)(instance->list, pPacket, dwSize, dwBuffer);
    DEBUG_LOG("Warden::PacketHandler handeled %u bytes of the packet", *dwBuffer);
}

void Tick(DWORD _2, InstanceS *instance)
{
    DEBUG_LOG("Warden::Tick called");
    ((fnTick)instance->pointers.f4)(instance->list, _2);
}

void Wardend::Initialize()
{
    sLog.outString("Warden system initialized." );
}

Wardend::Wardend()
{
}

bool Wardend::LoadModuleAndExecute(uint32 accountId, uint32 modLen, uint8 *module, uint8 *sessionKey, uint8 *packet, ByteBuffer *returnPacket)
{
    DEBUG_LOG("Wardend::LoadModuleAndExecute()");

    uint32 m_signature = *(uint32*)(module + modLen - 4); // - sizeof(uint32)
    if (m_signature != 0x5349474E) // NGIS->SIGN string
    {
        sLog.outError("Warden module seams damaged, cannot find signature data.");
        return false;
    }
    // Now inflate the module after removing uint32 size at the beginning and last 4 "SIGN"
    uint32 m_InflateSize = *(uint32*)module;
    uint8* moduleCode = (uint8*)malloc(m_InflateSize);
    uint32 currentSize = modLen - 4 - 4; // - sizeof(uint32) for inflateSize and - sizeof(uint32) for signature
    uLongf finalSize = m_InflateSize;
    if (uncompress(moduleCode, &finalSize, module+4, currentSize) != Z_OK)
    {
        sLog.outError("Warden module could not be inflated.");
        free(moduleCode);
        return false;
    }

    InstanceS instance;
    instance.loader = new CWardenLoader();

    instance.loader->PrintHeader((PDWORD)moduleCode);
    instance.loader->LoadWarden((PDWORD)moduleCode, finalSize);
    instance.list = instance.loader->InitializeWarden(&instance);

    instance.pointers.f1 = &*(*instance.list)->fpGenerateRC4Keys;
    instance.pointers.f2 = &*(*instance.list)->fpUnload;
    instance.pointers.f3 = &*(*instance.list)->fpPacketHandler;
    instance.pointers.f4 = &*(*instance.list)->fpTick;

    uint8 *keyAddr = GenerateNewKeys(&instance, sessionKey, packet);

    *returnPacket << uint8(WMSG_WARDEN_KEYS);
    *returnPacket << uint32(accountId);
    returnPacket->append(((KeyPair*)keyAddr)->server, 0x102);
    returnPacket->append(((KeyPair*)keyAddr)->client, 0x102);
    returnPacket->append(&((WardenInitData*)(instance.list))->seed[0], 16);

    // Unload the module
    UnloadModule(&instance);
    instance.loader->UnloadWarden();
    delete instance.loader;
    free(moduleCode);
    return true;
}

uint8 *Wardend::GenerateNewKeys(InstanceS *instance, uint8 *sessionKey/*[40]*/, uint8 *packet/*[17]*/)
{
    DEBUG_LOG("Wardend::GenerateNewKeys()");
    // Call the module function to generate the key
    GenerateRC4Keys(sessionKey, 40, instance);
    // Then ask it to handle the packet we also sent to the client
    DWORD handled;
    PacketHandler(packet, 17, &handled, instance);
    return &((WardenInitData*)(instance->list))->keys[0];
}

/////////////////////////////
// Singleton access function
/////////////////////////////

Wardend& sWardend
{
    static Wardend wardendaemon;
    return wardendaemon;
}