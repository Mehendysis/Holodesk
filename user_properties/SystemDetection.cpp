//SystemDetection.cpp
#include "SystemDetection.h"
#include "Debug.h"
#include "GLMemoryWrapper.h"

//#include <glad/glad.h>
#include <stdio.h>
#include <d3d11.h>
#include <d3d12.h>
#include <dxgi1_6.h>

#pragma comment(lib, "dxgi.lib")

using namespace std;
bool m_useDirectX = false;

void SystemDetection::CheckOpenGLVersionSimplified()
{
    // Check OpenGL version
    const char* version = (const char*)glGetString(GL_VERSION);
    printf("OpenGL version: %s\n", version);
}

void SystemDetection::CheckOpenGLVersionAdvaced()
{
    const GLubyte* version = glGetString(GL_VERSION);
    if (version != nullptr)
    {
        printf("OpenGL version supported by the hardware: %s\n", version);
    }
    else
    {
        printf("Error: Unable to retrieve OpenGL version information\n");
    }
}

bool SystemDetection::CheckOpenglVersion()
{
    const GLubyte* version = glGetString(GL_VERSION);

    if (version == nullptr)
    {
        DEBUG_MSG("¢RMain.cpp : main() : Failed to get OpenGL version.");
        return false;
    }

    DEBUG_MSG("OpenGL version: ");
    cout << version;

    // Check if the version is at least 4.3
    int major, minor;
    if (sscanf_s((char*)version, " %d.%d", &major, &minor) != 2 || major < 4 || (major == 4 && minor < 3))
    {
        DEBUG_MSG("¢RMain.cpp : main() : OpenGL version 4.3 or higher is required.");
        return false;
    }

    return true;
}

void SystemDetection::OsDetection()
{
#ifdef _WIN32
    m_useDirectX = true;
#else
    m_useDirectX = false;
#endif
}

bool SystemDetection::isUsingDirectX()
{
    return m_useDirectX;
}

bool SystemDetection::isDirectX12FeatureLevelSupported()
{
    // Create the DirectX 12 device
    ID3D12Device* device;
    HRESULT hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));
    if (FAILED(hr))
    {
        return false;
    }

    // Check the feature level
    D3D12_FEATURE_DATA_FEATURE_LEVELS featureLevels = {};
    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_12_1;
    featureLevels.NumFeatureLevels = 1;
    featureLevels.pFeatureLevelsRequested = &featureLevel;
    hr = device->CheckFeatureSupport(D3D12_FEATURE_FEATURE_LEVELS, &featureLevels, sizeof(featureLevels));
    device->Release();

    // Check if the feature level is supported by the GPU
    if (FAILED(hr) || featureLevel > featureLevels.MaxSupportedFeatureLevel)
    {
        return false;
    }

    return true;
}

int SystemDetection::GetDirectX12Version()
{
    int directXVersion = 0;

    IDXGIFactory4* factory = nullptr;
    HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&factory));

    if (SUCCEEDED(hr))
    {
        ID3D12Device* device12 = nullptr;
        hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&device12));

        if (SUCCEEDED(hr))
        {
            directXVersion = 12;
            device12->Release();
        }

        factory->Release();
    }

    return directXVersion;
}

int SystemDetection::GetDirectX11Version()
{
    int directXVersion = 0;

    D3D_FEATURE_LEVEL featureLevels[] = {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1
    };

    D3D_FEATURE_LEVEL supportedFeatureLevel;
    ID3D11Device* device11 = nullptr;
    ID3D11DeviceContext* deviceContext = nullptr;

    HRESULT hr = D3D11CreateDevice(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        featureLevels,
        _countof(featureLevels),
        D3D11_SDK_VERSION,
        &device11,
        &supportedFeatureLevel,
        &deviceContext);

    if (SUCCEEDED(hr))
    {
        switch (supportedFeatureLevel)
        {
        case D3D_FEATURE_LEVEL_11_1:
        case D3D_FEATURE_LEVEL_11_0:
            directXVersion = 11;
            break;
        case D3D_FEATURE_LEVEL_10_1:
        case D3D_FEATURE_LEVEL_10_0:
            directXVersion = 10;
            break;
        case D3D_FEATURE_LEVEL_9_3:
        case D3D_FEATURE_LEVEL_9_2:
        case D3D_FEATURE_LEVEL_9_1:
            directXVersion = 9;
            break;
        default:
            directXVersion = 0; // Unknown version
        }

        deviceContext->Release();
        device11->Release();
    }

    return directXVersion;
}

int SystemDetection::GetDirectXVersion()
{
    int dx11Version = GetDirectX11Version();
    int dx12Version = GetDirectX12Version();

    if (dx12Version > 0) 
    {
        if (isDirectX12FeatureLevelSupported())
        {
			return dx12Version;
		}
        else
        {
			return dx11Version;
		}
    }
    else if (dx11Version > 0) 
    {
        return dx11Version;
    }
    else 
    {
        return 0; // DirectX is not supported
    }
}
