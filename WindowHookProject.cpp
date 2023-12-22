// WindowHookProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "WindowHook.h"
#include "MouseHook.h"

int main()
{
    CMouseHook* pMouseHook = new CMouseHook();
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