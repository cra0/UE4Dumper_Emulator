#pragma once
string resolveProp(list<kaddr>& recurrce, kaddr prop);
string resolveProp423(list<kaddr>& recurrce, kaddr prop);
bool isScanned(uint32 id);
list<kaddr> writeStructChild(ofstream& sdk, kaddr childprop);
list<kaddr> writeStructChild423(ofstream& sdk, kaddr childprop);
list<kaddr> writeStructChild423_Func(ofstream& sdk, kaddr childprop);
void writeStruct(ofstream& sdk, kaddr clazz);
void DumpSDK(string out);
void TestDump(kaddr uobj);
void DumpSDKW(string out);
void DumpActors();