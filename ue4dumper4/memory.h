#pragma once

extern DWORD pID;
bool readRaw(LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead);
void writeRaw(LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead);
int getAowProcID();
kaddr getRealOffset(kaddr offset);
template<typename T>
T Read(kaddr address);
template<typename T>
void Write(kaddr address, T data);
template<typename T>
T* ReadArr(kaddr address, unsigned int size);
string ReadStr(kaddr address, unsigned int size);
string ReadStr2(kaddr address, unsigned int size);
kaddr getPtr(kaddr address);
void HexDump(kaddr addr, int lines);
void HexDump1B(kaddr addr, int lines);
void HexDump4B(kaddr addr, int lines);
void HexDump8B(kaddr addr, int lines);

template<typename T>
T Read(kaddr address) {
    T data;
    readRaw(reinterpret_cast<void*>(address), reinterpret_cast<void*>(&data), sizeof(T), 0);
    return data;
}

template<typename T>
void Write(kaddr address, T data) {
    writeRaw(reinterpret_cast<void*>(address), reinterpret_cast<void*>(&data), sizeof(T), 0);
}

template<typename T>
T* ReadArr(kaddr address, unsigned int size) {
    T* shit = {};
    T ptr = shit[size];
    readRaw(reinterpret_cast<void*>(address), reinterpret_cast<void*>(ptr), (sizeof(T) * size), 0);
    return (T*)ptr;
}