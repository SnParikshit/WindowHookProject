#pragma once

#include<windows.h>
#include <UIAutomation.h>

class CWindowHook
{
public:
	static HHOOK m_hWindowHook;

public:
	HHOOK GetWindowHook() { return m_hWindowHook; }
	void  SetWindowHook(HHOOK windowHook) { m_hWindowHook = windowHook; }
	static LRESULT CALLBACK WindowHookProc(int nCode, WPARAM wParam, LPARAM lParam);
	

private:
	static void GetFocusedElementInfo();
	static void PrintElementInfo(IUIAutomationElement* pElement);
};

