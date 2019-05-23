#pragma once
#include "RecvProp.h"

class RecvTable
{
public:
	RecvProp* GetProperty(int i)
	{
		return (RecvProp*)((*(DWORD*)this) + i * 60);
	}

	int NumProps()
	{
		return *(int*)((DWORD)this + 0x4);
	}
};