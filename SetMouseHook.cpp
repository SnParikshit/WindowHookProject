#include "SetMouseHook.h"
#include "WindowHook.h"
#include<iostream>

void CSetMouseHook::SetMouseHook()
{
    HHOOK mouseHook = SetWindowsHookEx(WH_MOUSE_LL, CWindowHook::WindowHookProc, GetModuleHandle(NULL), 0);
    if (mouseHook == NULL) {
        DWORD error = GetLastError();
        std::cerr << "Failed to set up the mouse hook. Error code: " << error << std::endl;
    }
    else {
        m_pMousehook->SetWindowHook(mouseHook);
        std::cout << "Mouse hook successfully set up. Press Enter to exit." << std::endl;
    }
}

void CSetMouseHook::UnHookMouse()
{
    // Unhook the mouse hook
        if (m_pMousehook != NULL) {
            HHOOK mouseHook = m_pMousehook->GetWindowHook();
            if (mouseHook != NULL)
            {
                UnhookWindowsHookEx(mouseHook); 
                mouseHook = NULL;
            }
            m_pMousehook = NULL;
        }
}
