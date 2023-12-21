#include "WindowHook.h"
#include <iostream>
#include <Psapi.h>
#include <UIAutomation.h>
#include <variant>
#include <comutil.h>

HHOOK CWindowHook::m_hWindowHook = NULL;

LRESULT CALLBACK CWindowHook::WindowHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0 && wParam == WM_LBUTTONDOWN) {
        MSLLHOOKSTRUCT* pMouseStruct = reinterpret_cast<MSLLHOOKSTRUCT*>(lParam);
        int x = pMouseStruct->pt.x;
        int y = pMouseStruct->pt.y;

        GetFocusedElementInfo();
    }

    // Call the next hook in the hook chain
    return CallNextHookEx(m_hWindowHook, nCode, wParam, lParam);
}

void CWindowHook::GetFocusedElementInfo()
{
    CoInitialize(nullptr);

    // Initialize UI Automation
    IUIAutomation* pAutomation;
    if (SUCCEEDED(CoCreateInstance(CLSID_CUIAutomation, nullptr, CLSCTX_INPROC_SERVER, IID_IUIAutomation, (void**)&pAutomation))) {
        IUIAutomationElement* pRootElement;

        // Get the root element
        if (SUCCEEDED(pAutomation->GetRootElement(&pRootElement))) {
            IUIAutomationElement* pFocusedElement = nullptr;

            // Attempt to get the focused element with a delay
            for (int i = 0; i < 5; ++i) {
                Sleep(500); // Wait for 500 milliseconds between attempts
                if (SUCCEEDED(pAutomation->GetFocusedElement(&pFocusedElement))) {
                    if (pFocusedElement != nullptr) {
                        break; // Break the loop if focused element is obtained
                    }
                }
            }

            if (pFocusedElement != nullptr) {
                // Get the process ID of the focused element
                int processId;
                if (SUCCEEDED(pFocusedElement->get_CurrentProcessId(&processId))) {
                    // Get the process handle
                    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, static_cast<DWORD>(processId));

                    if (hProcess != nullptr) {
                        // Get the module file name
                        TCHAR szProcessName[MAX_PATH];
                        if (GetModuleFileNameEx(hProcess, nullptr, szProcessName, MAX_PATH)) {
                            std::wstring processName = szProcessName;
                            size_t lastSlashPos = processName.find_last_of(L"\\");
                            if (lastSlashPos != std::wstring::npos) 
                            {
                                processName = processName.substr(lastSlashPos + 1);
                            }
                            std::wcout << processName << L": ";
                            PrintElementInfo(pFocusedElement);
                        }

                        CloseHandle(hProcess);
                    }
                }

                // Release the focused element
                pFocusedElement->Release();
            }
            else {
                std::wcout << L"No focused element." << std::endl;
            }

            // Release the root element
            pRootElement->Release();
        }

        // Release UI Automation
        pAutomation->Release();
    }

    CoUninitialize();

}

void CWindowHook::PrintElementInfo(IUIAutomationElement* pElement)
{
    
    // Get the bounding rectangle of the element
    RECT boundingRect;
    if (SUCCEEDED(pElement->get_CurrentBoundingRectangle(&boundingRect))) 
    {
        std::wcout << L"{X=" << boundingRect.left << L", Y=" << boundingRect.top << L"}" << L": ";
    }

    if (pElement != nullptr)
    {
        // Get the name of the element
        BSTR name;
        if (SUCCEEDED(pElement->get_CurrentName(&name)))
        {
            std::wcout << name << std::endl;
            SysFreeString(name);
        }
    }
}
