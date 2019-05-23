#include  "NetVarMgr.h"

Factory* g_pFactory = new Factory();
NetVarMgr* g_NetVarMgr = new NetVarMgr(g_pFactory);

void Thread()
{
	while (true)
	{
		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			g_pFactory->GetInterface();

			DWORD activeWeapon;
			g_NetVarMgr->GetOffset("CBasePlayer", "m_hActiveWeapon", activeWeapon);
			g_NetVarMgr->GetOffset("CBaseCombatWeapon", "m_iClip1", activeWeapon);
			g_NetVarMgr->GetOffset("CBaseCombatWeapon", "m_flNextPrimaryAttack", activeWeapon);
			g_NetVarMgr->GetOffset("CBasePlayer", "m_aimPunchAngle", activeWeapon);
			g_NetVarMgr->GetOffset("CCSPlayer", "m_iTeamNum", activeWeapon);
			g_NetVarMgr->GetOffset("CCSPlayer", "m_nTickBase", activeWeapon);
			g_NetVarMgr->GetOffset("CBaseCombatWeapon", "m_iItemDefinitionIndex", activeWeapon);

			break;
		}
	}
}

bool __stdcall DllMain(HINSTANCE base, DWORD reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Thread, 0, 0, 0);

	return true;
}