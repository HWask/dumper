#pragma once

class RecvTable;

typedef enum
{
	DPT_Int = 0,
	DPT_Float,
	DPT_Vector,
	DPT_VectorXY, // Only encodes the XY of a vector, ignores Z
	DPT_String,
	DPT_Array,	// An array of the base types (can't be of datatables).
	DPT_DataTable,
	DPT_Int64,
	DPT_NUMSendPropTypes
} Type;

typedef void(*RecvVarProxyFn)(void* pData, void* pStruct, void* pOut);

class RecvProp
{
public:
	char* GetName()
	{
		return (char*)*(DWORD*)this;
	}

	Type GetType()
	{
		return (Type)*(DWORD*)((DWORD)this+4);
	}

	int GetOffset()
	{
		return *(int*)((DWORD)this+44);
	}

	RecvTable* GetTable()
	{
		return (RecvTable*)*(DWORD*)((DWORD)this + 40);
	}

	void SetProxyFn(RecvVarProxyFn proxy)
	{
		*(RecvVarProxyFn*)((DWORD)this + 32) = proxy;
	}

	RecvVarProxyFn GetProxyFn()
	{
		return *(RecvVarProxyFn*)((DWORD)this + 32);
	}
};