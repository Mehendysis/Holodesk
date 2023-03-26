#include <d3d12.h>
#include <d3dx12.h>

#include "DirectX12Renderer.h"
#include <Debug.h>
#include <DirectXMath.h>
#include <vector>
#include <stdexcept>
#include <wrl.h>
#include <iostream>
#include <chrono>
#include <dxgi1_6.h>

DirectX12Renderer::DirectX12Renderer(Window& window)
    : Renderer(window),
    m_windowHandle(static_cast<HWND>(window.GetNativeWindowHandle())),
    m_rtvDescriptorSize(0),
    m_dsvDescriptorSize(0),
    m_fenceValue(0),
    m_fenceEvent(nullptr)
{
}

DirectX12Renderer::~DirectX12Renderer()
{
    CleanUp();
}

void DirectX12Renderer::Render()
{
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Enters DirectX render function.");
    // Check if swap chain exists
    if (!m_swapChain)
    {
        cerr << "Swap chain is null, cannot present frame" << endl;
        return;
    }

    // Get current back buffer index
    UINT backBufferIndex = m_swapChain->GetCurrentBackBufferIndex();

    if (!m_commandAllocator)
    {
        HRESULT hr = m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_commandAllocator));
        if (FAILED(hr))
        {
            cerr << "Error: failed to create command allocator" << endl;
            return;
        }
    }

    // Create command list
    ComPtr<ID3D12CommandAllocator> commandAllocator;
    ComPtr<ID3D12GraphicsCommandList> commandList;
    m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));
    m_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocator.Get(), nullptr, IID_PPV_ARGS(&commandList));

    // Create command allocator
    if (!m_commandAllocator)
    {
        cerr << "Error: m_commandAllocator is null" << endl;
        return;
    }

    HRESULT hr = m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_commandAllocator));
    if (FAILED(hr))
    {
        cerr << "Error creating command allocator: " << hr << endl;
        return;
    }
    else
    {
        cout << "Command allocator created successfully." << endl;
    }

    // Set render target and depth stencil views
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Set render target and depth stencil views.");
    auto rtvHandleOMSet = m_rtvHeap->GetCPUDescriptorHandleForHeapStart();
 //   rtvHandleOMSet.ptr += backBufferIndex * m_rtvDescriptorSize;
    rtvHandleOMSet.ptr += static_cast<unsigned long long>(backBufferIndex) * m_rtvDescriptorSize;
    auto dsvHandleOMSet = m_dsvHeap->GetCPUDescriptorHandleForHeapStart();
    if (!commandList)
    {
        cerr << "Error: commandList is null" << endl;
        return;
    }
    commandList->OMSetRenderTargets(1, &rtvHandleOMSet, FALSE, &dsvHandleOMSet);

    // Clear render target and depth stencil
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Clear render target and depth stencil.");
    float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
    commandList->ClearRenderTargetView(rtvHandleOMSet, clearColor, 0, nullptr);
    commandList->ClearDepthStencilView(dsvHandleOMSet, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

    // Draw the scene
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Draw the scene.");
    // TODO: Implement scene drawing

    // Resource barrier to transition render target from render to present state
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Resource barrier to transition render target from render to present state.");
    CD3DX12_RESOURCE_BARRIER barrierTargetToPresent = CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[backBufferIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
    commandList->ResourceBarrier(1, &barrierTargetToPresent);

    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Checks m_dsvHeap.");
    if (!m_dsvHeap)
    {
        cerr << "Error: m_dsvHeap is null" << endl;
        return;
    }

    DEBUG_MSG("DirectX12Renderer.cpp : Render() : m_dsvHeap checked.");

    // Define descriptor sizes
    UINT dsvDescriptorSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
    UINT rtvDescriptorSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    // Get render target view handle
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Get render target view handle.");
    CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(m_dsvHeap->GetCPUDescriptorHandleForHeapStart());
    dsvHandle.Offset(dsvDescriptorSize * backBufferIndex); // <-- use Offset member variable

    // Set render target and depth stencil views
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Set render target and depth stencil views.");
    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart());
    rtvHandle.Offset(backBufferIndex, rtvDescriptorSize); // <-- use Offset member variable

    // Create a resource barrier to transition the resource from one state to another
    CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
        m_renderTargets[backBufferIndex].Get(),
        D3D12_RESOURCE_STATE_PRESENT,
        D3D12_RESOURCE_STATE_RENDER_TARGET);

    // Add the resource barrier to the command list
    commandList->ResourceBarrier(1, &barrier);

    // Transition render target to render state
    CD3DX12_RESOURCE_BARRIER barrierRenderTarget = CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[backBufferIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
    commandList->ResourceBarrier(1, &barrierRenderTarget);

    // Transition depth stencil to read state
    CD3DX12_RESOURCE_BARRIER barrierDepthStencil = CD3DX12_RESOURCE_BARRIER::Transition(m_depthStencilBuffer.Get(), D3D12_RESOURCE_STATE_DEPTH_WRITE, D3D12_RESOURCE_STATE_DEPTH_READ);
    commandList->ResourceBarrier(1, &barrierDepthStencil);
    commandList->OMSetRenderTargets(1, &rtvHandle, FALSE, &dsvHandle);

    // Resource barrier to transition render target from present to render state
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Resource barrier to transition render target from present to render state.");
    CD3DX12_RESOURCE_BARRIER presentToRenderTarget = CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[backBufferIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
    commandList->ResourceBarrier(1, &presentToRenderTarget);

    // Resource barrier to transition depth stencil buffer from write to read state
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Resource barrier to transition depth stencil buffer from write to read state.");
    CD3DX12_RESOURCE_BARRIER writeToReadDepth = CD3DX12_RESOURCE_BARRIER::Transition(m_depthStencilBuffer.Get(), D3D12_RESOURCE_STATE_DEPTH_WRITE, D3D12_RESOURCE_STATE_DEPTH_READ);
    commandList->ResourceBarrier(1, &writeToReadDepth);

    // Close the command list
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Close the command list.");
    commandList->Close();

    // Execute the command list
    ID3D12CommandList* ppCommandLists[] = { commandList.Get() };
    m_commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

    // Present the frame
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Present the frame.");
    hr = m_swapChain->Present(0, 0);
    // Check for required feature support
    D3D12_FEATURE_DATA_D3D12_OPTIONS options = {};

    hr = m_device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS, &options, sizeof(options));
    if (FAILED(hr))
    {
        std::cout << "Failed to check feature support." << std::endl;
    }

    if (options.ResourceBindingTier < D3D12_RESOURCE_BINDING_TIER_2)
    {
        std::cout << "GPU device does not support required feature level (Resource Binding Tier 2)." << std::endl;
    }

    // Reset the command allocator
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Reset the command allocator.");
    hr = m_commandAllocator->Reset();
    if (FAILED(hr))
    {
        // Error resetting the command allocator, print the HRESULT and return
        std::cout << "Error resetting command allocator. HRESULT: " << hr << std::endl;
        return;
    }
}

