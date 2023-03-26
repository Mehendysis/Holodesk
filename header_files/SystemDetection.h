#pragma once

#include <string>
using namespace std;

class SystemDetection
{
public:
    static void OsDetection();
    static bool isUsingDirectX();

    int GetDirectXVersion();

private:
    static bool m_useDirectX;
    static void GetWindowsVersion();
};