#include "stdafx.h"
#include "CallWndProc.h"
#include "InjectDll.h"

extern HINSTANCE g_Instance;

#pragma data_seg("CallWndProc")
HHOOK g_hCallWndProc = nullptr;
HWND g_hwndCallWndProcMonitor = nullptr;
HWND g_hwndCallWndProcNotify = nullptr;
UINT g_msgCallWndProcNotify = 0;
#pragma data_seg()



LRESULT CALLBACK CallWndProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	if (nCode < 0)
	{
		return CallNextHookEx(g_hCallWndProc, nCode, wParam, lParam);
	}
	switch (nCode)
	{
	case HC_ACTION:
		{
			BOOL bCAllByCurrentThread = (BOOL)wParam;
			CWPSTRUCT* pWndProc = reinterpret_cast<CWPSTRUCT*>(lParam);
			//TODO: do modify
		}
		break;
	default:
		break;
	}
	return CallNextHookEx(g_hCallWndProc, nCode, wParam, lParam);
}

int WINAPI InstallCallWndProc(HWND hwndMonitor, HWND hwndNotify, UINT uNotifyMsg)
{
	int iRet = -1;
	do 
	{
		if (!::IsWindow(hwndNotify) || !::IsWindow(hwndMonitor))
		{
			//不是合法的hwnd
			break;
		}
		DWORD dwMonitorProcessId = 0;
		DWORD dwMonitorThreadId = ::GetWindowThreadProcessId(hwndMonitor, &dwMonitorProcessId);
		DWORD dwNotifyProcessId = 0;
		DWORD dwNotifyThreadId = ::GetWindowThreadProcessId(hwndNotify, &dwNotifyProcessId);
		HINSTANCE hInstance = g_Instance;
		if (dwMonitorProcessId == dwNotifyProcessId)
		{
			hInstance = nullptr;
		}
		g_hwndCallWndProcMonitor = hwndMonitor;
		g_hwndCallWndProcNotify = hwndNotify;
		g_msgCallWndProcNotify = uNotifyMsg;
		g_hCallWndProc = ::SetWindowsHookEx(WH_CALLWNDPROC, CallWndProc, hInstance, dwMonitorThreadId);
		if (nullptr == g_hCallWndProc)
		{
			break;
		}
		iRet = 0;
	} while (false);
	return iRet;
}

void WINAPI UninstallCallWndProc()
{
	do 
	{
		if (nullptr != g_hCallWndProc)
		{
			UnhookWindowsHookEx(g_hCallWndProc);
			g_hCallWndProc = nullptr;
		}
		g_hwndCallWndProcMonitor = nullptr;
	} while (false);
}