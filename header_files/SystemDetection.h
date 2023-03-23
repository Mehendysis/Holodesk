#pragma once

#include <string>
using namespace std;

class SystemDetection
{
public:

    bool isUsingDirectX() const;

private:
    bool m_useDirectX;
    void OsDetection();
    void GetWindowsVersion();
};
