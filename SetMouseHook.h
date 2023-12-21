#pragma once
#include "WindowHook.h"

class CSetMouseHook
{
private:
	CWindowHook* m_pMousehook;

public:
	void SetMouseHook();
	void UnHookMouse();
};

