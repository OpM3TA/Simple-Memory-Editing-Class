#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <string>


#include "Memory.h"

using namespace std;
char *menu = "1. Toggle GodMode\n"
			 "2. NoClip\n"
			 "3. Reset Character\n";

// Switches


#define NOP 0x90 // I think thats right
// We are NOT in the processes address space, unless we make a dll, so don't forget to openproc & VirtualProtect
struct addr_switches {

	int GodMode = 0x000000;
	int NoClip = 0x000000;
	int Reset = 0x000000;
	int Health = 0x00248C58;
} addresses;





int main(int argc, _TCHAR* argv[])
{
	
	const char *title = "Step 2";
	Memory *roblox = new Memory();
	roblox->GetProcessFromWindow(title);
	roblox->getModuleBaseAddress(_TEXT("Tutorial-i386.exe"), 0x00245300);

	int offsets[] = { 0x754, 0x24c, 0x104, 0x8, 0x6c0 };
	DWORD addr = roblox->FindPointer(5, roblox->BASE_ADDRESS, offsets);


	cout << menu;
	int cmd;
	while (true) {

		cout << "CMD : ";
		cin >> cmd;
		switch (cmd) {
		case 1:
			cout << "Activating GodMode\n";
			roblox->Write((LPCVOID)addr, 1000);
			break;
		default:
			cout << cmd <<endl;
			break;
		}

	}
	getchar();
	return 0;
}
