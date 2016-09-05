#include "stdafx.h"
#include "CallWndRetProc.h"

extern HINSTANCE g_Instance;

#pragma data_seg("CallWndRetProc")
HHOOK g_hCallWndRet = nullptr;
HWND g_hwndCallWndRetMonitor = nullptr;
HWND g_hwndCallWndRetNotify = nullptr;
UINT g_uMsgCallWndRetNotify = 0;
#pragma data_seg()


LRESULT CALLBACK CallWndRetProc(_In_ int iCode, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    if (iCode < 0)
    {
        return CallNextHookEx(g_hCallWndRet, iCode, wParam, lParam);
    }
    switch (iCode)
    {
    case HC_ACTION:
    {
        CWPRETSTRUCT* pWndRet = reinterpret_cast<CWPRETSTRUCT*>(lParam);
        //TODO: modify
    }
    break;
    default:
        break;
    }
    return CallNextHookEx(g_hCallWndRet, iCode, wParam, lParam);
}

int WINAPI InstallCallWndRet(HWND hwndMonitor, HWND hwndNotify, UINT uMsgNotify)
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
        g_hwndCallWndRetMonitor = hwndMonitor;
        g_hwndCallWndRetNotify = hwndNotify;
        g_uMsgCallWndRetNotify = uMsgNotify;
        g_hCallWndRet = ::SetWindowsHookEx(WH_CALLWNDPROCRET, CallWndRetProc, hInstance, dwMonitorThreadId);
        if (nullptr == g_hCallWndRet)
        {
            break;
        }
        iRet = 0;
    } while (false);
    if (iRet < 0)
    {
        UninstallCallWndRet();
    }
    return iRet;
}

void WINAPI UninstallCallWndRet()
{
    do 
    {
        if (nullptr != g_hCallWndRet)
        {
            UnhookWindowsHookEx(g_hCallWndRet);
            g_hCallWndRet = nullptr;
        }
        g_hwndCallWndRetMonitor = nullptr;
        g_hwndCallWndRetNotify = nullptr;
        g_uMsgCallWndRetNotify = 0;
    } while (false);
}