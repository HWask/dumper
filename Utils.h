#pragma once

class Utils
{
public:
	template<typename Function> static Function vfunc(void* base, int index)
	{
		DWORD* VTable = *(DWORD**)base;
		return (Function)VTable[index];
	}
};