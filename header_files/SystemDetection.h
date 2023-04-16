//SystemDetection.h

#pragma once

class SystemDetection
{
public:
    static void CheckOpenGLVersionSimplified();
    static void CheckOpenGLVersionAdvaced();
    static bool CheckOpenglVersion();

    static void OsDetection();

    static bool isUsingDirectX();
    static bool isDirectX12FeatureLevelSupported();
    static int GetDirectX12Version();
    static int GetDirectX11Version();
    static int GetDirectXVersion();
};
