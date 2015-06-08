#include "Memory.h"

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <string>

#include "Memory.h"

using namespace std;
char *menu = "1. Toggle GodMode\n"
			 "2. NoClip\n"
			 "3. Reset Character\n";
			 
// We are NOT in the processes address space, unless we make a dll, so don't forget to openproc & VirtualProtect

#define NOP 0x90 // I think thats right

// Switches
// Fill in for fun :P
struct addr_switches {

//	int GodMode = 0x000000;
	int NoClip = 0x000000;
	int Reset = 0x000000;
	int Health = 0x00248C58;
} addresses;



int main(int argc, _TCHAR* argv[])
{
	
	const char *title = "Step 2";
	Memory *roblox = new Memory();
	roblox->GetProcessFromWindow(title);
	// Later on perhaps do what I did before. if no value is supplied auto-Nop the address
	roblox->Write(addresses.Health, NOP); 

	
	cout << menu;
	int cmd;
	while (true) {

		cout << "CMD : ";
		cin >> cmd;
		switch (cmd) {
		case 1:
			cout << "Activating GodMode\n";

			break;
		}

	}
	getchar();
	return 0;
}
