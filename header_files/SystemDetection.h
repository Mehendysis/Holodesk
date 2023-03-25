#pragma once

#include <string>
using namespace std;

class SystemDetection
{
public:
    int Renderer();
    static void OsDetection();
    static bool isUsingDirectX();

private:
    static bool m_useDirectX;
    static void GetWindowsVersion();
};