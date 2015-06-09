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
DWORD Memory::Read(LPCVOID Address)
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


DWORD Memory::FindPointer(int level, int baseaddr, int offsets[])
{
	DWORD Address = baseaddr;
	int total = level;
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PROCESSID);
	for (int i = 0; i < total; i++) //Loop trough the offsets
	{
		ReadProcessMemory(pHandle, (LPCVOID)Address, &Address, 4, NULL);
		Address += offsets[i];
	}
	return Address;
}
DWORD Memory::getModuleBaseAddress(TCHAR * lpszModuleName, DWORD initOffset)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PROCESSID);
	DWORD moduleBaseAddr = 0;

	if (hSnapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 mentry32 = { 0 };
		mentry32.dwSize = sizeof(MODULEENTRY32);

		if (Module32First(hSnapshot, &mentry32))
		{
			do
			{
				if (_tcscmp(mentry32.szModule, lpszModuleName) == 0)
				{
					moduleBaseAddr = (DWORD)mentry32.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnapshot, &mentry32));
		}
	}
	else
	{
		std::cout << "Error on finding module base address: " << GetLastError() << "\n";
	}
	BASE_ADDRESS = moduleBaseAddr + initOffset;
	return moduleBaseAddr+initOffset;
}









// destroy data and such
Memory::~Memory()
{
}


/*

void activate_switch(int addr, DWORD processid, uint16_t newValue = NOP){
write_addr((LPCVOID)addr, newValue, processid);
}
double read_switch(int addr, DWORD processid){
return read_addr((LPCVOID)addr, processid);
}



//  TODO: Add error handling/returning to check if successful





}
*/
