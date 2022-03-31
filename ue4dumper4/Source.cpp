#pragma warning(disable : 4996)
#include "includes.h"

int DumpLib(DWORD pid,DWORD base,DWORD endbase,bool isLibDump,bool isRawDump,bool isFastDump)
{
    //Find PID
    DWORD target_pid = pid;
    if (target_pid == -1) {
        cout << "Can't find the process" << endl;
        return -1;
    }
    cout << "Process name: " << pkg.c_str() << ", Pid: " << target_pid << endl;

    //Lib Base Address
    DWORD libbase = base;
    if (libbase == 0) {
        cout << "Can't find Library: " << lib_name << endl;
        return -1;
    }
    cout << "Base Address of " << lib_name << " Found At " << setbase(16) << libbase << setbase(10)
        << endl;

    if (isLibDump) {
        //Lib End Address
        kaddr start_addr = libbase;
        kaddr end_addr = endbase;
        if (end_addr == 0) {
            cout << "Can't find End of Library: " << lib_name << endl;
            return -1;
        }
        cout << "End Address of " << lib_name << " Found At " << setbase(16) << end_addr
            << setbase(10) << endl;

        //Lib Dump
        size_t libsize = (end_addr - libbase);
        cout << "Lib Size: " << libsize << endl;

        if (isRawDump) {
            ofstream rdump(lib_name, ofstream::out | ofstream::binary);
            if (rdump.is_open()) {
                if (isFastDump) {
                    auto* buffer = new uint8_t[libsize];
                    memset(buffer, '\0', libsize);
                    readRaw((void*)start_addr, buffer, libsize, 0);
                    rdump.write((char*)buffer, libsize);
                }
                else {
                    char* buffer = new char[1];
                    while (libsize != 0) {
                        readRaw((void*)(start_addr++), buffer, 1, 0);
                        rdump.write(buffer, 1);
                        --libsize;
                    }
                }
            }
            else {
                cout << "Can't Output File" << endl;
                return -1;
            }
            rdump.close();
        }
        else {
            string tempPath = "KTemp.dat";

            ofstream ldump(tempPath, ofstream::out | ofstream::binary);
            if (ldump.is_open()) {
                if (isFastDump) {
                    auto* buffer = new uint8_t[libsize];
                    memset(buffer, '\0', libsize);
                    readRaw((void*)start_addr, buffer, libsize, 0);
                    ldump.write((char*)buffer, libsize);
                }
                else {
                    char* buffer = new char[1];
                    while (libsize != 0) {
                        readRaw((void*)(start_addr++), buffer, 1, 0);
                        ldump.write(buffer, 1);
                        --libsize;
                    }
                }
            }
            else {
                cout << "Can't Output File" << endl;
                return -1;
            }
            ldump.close();

            //SoFixer Code//
            cout << "Rebuilding Elf(So)" << endl;

#if (process64 == 1)
            string outPath =  lib_name;

            fix_so(tempPath.c_str(), outPath.c_str(), start_addr);
#else
            ElfReader elf_reader;

            elf_reader.setDumpSoFile(true);
            elf_reader.setDumpSoBaseAddr(start_addr);

            auto file = fopen(tempPath.c_str(), "rb");
            if (nullptr == file) {
                printf("source so file cannot found!!!\n");
                return -1;
            }
            auto fd = fileno(file);

            elf_reader.setSource(tempPath.c_str(), fd);

            if (!elf_reader.Load()) {
                printf("source so file is invalid\n");
                return -1;
            }

            ElfRebuilder elf_rebuilder(&elf_reader);
            if (!elf_rebuilder.Rebuild()) {
                printf("error occured in rebuilding elf file\n");
                return -1;
            }
            fclose(file);
            //SoFixer Code//

            ofstream redump(lib_name, ofstream::out | ofstream::binary);
            if (redump.is_open()) {
                redump.write((char*)elf_rebuilder.getRebuildData(), elf_rebuilder.getRebuildSize());
            }
            else {
                cout << "Can't Output File" << endl;
                return -1;
            }
            redump.close();
#endif

            cout << "Rebuilding Complete" << endl;
            remove(tempPath.c_str());
        }
    }
}
int main()
{
    std::cout << "UE4Dumper For Emulator  Developed by Zakaria-Master https://github.com/Zakaria-Master" << std::endl;
#if process64==1
    Offsets::initOffsets_64();
    if (Settings::isUE423) {
        Offsets::patchUE423_64();
    }
    Offsets::patchCustom_64();
#else
    Offsets::initOffsets_32();
    if (Settings::isUE423) {
        Offsets::patchUE423_32();
    }
    Offsets::patchCustom_32();
#endif

	isPUBGLite();
	isPUBGNewState();
	Offsets::Base = 0x0;
    Offsets::EndBase = 0x0;

	Offsets::GNames = 0x0;
    Offsets::GNOffset = 0x0;
	Offsets::GWorld = 0x0;
    Offsets::GWOffset = 0x0;
    Offsets::GUObjectArray = 0x0;

	 pID = getAowProcID();
     if (pID > 0)
     {
     re:
         system("cls");
         std::cout << "[+] Game PID " << std::hex << pID << std::endl;
         std::cout << "UE4Dumper For Emulator  Developed by Zakaria-Master https://github.com/Zakaria-Master" << std::endl;
         std::cout << "SDK Dump With GObjectArray Press [1],SDK Dump With GWorld Press [2] , Dump Strings Press [3],Dump Objects Press [4],Show ActorList With GWorld Press [5], Dump Lib Game Press [6]" <<std::endl;
    
         int choise = 0;
         std::cin >> choise;
         switch (choise)
         {
         case 1: {
             std::cout << "Input pkg Name Example: com.tencent.ig" << std::endl;
             std::string pkgname = "";
             std::cin >> pkgname;
             pkg = pkgname;
             std::cout << "Input LibUE4 Base" << std::endl;
             DWORD_PTR GameBase;
             std::cin >> std::hex >> GameBase;
             Offsets::Base = GameBase;
             std::cout << "Input Gname Address" << std::endl;
             DWORD_PTR GnameAddress;
             std::cin >> std::hex >> GnameAddress;
             Offsets::GNames = GnameAddress;
             std::cout << "Input Gname Offset" << std::endl;
             DWORD_PTR GnameOffset;
             std::cin >> std::hex >> GnameOffset;
             Offsets::GNOffset = GnameOffset;
             std::cout << "Input GUObjectArray Address" << std::endl;
             DWORD_PTR GUObjectArray;
             std::cin >> std::hex >> GUObjectArray;
             Offsets::GUObjectArray = GUObjectArray;
             if (Offsets::Base != 0 && Offsets::GNames != 0 && Offsets::GUObjectArray != 0)
             {
                 DumpSDK("");
             }
             else
             {
                 std::cout << "Error Address" << std::endl;
             }
             getchar();
         }
               break;
         case 2: {
             std::cout << "Input pkg Name Example: com.tencent.ig" << std::endl;
             std::string pkgname = "";
             std::cin >> pkgname;
             pkg = pkgname;
             std::cout << "Input LibUE4 Base" << std::endl;
             DWORD_PTR GameBase;
             std::cin >> std::hex >> GameBase;
             Offsets::Base = GameBase;
             std::cout << "Input Gname Address" << std::endl;
             DWORD_PTR GnameAddress;
             std::cin >> std::hex >> GnameAddress;
             Offsets::GNames = GnameAddress;
             std::cout << "Input Gname Offset" << std::endl;
             DWORD_PTR GnameOffset;
             std::cin >> std::hex >> GnameOffset;
             Offsets::GNOffset = GnameOffset;
             std::cout << "Input Gworld Address" << std::endl;
             DWORD_PTR GworldAddress;
             std::cin >> std::hex >> GworldAddress;
             Offsets::GWorld = GworldAddress;
             std::cout << "Input Gworld Offset" << std::endl;
             DWORD_PTR GworldOffset;
             std::cin >> std::hex >> GworldOffset;
             Offsets::GWOffset = GworldOffset;
             if (Offsets::Base != 0 && Offsets::GNames != 0 && Offsets::GWorld != 0)
             {
                 DumpSDKW("");
             }
             else
             {
                 std::cout << "Error Address" << std::endl;

             }
             getchar();
         }
               break;
         case 3: {
             std::cout << "Input pkg Name Example: com.tencent.ig" << std::endl;
             std::string pkgname = "";
             std::cin >> pkgname;
             pkg = pkgname;
             std::cout << "Input LibUE4 Base" << std::endl;
             DWORD_PTR GameBase;
             std::cin >> std::hex >> GameBase;
             Offsets::Base = GameBase;
             std::cout << "Input Gname Address" << std::endl;
             DWORD_PTR GnameAddress;
             std::cin >> std::hex >> GnameAddress;
             Offsets::GNames = GnameAddress;
             std::cout << "Input Gname Offset" << std::endl;
             DWORD_PTR GnameOffset;
             std::cin >> std::hex >> GnameOffset;
             Offsets::GNOffset = GnameOffset;
             if (Offsets::Base != 0 && Offsets::GNames != 0)
             {
                 DumpStrings("");
             }
             else
             {
                 std::cout << "Error Address" << std::endl;
             }
             getchar();
         }
               break;
         case 4: {
             std::cout << "Input pkg Name Example: com.tencent.ig" << std::endl;
             std::string pkgname = "";
             std::cin >> pkgname;
             pkg = pkgname;
             std::cout << "Input LibUE4 Base" << std::endl;
             DWORD_PTR GameBase;
             std::cin >> std::hex >> GameBase;
             Offsets::Base = GameBase;
             std::cout << "Input Gname Address" << std::endl;
             DWORD_PTR GnameAddress;
             std::cin >> std::hex >> GnameAddress;
             Offsets::GNames = GnameAddress;
             std::cout << "Input Gname Offset" << std::endl;
             DWORD_PTR GnameOffset;
             std::cin >> std::hex >> GnameOffset;
             Offsets::GNOffset = GnameOffset;
             std::cout << "Input GUObjectArray Address" << std::endl;
             DWORD_PTR GUObjectArray;
             std::cin >> std::hex >> GUObjectArray;
             Offsets::GUObjectArray = GUObjectArray;
             if (Offsets::Base != 0 && Offsets::GNames != 0 && Offsets::GUObjectArray != 0)
             {
                 DumpObjects("");
             }
             else
             {
                 std::cout << "Error Address" << std::endl;

             }
             getchar();
         }
               break;
         case 5: {
             std::cout << "Input pkg Name Example: com.tencent.ig" << std::endl;
             std::string pkgname = "";
             std::cin >> pkgname;
             pkg = pkgname;
             std::cout << "Input LibUE4 Base" << std::endl;
             DWORD_PTR GameBase;
             std::cin >> std::hex >> GameBase;
             Offsets::Base = GameBase;
             std::cout << "Input Gname Address" << std::endl;
             DWORD_PTR GnameAddress;
             std::cin >> std::hex >> GnameAddress;
             Offsets::GNames = GnameAddress;
             std::cout << "Input Gname Offset" << std::endl;
             DWORD_PTR GnameOffset;
             std::cin >> std::hex >> GnameOffset;
             Offsets::GNOffset = GnameOffset;
             std::cout << "Input Gworld Address" << std::endl;
             DWORD_PTR GworldAddress;
             std::cin >> std::hex >> GworldAddress;
             Offsets::GWorld = GworldAddress;
             std::cout << "Input Gworld Offset" << std::endl;
             DWORD_PTR GworldOffset;
             std::cin >> std::hex >> GworldOffset;
             Offsets::GWOffset = GworldOffset;
             if (Offsets::Base != 0 && Offsets::GNames != 0 && Offsets::GWorld != 0)
             {
                 DumpActors();
             }
             else
             {
                 std::cout << "Error Address" << std::endl;

             }
             getchar();
         }
               break;
         case 6: {
             std::cout << "Input pkg Name Example: com.tencent.ig" << std::endl;
             std::string pkgname = "";
             std::cin >> pkgname;
             pkg = pkgname;

             std::cout << "Input Lib Name Example: libUE4.so" << std::endl;
             std::string libname = "";
             std::cin >> libname;
             lib_name = libname.c_str();
             std::cout << "Input Lib Base" << std::endl;
             DWORD_PTR BaseAddress;
             std::cin >> std::hex >> BaseAddress;
             std::cout << "Input Lib End Base Address" << std::endl;
             DWORD_PTR EndBaseAddress;
             std::cin >> std::hex >> EndBaseAddress;

             std::cout << "Input Is Raw Dump" << std::endl;
             bool IsRawDump;
             std::cin >> IsRawDump;
             std::cout << "Input Is Fast Dump" << std::endl;
             bool IsFastDump;
             std::cin >> IsFastDump;
             if (BaseAddress != 0 && EndBaseAddress != 0) {
                 DumpLib(pID, BaseAddress, EndBaseAddress, true, IsRawDump, IsFastDump);
             }
             else
             {
                 std::cout << "Error Address" << std::endl;
             }
             getchar();
         }
               break;
         default:
             goto re;
             break;
         }
         Sleep(500);
		std::cout << "Finshed" << std::endl;
        getchar();
        goto re;
	}
	getchar();
	return 0;
}










