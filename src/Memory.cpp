#include "stdafx.h"
#include "Memory.h"


Memory::Memory(DWORD pid)
{
	PROCESSID= pid;
}


void Memory::GetProcessFromWindow(const char* WindowTitle){
	HWND window = FindWindowA(NULL, WindowTitle);
	DWORD pid = NULL;
	int tid = GetWindowThreadProcessId(window, &pid);
	PROCESSID = pid;
	
}

void Memory::Write(LPCVOID Address, int Value)
{
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PROCESSID);
	if (!hProcess) {
		std::cout << "Error opening process!\n";
	}
	else
	{
		DWORD newdatasize = sizeof(Value);
		if (WriteProcessMemory(hProcess, (LPVOID)Address, &Value, sizeof(Value), NULL))
			//std::cout << "Success\n"; 
			;
		else
			//std::cout << "Could not write process memory\n";
			;

		CloseHandle(hProcess);

	}
}
int Memory::Read(LPCVOID Address)
{
	int value = 0;
	HANDLE phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PROCESSID);
	if (phandle)
	{
		if (ReadProcessMemory(phandle, (void*)Address, &value, sizeof(value), 0)) {
			return value;
		}
	}
}
// destroy data and such; later.
Memory::~Memory()
{
}



/*
Old stuff from an interesting idea :p
void activate_switch(int addr, DWORD processid, uint16_t newValue = NOP){
write_addr((LPCVOID)addr, newValue, processid);
}
double read_switch(int addr, DWORD processid){
return read_addr((LPCVOID)addr, processid);
}



//  TODO: Add error handling/returning to check if successful



}
*/
