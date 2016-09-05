/*
 * @file		CallWndProc
 * @author		afeng0007
 * @email		afeng0007@gmail.com
 * @date        2016-09-03
 * 
 * @brief		install and uninstall hook of type: WH_CALLWNDPROC
 * 
 */
#pragma once


/**
 * @brief       Callback of the type hook: WH_CALLWNDPROC
 * @param       nCode  [description]
 * @param       wParam [description]
 * @param       lParam [description]
 * @return      [description]
 */
LRESULT CALLBACK CallWndProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam);

/**
 * @brief       install/uninstall the hook: WH_CALLWNDPROC
 * 
 * @param       hwndMonitor: hwnd to monitor
 * @param       hwndNotify: hwnd to notify
 * @param       uNotifyMsg: message to notify, the msg must be  `RegisterWindowMessage`
 * @return      status of the install
 * 
 */
int WINAPI InstallCallWndProc(HWND hwndMonitor, HWND hwndNotify, UINT uNotifyMsg);
void WINAPI UninstallCallWndProc();