#pragma once
#include "Utils.h"
#include "CClientClass.h"

class IBaseClientDLL 
{
public:
	CClientClass* GetAllClasses()
	{
		typedef CClientClass*(__thiscall* oGetAllClasses)();
		return Utils::vfunc<oGetAllClasses>(this, 8)();
	}
};