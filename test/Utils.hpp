#include <string>
#include <windows.h>
#include <TlHelp32.h>
#include <iostream>
using namespace std;
string GetFocused()
{
    // Get the handle of the foreground window
    HWND foregroundWindow = GetForegroundWindow();

    // Get the process ID of the foreground window
    DWORD processId;
    GetWindowThreadProcessId(foregroundWindow, &processId);

    // Get a handle to the process
    HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);

    // Get the process name
    char processName[MAX_PATH];
    if (GetModuleBaseNameA(processHandle, NULL, processName, MAX_PATH) == 0)
    {
        std::cout << "Tabbed Into: VRChat.exe" << std::endl;
        return "VRChat.exe";
    }

    // Print the process name
    std::cout << "Tabbed Into: " << processName << std::endl;

    // Close the process handle
    CloseHandle(processHandle);

    return processName;
}
string GetSpotify()
{
    HWND hwnd = FindWindowA("Chrome_WidgetWin_0", NULL); // get the handle of the first window with the specified class name
    char classname[256], title[256];
    while (hwnd != NULL) {
        GetClassNameA(hwnd, classname, 256); // get the class name of the window
        if (strcmp(classname, "Chrome_WidgetWin_0") == 0) { // check if the class name is correct
            GetWindowTextA(hwnd, title, 256); // get the window text
            if (title[0] != '\0') { // check if the window text is not null
                char* windowText = new char[strlen(title) + 1]; // allocate memory for the window text
                strcpy_s(windowText, sizeof(title), title); // copy the window text to the allocated memory
                return windowText; // return the window text as a char*
            }
        }
        hwnd = GetWindow(hwnd, GW_HWNDNEXT); // get the handle of the next window with the same class name
    }
    return NULL; // return NULL if no window with non-null text was found

    
}