void DirectX12Renderer::CleanUp() 
{
    WaitForPreviousFrame();

    CloseHandle(m_fenceEvent);
}

void DirectX12Renderer::WaitForPreviousFrame() 
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

void DirectX12Renderer::Initialize()
{
    DEBUG_MSG("DirectX12Renderer.cpp : Initialize() : Enters the DirectX initialize function.");

    // Get the size of the window
    DEBUG_MSG("DirectX12Renderer.cpp : Initialize() : Get the size of the window.");
    RECT rect;
    if (!GetClientRect(m_windowHandle, &rect)) {
        const auto error = GetLastError();
        cerr << "Failed to get client rect. Error code: " << error << endl;
        return;
    }
    UINT width = rect.right - rect.left;
    UINT height = rect.bottom - rect.top;
    if (width == 0 || height == 0) {
        cerr << "Invalid window size" << endl;
        return;
    }

    // Create the device
    DEBUG_MSG("DirectX12Renderer.cpp : Initialize() : Create the device.");
    auto hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_device));
    if (FAILED(hr)) {
        cerr << "Failed to create D3D12 device" << endl;
        return;
    }

    // Create the command queue
    DEBUG_MSG("DirectX12Renderer.cpp : Initialize() : Create the command queue.");
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

    hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_device));
    if (FAILED(hr))
    {
        // Error creating device
        std::cout << "Error creating device: " << hr << std::endl;
        return;
    }

    // Check if the device was created successfully
    if (!m_device)
    {
        std::cout << "Device not created successfully" << std::endl;
        return;
    }

    // Set the feature support for the device
    D3D12_FEATURE_DATA_D3D12_OPTIONS options = {};
    HRESULT result = m_device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS, &options, sizeof(options));
    if (FAILED(result))
    {
        // Error checking feature support
        std::cout << "Error checking feature support: " << result << std::endl;
        return;
    }

    // Create the command queue
    D3D12_COMMAND_QUEUE_DESC cqDesc = {};
    cqDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    cqDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    hr = m_device->CreateCommandQueue(&cqDesc, IID_PPV_ARGS(&m_commandQueue));
    if (FAILED(hr))
    {
        // Error creating command queue
        std::cout << "Error creating command queue: " << hr << std::endl;
        return;
    }

    // Create the swap chain
    DEBUG_MSG("DirectX12Renderer.cpp : Initialize() : Create the swap chain.");
    auto factory = Microsoft::WRL::ComPtr<IDXGIFactory4>{};
    hr = CreateDXGIFactory1(IID_PPV_ARGS(&factory));
    if (FAILED(hr)) {
        cerr << "Failed to create DXGIFactory" << endl;
        return;
    }
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.BufferCount = 2;
    swapChainDesc.Width = width;
    swapChainDesc.Height = height;
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.SampleDesc.Count = 1;
    hr = factory->CreateSwapChainForHwnd(m_commandQueue.Get(), m_windowHandle, &swapChainDesc, nullptr, nullptr, reinterpret_cast<IDXGISwapChain1**>(m_swapChain.GetAddressOf()));
    if (FAILED(hr)) {
        cerr << "Failed to create swap chain" << endl;
        return;
    }
    DXGI_SWAP_CHAIN_DESC desc;
    m_swapChain->GetDesc(&desc);
    cout << "Swap chain width: " << desc.BufferDesc.Width << endl;
    cout << "Swap chain height: " << desc.BufferDesc.Height << endl;
    cout << "Swap chain format: " << desc.BufferDesc.Format << endl;
    cout << "Swap chain buffer usage: " << desc.BufferUsage << endl;

    // Create the RTV heap
    DEBUG_MSG("DirectX12Renderer.cpp : Initialize() : Create the RTV heap.");
    D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
    rtvHeapDesc.NumDescriptors = 2;
    rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    hr = m_device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&m_rtvHeap));
    if (FAILED(hr)) {
        cerr << "Failed to create RTV heap" << endl;
        return;
    }
    m_rtvDescriptorSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);


    // Create the DSV heap
    DEBUG_MSG("DirectX12Renderer.cpp : Initialize() : Create the DSV heap.");
    D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
    dsvHeapDesc.NumDescriptors = 1;
    dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
    dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    hr = m_device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&m_dsvHeap));
    if (FAILED(hr)) {
        cerr << "Failed to create DSV descriptor heap" << endl;
        return;
    }

    // Query the swap chain for its back buffer
    auto backBuffer = Microsoft::WRL::ComPtr<ID3D12Resource>{};

    hr = m_swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
    if (FAILED(hr)) {
        cerr << "Failed to get back buffer from swap chain" << endl;
        return;
    }

    DEBUG_MSG("DirectX12Renderer.cpp : Initialize() : Initialize completed.");

}
