#pragma once

#include <string>
using namespace std;

class SystemDetection
{
public:
    static bool isUsingDirectX();
    static void OsDetection();
    int GetDirectXVersion();

private:
    static bool m_useDirectX;

    int GetDirectX12Version();
    int GetDirectX11Version();
    bool isDirectX12FeatureLevelSupported();
};