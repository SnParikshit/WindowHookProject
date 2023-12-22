#pragma once
#include "WindowHook.h"

class CMouseHook
{
private:
	CWindowHook* m_pMousehook;

public:
	void SetMouseHook();
	void UnHookMouse();
};

