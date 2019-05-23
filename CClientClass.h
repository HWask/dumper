#pragma once
#include <Windows.h>
#include "RecvTable.h"

class CClientClass
{
public:
	char* GetName()
	{
		return (char*)*(DWORD*)((DWORD)this + 0x8);
	}

	RecvTable* GetRecvTable()
	{
		return (RecvTable*)*(DWORD*)((DWORD)this + 0xC);
	}

	CClientClass* GetNextClass()
	{
		return (CClientClass*)*(DWORD*)((DWORD)this + 0x10);
	}
};