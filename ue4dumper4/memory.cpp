#include "includes.h"
DWORD pID = 0;
bool readRaw(LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead) {
    //paste your code here (ReadMemory)
    return 0;
}
void writeRaw(LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead)
{
    //paste your code here (WriteMemory)
}
 int getAowProcID() {
    int pid = 0;
    int threadCount = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);
    Process32First(hSnap, &pe);
    while (Process32Next(hSnap, &pe)) {
        if (_tcsicmp(pe.szExeFile, _T("AndroidProcess.exe")) == 0) {
            if ((int)pe.cntThreads > threadCount) {
                threadCount = pe.cntThreads;
                pid = pe.th32ProcessID;
            }
        }
    }

    return pid;
}

kaddr getRealOffset(kaddr offset) {
    if (Offsets::Base == 0) {
        cout << ("Error: Can't Find Base Addr for Real Offset") << std::endl;
        return 0;
    }
    return (Offsets::Base + offset);
}



string ReadStr(kaddr address, unsigned int size) {
    char* data = new char[size];
    memset(data, '\0', size);

    for (int i = 0; i < size; i++) {
        readRaw((void*)(address + (sizeof(char) * i)), (void*)(&data[0] + i), sizeof(char),0);
        if (data[i] == 0x0) {
            break;
        }
    }

    string name(data);
    name.shrink_to_fit();
    return name;
}

string ReadStr2(kaddr address, unsigned int size) {
    string name(size, '\0');
    readRaw((void*)address, (void*)name.data(), size * sizeof(char),0);
    name.shrink_to_fit();
    return name;
}

kaddr getPtr(kaddr address) {
    return Read<kaddr>(address);
}

void HexDump(kaddr addr, int lines) {
    printf("\n\t\t:Hex Dump:\n\n");
    int ptr = 0;
    for (int i = 0; i < lines; i++) {
#if defined(__LP64__)
        printf("0x%04lx: ", addr + (i * 8));
#else
        printf("0x%04x: ", addr + (i * 8));
#endif
        for (int j = 0; j < 8; j++) {
#if defined(__LP64__)
            printf("0x%02hhx ", Read<char>(addr + ptr++));
#else
            printf("0x%02x ", Read<char>(addr + ptr++));
#endif
        }
        printf("\n");
    }
}

void HexDump1B(kaddr addr, int lines) {
    printf("\n\t\t:Hex Dump:\n\n");
    int ptr = 0;
    for (int i = 0; i < lines; i++) {
        uint8 data1 = Read<uint8>(addr + ptr);
        ptr++;
        uint8 data2 = Read<uint8>(addr + ptr);
        ptr++;
        uint8 data3 = Read<uint8>(addr + ptr);
        ptr++;
        uint8 data4 = Read<uint8>(addr + ptr);
        ptr++;
        uint8 data5 = Read<uint8>(addr + ptr);
        ptr++;
        uint8 data6 = Read<uint8>(addr + ptr);
        ptr++;
        uint8 data7 = Read<uint8>(addr + ptr);
        ptr++;
        uint8 data8 = Read<uint8>(addr + ptr);
        ptr++;
#if defined(__LP64__)
        printf("(%d) 0x%04lx: 0x%02hhx 0x%02hhx 0x%02hhx 0x%02hhx 0x%02hhx 0x%02hhx 0x%02hhx 0x%02hhx",
            i + 1, addr + (i * 8), data1, data2, data3, data4,
            data5, data6, data7, data8);
#else
        printf("(%d) 0x%04x: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x", i + 1, addr + (i * 8), data1, data2, data3, data4,
            data5, data6, data7, data8);
#endif
        printf("\n");
    }
    printf("\n");
}

void HexDump4B(kaddr addr, int lines) {
    printf("\n\t\t:Hex Dump:\n\n");
    int ptr = 0;
    for (int i = 0; i < lines; i++) {
        uint32 data1 = Read<uint32>(addr + ptr);
        ptr += 4;
        uint32 data2 = Read<uint32>(addr + ptr);
        ptr += 4;
#if defined(__LP64__)
        printf("(%d) 0x%lx: 0x%04x 0x%04x", i + 1, addr + (i * 8), data1, data2);
#else
        printf("(%d) 0x%x: 0x%04x 0x%04x", i + 1, addr + (i * 8), data1, data2);
#endif
        printf("\n");
    }
    printf("\n");
}

void HexDump8B(kaddr addr, int lines) {
    printf("\n\t\t:Hex Dump:\n\n");
    int ptr = 0;
    for (int i = 0; i < lines; i++) {
        uint64 data1 = Read<uint64>(addr + ptr);
        ptr += 8;
        uint64 data2 = Read<uint64>(addr + ptr);
        ptr += 8;
#if defined(__LP64__)
        printf("(%d) 0x%lx: 0x%llx 0x%llx", i + 1, addr + (i * 8), data1, data2);
#else
        printf("(%d) 0x%x: 0x%llx 0x%llx", i + 1, addr + (i * 8), data1, data2);
#endif
        printf("\n");
    }
    printf("\n");
}