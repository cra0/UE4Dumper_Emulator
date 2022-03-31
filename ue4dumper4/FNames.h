#pragma once
string GetFNameFromID(uint32 index);
void DumpBlocks423(ofstream& gname, uint32& count, kaddr FNamePool, uint32 blockId, uint32 blockSize);
void DumpStrings(string out);