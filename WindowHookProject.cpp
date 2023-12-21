// WindowHookProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "WindowHook.h"
#include "SetMouseHook.h"

int main()
{
    CSetMouseHook* pMouseHook = new CSetMouseHook();
    pMouseHook->SetMouseHook();
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    pMouseHook->UnHookMouse();
    delete pMouseHook;
    return 0;
}