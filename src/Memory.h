#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cstdint>
#include <tchar.h>
#include <TlHelp32.h>
#include <tchar.h>
class Memory
{
public:
	DWORD PROCESSID = 0;
	HANDLE PROCESS = 0;
	DWORD BASE_ADDRESS = 0;
	Memory(DWORD pid=0);
	void Write(LPCVOID Address, int Value);
	DWORD Read(LPCVOID Address);

	DWORD getModuleBaseAddress(TCHAR * lpszModuleName, DWORD initOffset=0);
	DWORD FindPointer(int level, int baseaddr, int offsets[]);
	void GetProcessFromWindow(const char*);
	~Memory();
};

