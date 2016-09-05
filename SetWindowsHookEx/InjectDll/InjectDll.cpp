#include "stdafx.h"
#include "InjectDll.h"

#pragma data_seg("Common")
HINSTANCE g_Instance = nullptr;
#pragma data_seg()

BOOL WINAPI DllMain(_In_ HINSTANCE hinstDLL, _In_ unsigned long _Reason, _In_opt_ void* _Reserved)
{
	switch (_Reason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hinstDLL);
		break;
	case DLL_PROCESS_DETACH:
		break;
	default:
		break;
	}
	return TRUE;
}