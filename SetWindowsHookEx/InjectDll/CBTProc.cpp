#include "stdafx.h"
#include "CBTProc.h"

extern HINSTANCE g_Instance;

#pragma data_seg("CBTProc")

HHOOK g_hCBTProc = nullptr;
HWND g_hwndMonitor = nullptr;
HWND g_hwndNotify = nullptr;
UINT g_uMsgNotify = 0;

#pragma data_seg()

LRESULT CALLBACK
CBTProc(int iCode, WPARAM wParam, LPARAM lParam)
{
    if (iCode < 0)
    {
        return CallNextHookEx(g_hCBTProc, iCode, wParam, lParam);
    }
    switch (iCode)
    {
    case HCBT_ACTIVATE:
        break;
    case HCBT_CLICKSKIPPED:
        break;
    case HCBT_CREATEWND:
        break;
    case HCBT_DESTROYWND:
        break;
    case HCBT_KEYSKIPPED:
        break;
    case HCBT_MINMAX:
        break;
    case HCBT_MOVESIZE:
        break;
    case HCBT_QS:
        break;
    case HCBT_SETFOCUS:
        break;
    case HCBT_SYSCOMMAND:
        break;
    default:
        break;
    }
    return CallNextHookEx(g_hCBTProc, iCode, wParam, lParam);
}

int WINAPI
InstallCBTHook(HWND hwndMonitor, HWND hwndNotify, UINT uMsgNotify)
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
        g_hwndMonitor = hwndMonitor;
        g_hwndNotify = hwndNotify;
        g_uMsgNotify = uMsgNotify;
        g_hCBTProc = ::SetWindowsHookEx(WH_CBT, CBTProc, hInstance, dwMonitorThreadId);
        if (nullptr == g_hCBTProc)
        {
            break;
        }
        iRet = 0;
    } while (false);
    if (iRet < 0)
    {
        UninstallCBTHook();
    }
    return iRet;
}

void WINAPI
UninstallCBTHook()
{
    if (nullptr != g_hCBTProc)
    {
        UnhookWindowsHookEx(g_hCBTProc);
        g_hCBTProc = nullptr;
    }
    g_hwndNotify = nullptr;
    g_hwndMonitor = nullptr;
    g_uMsgNotify = 0;
}

