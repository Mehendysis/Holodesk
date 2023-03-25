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
    WaitForPreviousFrame();

    CloseHandle(m_fenceEvent);
}

void DirectXRenderer::WaitForPreviousFrame() 
{
    const UINT64 fence = m_fenceValue;
    m_commandQueue->Signal(m_fence.Get(), fence);
    m_fenceValue++;

    if (m_fence->GetCompletedValue() < fence) 
    {
        m_fence->SetEventOnCompletion(fence, m_fenceEvent);
        WaitForSingleObject(m_fenceEvent, INFINITE);
    }
}

void DirectXRenderer::Initialize()
{
    DEBUG_MSG("DirectXRenderer.cpp : Initialize() : Enters the DirectX initialize function.");

    // Get the size of the window
    DEBUG_MSG("DirectXRenderer.cpp : Initialize() : Get the size of the window.");
    RECT rect;
    GetClientRect(m_windowHandle, &rect);
    UINT width = rect.right - rect.left;
    UINT height = rect.bottom - rect.top;

    // Create the device
    DEBUG_MSG("DirectXRenderer.cpp : Initialize() : Create the device.");
    HRESULT hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_device));
    if (FAILED(hr)) {
        cerr << "Failed to create D3D12 device" << endl;
        return;
    }

    // Create the command queue
    DEBUG_MSG("DirectXRenderer.cpp : Initialize() : Create the command queue.");
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    queueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.NodeMask = 0;
    hr = m_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_commandQueue));
    if (FAILED(hr)) {
        cerr << "Failed to create command queue" << endl;
        return;
    }

    // Create the swap chain
    DEBUG_MSG("DirectXRenderer.cpp : Initialize() : Create the swap chain.");
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.BufferCount = 2;
    swapChainDesc.Width = width;
    swapChainDesc.Height = height;
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.SampleDesc.Count = 1;

    ComPtr<IDXGIFactory4> factory;
    hr = CreateDXGIFactory1(IID_PPV_ARGS(&factory));
    if (FAILED(hr)) {
        cerr << "Failed to create DXGIFactory" << endl;
        return;
    }

    hr = factory->CreateSwapChainForHwnd(m_commandQueue.Get(), m_windowHandle, &swapChainDesc, nullptr, nullptr, reinterpret_cast<IDXGISwapChain1**>(m_swapChain.GetAddressOf()));
    if (FAILED(hr)) {
        cerr << "Failed to create swap chain" << endl;
        return;
    }
    DEBUG_MSG("DirectXRenderer.cpp : Initialize() : Initialize completed.");
}

//void DirectXRenderer::Initialize()
//{
//    DEBUG_MSG("DirectXRenderer.cpp : Initialize() : Enters the DirectX initialize function.");
//    RECT rc;
//
//    cout << "m_windowHandle : " << m_windowHandle << endl;
//
// /*   if (!IsWindow(m_windowHandle))
//    {
//        cerr << "Failed to get a valid window handle." << endl;
//
//        DEBUG_MSG("DirectXRenderer.cpp : Initialize() : IsWindow(m_windowHandle) : Failed DirectX initialization.");
//        return;
//    }*/
//
//    GetClientRect(m_windowHandle, &rc);
//    UINT width = rc.right - rc.left;
//    UINT height = rc.bottom - rc.top;
//    UINT factoryFlags = 0;
//
//    DXGI_SWAP_CHAIN_DESC scd = {};
//    scd.BufferDesc.Width = width;
//    scd.BufferDesc.Height = height;
//    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//    scd.BufferCount = 1;
//    scd.OutputWindow = m_windowHandle;
//    scd.Windowed = TRUE;
//    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
//
//    HRESULT hr = D3D11CreateDeviceAndSwapChain(
//        nullptr,
//        D3D_DRIVER_TYPE_HARDWARE,
//        nullptr,
//        0,
//        nullptr,
//        0,
//        D3D11_SDK_VERSION,
//        &scd,
//        &m_swapChain,
//        &m_device,
//        nullptr,
//        &m_deviceContext);
//
//    if (FAILED(hr))
//    {
//        cerr << "Failed to create device and swap chain: " << hr << endl;
//
//        DEBUG_MSG("DirectXRenderer.cpp : Initialize() : (FAILED(hr)) : Failed DirectX initialization.");
//    }
//    else
//    {
//        DEBUG_MSG("DirectXRenderer.cpp : Initialize() : DirectX initialized successfully.");
//    }
//
//    DEBUG_MSG("DirectXRenderer.cpp : Initialize() : Exits DirectX initialization.");
//}