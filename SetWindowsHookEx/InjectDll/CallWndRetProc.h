/**
 * @file        CallWndRetProc.h
 * @author      afeng0007
 * @email       afeng0007@gmail.com
 * @date        2016-09-03
 *
 * @brief       example to install/uninstall the hook: WH_CALLWNDPROCRET
 *
 * @reference   
 */

#pragma once

/**
 * @brief       call back of the hook with type: WH_CALLWNDPROCRET
 * @param       iCode  
 * @param       wParam [description]
 * @param       lParam [description]
 * 
 * @return      [description]
 */
LRESULT CALLBACK CallWndRetProc(_In_ int iCode, _In_ WPARAM wParam, _In_ LPARAM lParam);

/**
 * @brief       install/unstall the hook of WH_CALLWNDPROCRET
 * @param       hwndMonitor:    hwnd to monitor
 * @param       hwndNotify:     hwnd to notify
 * @param       uMsgNotify:     message to notify
 * 
 * @return      status of return
 */
int WINAPI  InstallCallWndRet(HWND hwndMonitor, HWND hwndNotify, UINT uMsgNotify);
void WINAPI UninstallCallWndRet();