#include "stdafx.h"
#include "DebugProc.h"

extern HINSTANCE g_Instance;

#pragma data_seg("DebugProc")
HHOOK g_hDebugProc = nullptr;
HWND g_hwndDebugProcMonitor = nullptr;
HWND g_hwndDebugProcNotify = nullptr;
UINT g_uMsgDebugProcNotify = 0;
#pragma data_seg()

LRESULT CALLBACK
DebugProc(_In_ int iCode, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	if (iCode < 0)
	{
		return CallNextHookEx(g_hDebugProc, iCode, wParam, lParam);
	}
	if (iCode != HC_ACTION)
	{
		return CallNextHookEx(g_hDebugProc, iCode, wParam, lParam);
	}
	switch (wParam)
	{
	case WH_CALLWNDPROC:
		break;
	case WH_CALLWNDPROCRET:
		break;
	case WH_CBT:
		break;
	case WH_DEBUG:
		break;
	case WH_GETMESSAGE:
		break;
	case WH_JOURNALPLAYBACK:
		break;
	case WH_JOURNALRECORD:
		break;
	case WH_KEYBOARD:
		break;
	case WH_MOUSE:
		break;
	case WH_MSGFILTER:
		break;
	case WH_SHELL:
		break;
	case WH_SYSMSGFILTER:
		break;
	default:
		break;
	}
	LPDEBUGHOOKINFO pDebugInfo = (LPDEBUGHOOKINFO)lParam;
	//TODO: log info
	return CallNextHookEx(g_hDebugProc, iCode, wParam, lParam);
}

int WINAPI
InstallDebugProc(HWND hwndMonitor, HWND hwndNotify, UINT uMsgNotify)
{

	int iRet = -1;
	do
	{
		if (!::IsWindow(hwndMonitor) || !::IsWindow(hwndNotify))
		{
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
		g_hwndDebugProcMonitor = hwndMonitor;
		g_hwndDebugProcNotify = hwndNotify;
		g_uMsgDebugProcNotify= uMsgNotify;
		g_hDebugProc = ::SetWindowsHookEx(WH_CBT, DebugProc, hInstance, dwMonitorThreadId);
		if (nullptr == g_hDebugProc)
		{
			break;
		}
		iRet = 0;
	} while (false);
	if (iRet < 0)
	{
		UninstallDebugProc();
	}
	return iRet;
}

void WINAPI
UninstallDebugProc()
{
	if (nullptr != g_hDebugProc)
	{
		UnhookWindowsHookEx(g_hDebugProc);
		g_hDebugProc = nullptr;
	}
	g_hwndDebugProcMonitor = nullptr;
	g_hwndDebugProcNotify = nullptr;
	g_uMsgDebugProcNotify = 0;
}


