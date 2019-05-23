#pragma once
#include "IBaseClientDLL.h"

class Factory
{
public:
	typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);

	IBaseClientDLL*	m_pClient; //client
public:
	Factory()
	{
		m_pClient = NULL;
	}

	void GetInterface()
	{
		HMODULE hClient;
		while ( !(hClient = GetModuleHandle("client.dll")) ) {}
		CreateInterfaceFn ClientFactory = (CreateInterfaceFn)GetProcAddress(hClient, "CreateInterface");
		m_pClient = (IBaseClientDLL*)ClientFactory("VClient017", NULL);
	}
};