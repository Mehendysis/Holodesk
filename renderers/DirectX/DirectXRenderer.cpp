// DirectXREnderer.cpp
#include "DirectXRenderer.h"
#include <Debug.h>
#include <d3d12.h>
#include <dxgi1_6.h>

DirectXRenderer::DirectXRenderer(Window& window)
    : Renderer(window), // Call the Renderer constructor with the Window object
    m_windowHandle(static_cast<HWND>(window.GetNativeWindowHandle())) // Obtain the window handle and cast it to HWND
{
    Initialize();
}

DirectXRenderer::~DirectXRenderer()
{
    CleanUp();
}

void DirectXRenderer::Render()
{
    DEBUG_MSG("DirectXRenderer.cpp : Render() : Enters DirectX render function.");
    // Present the back buffer to the screen
    m_swapChain->Present(0, 0);
    DEBUG_MSG("DirectXRenderer.cpp : Render() : Presented the back buffer to the screen.");
}

void DirectXRenderer::CleanUp()
{
    if (m_deviceContext) {
        m_deviceContext->ClearState();
        m_deviceContext->Release();
        m_deviceContext = nullptr;
    }

    if (m_swapChain) {
        m_swapChain->Release();
        m_swapChain = nullptr;
    }

    if (m_device) {
        m_device->Release();
        m_device = nullptr;
    }
}

void DirectXRenderer::Initialize()
{
    DEBUG_MSG("DirectXRenderer.cpp : Initialize() : Enters the DirectX initialize function.");
    RECT rc;

    if (!IsWindow(m_windowHandle))
    {
        cerr << "Failed to get a valid window handle." << endl;

        DEBUG_MSG("DirectXRenderer.cpp : Initialize() : IsWindow(m_windowHandle) : Failed DirectX initialization.");
        return;
    }

    GetClientRect(m_windowHandle, &rc);
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;
    UINT factoryFlags = 0;

    DXGI_SWAP_CHAIN_DESC scd = {};
    scd.BufferDesc.Width = width;
    scd.BufferDesc.Height = height;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.BufferCount = 1;
    scd.OutputWindow = m_windowHandle;
    scd.Windowed = TRUE;
    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &scd,
        &m_swapChain,
        &m_device,
        nullptr,
        &m_deviceContext);

    if (FAILED(hr))
    {
        cerr << "Failed to create device and swap chain: " << hr << endl;

        DEBUG_MSG("DirectXRenderer.cpp : Initialize() : (FAILED(hr)) : Failed DirectX initialization.");
    }
    else
    {
        DEBUG_MSG("DirectXRenderer.cpp : Initialize() : DirectX initialized successfully.");
    }

    DEBUG_MSG("DirectXRenderer.cpp : Initialize() : Exits DirectX initialization.");
}