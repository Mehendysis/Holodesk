#include <iostream>
#include <Windows.h>

#include "SystemDetection.h"

using namespace std;

bool SystemDetection::m_useDirectX = false;

void SystemDetection::OsDetection()
{
#ifdef _WIN32
    cout << "This program is running on a Microsoft Windows system" << endl;
    m_useDirectX = true;
#else
    cout << "This program is not running on a Microsoft Windows system" << endl;
    m_useDirectX = false;
#endif
}

bool SystemDetection::isUsingDirectX()
{
    return m_useDirectX;
}

int SystemDetection::GetDirectXVersion()
{
    int directXVersion = 0;

    HMODULE hDxdiag = LoadLibraryA("dxdiag.dll");
    if (hDxdiag)
    {
        typedef HRESULT(WINAPI* LPFNDIRECTXSETUPGETVERSION)(UINT* pdwVersion, LPWSTR wszVersion, UINT cchVersion);
        LPFNDIRECTXSETUPGETVERSION pfnDirectXSetupGetVersion = (LPFNDIRECTXSETUPGETVERSION)GetProcAddress(hDxdiag, "DirectXSetupGetVersion");
        if (pfnDirectXSetupGetVersion)
        {
            UINT version = 0;
            WCHAR szDirectXVersion[32];
            if (SUCCEEDED(pfnDirectXSetupGetVersion(&version, szDirectXVersion, sizeof(szDirectXVersion))))
            {
                directXVersion = version / 100;
            }
        }
        FreeLibrary(hDxdiag);
    }

    return directXVersion;
}


void SystemDetection::GetWindowsVersion()
{
    OSVERSIONINFOEX osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    osvi.dwMajorVersion = 10; // Minimum supported Windows version

    DWORDLONG dwlConditionMask = 0;
    VER_SET_CONDITION(dwlConditionMask, VER_MAJORVERSION, VER_GREATER_EQUAL);

    if (VerifyVersionInfo(&osvi, VER_MAJORVERSION, dwlConditionMask))
    {
        cout << "Windows version: " << osvi.dwMajorVersion << "." << osvi.dwMinorVersion << "." << osvi.dwBuildNumber << endl;
    }
    else
    {
        cout << "Failed to get Windows version information" << endl;
    }
}