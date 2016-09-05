/**
 * @file        CBTProc.h
 * @author      afeng0007
 * @date        2016-09-05
 * 
 * @brief       CBT hook for windows
 * 
 */
#pragma once


LRESULT CALLBACK CBTProc(int iCode, WPARAM wParam, LPARAM lParam);


int WINAPI InstallCBTHook(HWND hwndMonitor, HWND hwndNotify, UINT uMsgNotify);
void WINAPI UninstallCBTHook();

