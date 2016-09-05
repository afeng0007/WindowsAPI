#pragma once

LRESULT CALLBACK DebugProc(_In_ int iCode, _In_ WPARAM wParam, _In_ LPARAM lParam);

int WINAPI InstallDebugProc(HWND hwndMonitor, HWND hwndNotify, UINT uMsgNotify);
void WINAPI UninstallDebugProc();