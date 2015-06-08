#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cstdint>


class Memory
{
public:
	DWORD PROCESSID = 0;
	//HANDLE PROCESS = 0;
	
	Memory(DWORD pid=0);
	void Write(LPCVOID Address, int Value);
	int Read(LPCVOID Address);

	void GetProcessFromWindow(const char*);
	~Memory();
};

