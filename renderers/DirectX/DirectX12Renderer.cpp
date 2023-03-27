#include <d3d12.h>
#include <d3dx12.h>
#include <Windows.h>
#include "DirectX12Renderer.h"
#include <Debug.h>
#include <DirectXMath.h>
#include <vector>
#include <stdexcept>
#include <wrl.h>
#include <iostream>
#include <chrono>
#include <dxgi1_6.h>
#include <DirectX11Renderer.h>
#include <stdexcept>
#include <sstream>
#include <string>

using namespace std;
using namespace Microsoft::WRL;

DirectX12Renderer::DirectX12Renderer(Window& window)
    : Renderer(window)
    , m_vsync(true)
    , m_outputSize()
    , m_viewport()
    , m_scissorRect()
    , m_fenceEvent(nullptr)
    , m_device(nullptr)
    , m_commandQueue(nullptr)
    , m_swapChain(nullptr)
    , m_renderTargets{}
    , m_commandAllocator(nullptr)
    , m_commandList(nullptr)
    , m_depthStencilBuffer(nullptr)
    , m_backBuffers{}
    , m_rtvHeap(nullptr)
    , m_dsvHeap(nullptr)
    , m_fence(nullptr)
    , m_dxgiFactory(nullptr)
    , m_renderTargetView()
    , m_depthStencilView()
    , m_rtvDescriptorSize(0)
    , m_backBufferIndex(0)
    , m_width(0)
    , m_height(0)
    , m_dsvDescriptorSize(0)
    , m_fenceValue(0)
    , m_window(window)
    , m_hwnd(NULL)
    , m_hr(S_OK)
{
    GetClientRect(m_windowHandle, &m_outputSize);
}

DirectX12Renderer::~DirectX12Renderer()
{
    CleanUp();
}

inline void ThrowIfFailed(HRESULT hr)
{
    if (FAILED(hr))
    {
        stringstream ss;
        ss << "Failed with HRESULT: 0x" << hex << uppercase << hr;
        throw runtime_error(ss.str());
    }
}


void DirectX12Renderer::SwapChainExists()
{
    if (!m_swapChain)
    {
        // Check if swap chain exists
        DEBUG_MSG("DirectX12Renderer.cpp : Render() : Check if swap chain exists.");
        cerr << "Swap chain is null, cannot present frame" << endl;
        return;
    }
}

void DirectX12Renderer::GetBackBuffIndex()
{
    // Get current back buffer index
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Get current back buffer index.");
    m_backBufferIndex = m_swapChain->GetCurrentBackBufferIndex();
    if (!m_commandAllocator)
    {
        m_hr = m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_commandAllocator));
        if (FAILED(m_hr))
        {
            cerr << "Error: failed to create command allocator" << endl;
        }
    }
}

void DirectX12Renderer::SetCommandAllocator()
{
	// Create command allocator
	DEBUG_MSG("DirectX12Renderer.cpp : Render() : Create command allocator.");
    m_hr = m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_commandAllocator));
    if (FAILED(m_hr))
    {
		cerr << "Error creating command allocator: " << m_hr << endl;
		return;
	}
    else
    {
		cout << "Command allocator created successfully." << endl;
	}
}

void DirectX12Renderer::PointerToAllocatorCOMInterface()
{
	// Declares a smart pointer to a DirectX 12 command allocator COM interface
	DEBUG_MSG("DirectX12Renderer.cpp : Render() : Declares a smart pointer to a DirectX 12 command allocator COM interface.");
	ComPtr<ID3D12CommandAllocator> commandAllocator;
    m_hr = m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));
    if (FAILED(m_hr))
    {
        cerr << "Error creating command allocator: " << m_hr << endl;
        return;
    }
}

void DirectX12Renderer::DX12CommandListForRecCMD()
{
	// Creates a Direct3D 12 command list for recording rendering commands
	DEBUG_MSG("DirectX12Renderer.cpp : Render() : Creates a Direct3D 12 command list for recording rendering commands.");
    m_hr = m_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocator.Get(), nullptr, IID_PPV_ARGS(&m_commandList));
    if (FAILED(m_hr))
    {
		cerr << "Error creating command list: " << m_hr << endl;
		return;
	}
}

void DirectX12Renderer::CheckCMDList()
{
	// Checks command list
	DEBUG_MSG("DirectX12Renderer.cpp : Render() : Checks command list.");
	if (!m_commandList)
    { 
		cerr << "Error: command list is null" << endl;
		return;
	}
}

void DirectX12Renderer::SetCommandList()
{
	// Create command list
	DEBUG_MSG("DirectX12Renderer.cpp : Render() : Create command list.");
    PointerToAllocatorCOMInterface();
    DX12CommandListForRecCMD();
    CheckCMDList();    
}

void DirectX12Renderer::CheckTargetViewDepthStencilWidthHeightCMDAllocator()
{
	// Check that all resources are properly created
	DEBUG_MSG("DirectX12Renderer.cpp : Render() : Check that all resources are properly created and set before resetting the command list.");
    if (m_renderTargetView.ptr == 0 || m_depthStencilView.ptr == 0 || m_width == 0 || m_height == 0 || !m_commandAllocator)
    {
		cerr << "Error: resources are not properly created and set" << endl;
		return;
	}
}

// Check for required feature support
D3D12_FEATURE_DATA_D3D12_OPTIONS options = {};

void DirectX12Renderer::ResetCMDAllocator()
{
	// Reset the command allocator
	DEBUG_MSG("DirectX12Renderer.cpp : Render() : Reset the command allocator.");
    m_hr = m_commandAllocator->Reset();
	if (FAILED(m_hr))
    {
		cerr << "Error resetting command allocator: " << m_hr << endl;
		return;
	}
}

void DirectX12Renderer::ResetCMDList()
{
	// Reset the command list
	DEBUG_MSG("DirectX12Renderer.cpp : Render() : Reset the command list.");
    m_hr = m_commandList->Reset(m_commandAllocator.Get(), nullptr);
    if (FAILED(m_hr))
    {
		cerr << "Error resetting command list: " << m_hr << endl;
		return;
	}
}

void DirectX12Renderer::ResetCMDListUsingAllocator()
{
    // Resets the command list using the command allocator
	DEBUG_MSG("DirectX12Renderer.cpp : Render() : Reset the command allocator and command list.");
    HRESULT m_hr = m_commandList->Reset(m_commandAllocator.Get(), nullptr);
    if (FAILED(m_hr))
    {
        cerr << "Error resetting command list: " << m_hr << endl;
        return;
    }
}

void DirectX12Renderer::SetRenderTargetAndDepthStencilView()
{
    // Set the render target view and depth stencil view
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Set the render target view and depth stencil view.");
    m_commandList->OMSetRenderTargets(1, &m_renderTargetView, FALSE, &m_depthStencilView);
}


void DirectX12Renderer::SetViewerAndScissorRect()
{
    // Set the viewport and scissor rect
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Set the viewport and scissor rect.");
    const D3D12_VIEWPORT viewport = { 0.0f, 0.0f, static_cast<float>(m_width), static_cast<float>(m_height), 0.0f, 1.0f };
    m_commandList->RSSetViewports(1, &viewport);
}

void DirectX12Renderer::SetScissorRect()
{
	// Sets the scissor rectangle for the command list
	DEBUG_MSG("DirectX12Renderer.cpp : Render() : Sets the scissor rectangle for the command list.");
	const D3D12_RECT scissorRect = { 0, 0, static_cast<LONG>(m_width), static_cast<LONG>(m_height) };
	m_commandList->RSSetScissorRects(1, &scissorRect);
}

void DirectX12Renderer::CheckCMDAllocator()
{
    // Verify command allocator
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Verify command allocator.");
    if (!m_commandAllocator)
    {
        cerr << "Error: command allocator is null" << endl;
        return;
    }
    else
    {
        DEBUG_MSG("DirectX12Renderer.cpp : Render() : Command allocator already exists.");
    }
}

void DirectX12Renderer::CheckCMDListAndReset()
{
    // Checks if the command list is null
    if (!m_commandList)
    {
        SetCommandAllocator();
        ResetCMDListUsingAllocator();
        SetRenderTargetAndDepthStencilView();
        SetViewerAndScissorRect();
        SetScissorRect();
    }
    else
    {
        ResetCMDListUsingAllocator();
    }
}

void DirectX12Renderer::CalculDescrHandlForRenderTargDepthStencil()
{
	// Calculates the CPU descriptor handle for the render target view and depth stencil view based on the current back buffer index
	DEBUG_MSG("DirectX12Renderer.cpp : Render() : Set render target and depth stencil views.");
	auto m_rtvHandleOMSet = m_rtvHeap->GetCPUDescriptorHandleForHeapStart();
	m_rtvHandleOMSet.ptr += static_cast<unsigned long long>(m_backBufferIndex) * m_rtvDescriptorSize;
	auto dsvHandleOMSet = m_dsvHeap->GetCPUDescriptorHandleForHeapStart();
}

void DirectX12Renderer::SetRenderTargDepthStencilView()
{
	// Sets the render target view and depth stencil view with the calculated descriptor handle
	DEBUG_MSG("DirectX12Renderer.cpp : Render() : Set render target and depth stencil views.");
	m_commandList->OMSetRenderTargets(1, &m_rtvHandleOMSet, FALSE, &m_dsvHandleOMSet);
}

void DirectX12Renderer::ClearRenderTargetDepthStencil()
{
    // Clear render target and depth stencil
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Clear render target and depth stencil.");
    float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
    m_commandList->ClearRenderTargetView(m_rtvHandleOMSet, clearColor, 0, nullptr);
    m_commandList->ClearDepthStencilView(m_dsvHandleOMSet, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void DirectX12Renderer::DrawScene()
{
    // Draw the scene
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Draw the scene.");
    // TODO: Implement scene drawing
}

void DirectX12Renderer::ResourceBarrierTransRenderTarget()
{
    // Resource barrier to transition render target from render to present state
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Resource barrier to transition render target from render to present state.");
    CD3DX12_RESOURCE_BARRIER barrierTargetToPresent = CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[m_backBufferIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
    m_commandList->ResourceBarrier(1, &barrierTargetToPresent);
}

void DirectX12Renderer::CheckDesciptorHeap()
{
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Checks m_dsvHeap.");
    if (!m_dsvHeap)
    {
        cerr << "Error: m_dsvHeap is null" << endl;
        return;
    }

    DEBUG_MSG("DirectX12Renderer.cpp : Render() : m_dsvHeap checked.");
}

void DirectX12Renderer::DefineDescriptorSizes()
{
    // Define descriptor sizes
    UINT dsvDescriptorSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
    const UINT rtvDescriptorSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
}

void DirectX12Renderer::GetRenderTargetViewHandle()
{
    // Get render target view handle
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Get render target view handle.");
    m_dsvHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(m_dsvHeap->GetCPUDescriptorHandleForHeapStart());
    m_dsvHandle.Offset(m_dsvDescriptorSize * m_backBufferIndex);
}

void DirectX12Renderer::RetrievesDescriptorHandle()
{
    // Retrieves the CPU descriptor handle for the start of the render target view heap
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Retrieves the CPU descriptor handle for the start of the render target view heap.");
    m_rtvHandle = m_rtvHeap->GetCPUDescriptorHandleForHeapStart();
}

void DirectX12Renderer::HandleBackBufferIndex()
{
	// Handle for the current back buffer index
	DEBUG_MSG("DirectX12Renderer.cpp : Render() : Handle for the current back buffer index.");
    m_rtvHandle.ptr += static_cast<unsigned long long>(m_backBufferIndex) * m_rtvDescriptorSize;
}

void DirectX12Renderer::SetRenderTargetViews()
{
    // Create render target views
    for (UINT i = 0; i < 2; i++)
    {
        ComPtr<ID3D12Resource> backBuffer;
        ThrowIfFailed(m_swapChain->GetBuffer(i, IID_PPV_ARGS(&backBuffer)));
        m_device->CreateRenderTargetView(backBuffer.Get(), nullptr, m_rtvHandle);
        m_backBuffers[i] = backBuffer;

        m_rtvHandle.Offset(1, m_rtvDescriptorSize);
    }
}

void DirectX12Renderer::SetResourceBarrierTransitionState()
{
    // Create a resource barrier to transition the resource from one state to another
    m_barrier = CD3DX12_RESOURCE_BARRIER::Transition(
        m_renderTargets[m_backBufferIndex].Get(),
        D3D12_RESOURCE_STATE_PRESENT,
        D3D12_RESOURCE_STATE_RENDER_TARGET);
}

void DirectX12Renderer::AddResourceBarrierToCommandList()
{
    // Add the resource barrier to the command list
    m_commandList->ResourceBarrier(1, &m_barrier);
}

void DirectX12Renderer::TransRenderTargetToRenderState()
{
    // Transition render target to render state
    CD3DX12_RESOURCE_BARRIER barrierRenderTarget = CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[m_backBufferIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
    m_commandList->ResourceBarrier(1, &barrierRenderTarget);
}

void DirectX12Renderer::TransDepthStencilToReadState()
{
    // Transition depth stencil to read state
    CD3DX12_RESOURCE_BARRIER barrierDepthStencil = CD3DX12_RESOURCE_BARRIER::Transition(m_depthStencilBuffer.Get(), D3D12_RESOURCE_STATE_DEPTH_WRITE, D3D12_RESOURCE_STATE_DEPTH_READ);
    m_commandList->ResourceBarrier(1, &barrierDepthStencil);
    m_commandList->OMSetRenderTargets(1, &m_rtvHandle, FALSE, &m_dsvHandle);
}

void DirectX12Renderer::ResourceBarrierToTransRenderTargetState()
{
    // Resource barrier to transition render target from present to render state
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Resource barrier to transition render target from present to render state.");
    CD3DX12_RESOURCE_BARRIER presentToRenderTarget = CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[m_backBufferIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
    m_commandList->ResourceBarrier(1, &presentToRenderTarget);
}

void DirectX12Renderer::ResourceBarrierToTransitionDepthStencilBufferState()
{
    // Resource barrier to transition depth stencil buffer from write to read state
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Resource barrier to transition depth stencil buffer from write to read state.");
    CD3DX12_RESOURCE_BARRIER writeToReadDepth = CD3DX12_RESOURCE_BARRIER::Transition(m_depthStencilBuffer.Get(), D3D12_RESOURCE_STATE_DEPTH_WRITE, D3D12_RESOURCE_STATE_DEPTH_READ);
    m_commandList->ResourceBarrier(1, &writeToReadDepth);
}

void DirectX12Renderer::CloseCMDList()
{
    // Close the command list
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Close the command list.");
    m_commandList->Close();
}

void DirectX12Renderer::ExecuteCMDList()
{
    // Execute the command list
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Execute the command list.");
    ID3D12CommandList* ppCommandLists[] = { m_commandList.Get() };
    m_commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
}

void DirectX12Renderer::Present()
{
    // Present the frame
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Present the frame.");
    m_hr = m_swapChain->Present(0, 0);
}

void DirectX12Renderer::CheckResource()
{
    // Check for required feature support
    D3D12_FEATURE_DATA_D3D12_OPTIONS options = {};
}

void DirectX12Renderer::CheckIfSupportD3D12Feature()
{
    // Checks if the Direct3D 12 device supports a specific feature and stores the result in the HRESULT variable hr.
    m_hr = m_device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS, &options, sizeof(options));
    if (FAILED(m_hr))
    {
        cout << "Failed to check feature support." << endl;
    }

    if (options.ResourceBindingTier < D3D12_RESOURCE_BINDING_TIER_2)
    {
        cout << "GPU device does not support required feature level (Resource Binding Tier 2)." << endl;
    }
}

void DirectX12Renderer::SignalCMDQeue()
{
    // Signal the command queue to increment the fence value when it finishes executing the command list
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Signal the command queue to increment the fence value when it finishes executing the command list.");
    m_hr = m_commandQueue->Signal(m_fence.Get(), m_fenceValue);
    if (FAILED(m_hr)) {
        cerr << "Error signaling fence: " << m_hr << endl;
        return;
    }
    m_fenceValue++;
}

void DirectX12Renderer::WaitForFenceValue()
{
    // Wait for the GPU to finish executing the command list
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Wait for the GPU to finish executing the command list.");
    if (m_fence->GetCompletedValue() < m_fenceValue) {
        HANDLE eventHandle = CreateEvent(nullptr, FALSE, FALSE, nullptr);
        if (eventHandle == nullptr) {
            cerr << "Error creating event: " << GetLastError() << endl;
            return;
        }

        m_hr = m_fence->SetEventOnCompletion(m_fenceValue, eventHandle);
        if (FAILED(m_hr)) {
            cerr << "Error setting event on completion: " << m_hr << endl;
            CloseHandle(eventHandle);
            return;
        }

        WaitForSingleObject(eventHandle, INFINITE);
        CloseHandle(eventHandle);
    }
}

void DirectX12Renderer::ResetFenceValue()
{
    // Reset the command allocator
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Reset the command allocator.");
    m_hr = m_commandAllocator->Reset();
    if (FAILED(m_hr))
    {
        // Error resetting the command allocator, print the HRESULT and return
        cout << "Error resetting command allocator. HRESULT: " << m_hr << endl;
        return;
    }
}

void DirectX12Renderer::Render()
{
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Enters DirectX render function.");

    SwapChainExists();

    if (FAILED(m_hr))
    {
        cerr << "Error: failed to create swap chain" << endl;
    }

    GetBackBuffIndex();

    SetCommandAllocator();
    SetCommandList();

    //CheckTargetViewDepthStencilWidthHeightCMDAllocator();

    ResetCMDAllocator();
    ResetCMDList();
    //ResetCMDListUsingAllocator();

    CheckCMDListAndReset();
    CheckCMDAllocator();

    CalculDescrHandlForRenderTargDepthStencil();
    SetRenderTargDepthStencilView();
    ClearRenderTargetDepthStencil();

    DrawScene();
    ResourceBarrierTransRenderTarget();
    CheckDesciptorHeap();

    DefineDescriptorSizes();

    GetRenderTargetViewHandle();
    RetrievesDescriptorHandle();

    SetRenderTargetViews();
    SetResourceBarrierTransitionState();

    AddResourceBarrierToCommandList();

    //TransRenderTargetToRenderState();
    //TransDepthStencilToReadState();

    ResourceBarrierToTransRenderTargetState();
    ResourceBarrierToTransitionDepthStencilBufferState();

    CloseCMDList();
    ExecuteCMDList();

    Present();

    CheckIfSupportD3D12Feature();
    SignalCMDQeue();

    WaitForFenceValue();
    ResetFenceValue();
    DEBUG_MSG("DirectX12Renderer.cpp : Render() : Render function completed.");
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

void DirectX12Renderer::Initialize(HWND hwnd)
{
    DEBUG_MSG("DirectX12Renderer.cpp : Initialize() : Enters the DirectX initialize function.");

    // Store the HWND
    m_hwnd = hwnd;

    // Get the client rect
    GetClientRect(m_hwnd, &m_outputSize);
    m_width = m_outputSize.right - m_outputSize.left;
    m_height = m_outputSize.bottom - m_outputSize.top;

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

    // Check if the device was created successfully
    DEBUG_MSG("DirectX12Renderer.cpp : Initialize() : Check if the device was created successfully.");
    if (!m_device)
    {
        cout << "Device not created successfully" << endl;
        return;
    }

    // Set the feature support for the device
    DEBUG_MSG("DirectX12Renderer.cpp : Initialize() : Set the feature support for the device.");
    D3D12_FEATURE_DATA_D3D12_OPTIONS options = {};
    HRESULT result = m_device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS, &options, sizeof(options));
    if (FAILED(result))
    {
        // Error checking feature support
        cout << "Error checking feature support: " << result << endl;
        return;
    }

    // Create the command queue
    DEBUG_MSG("DirectX12Renderer.cpp : Initialize() : Create the command queue.");
    D3D12_COMMAND_QUEUE_DESC cqDesc = {};
    cqDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    cqDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    hr = m_device->CreateCommandQueue(&cqDesc, IID_PPV_ARGS(&m_commandQueue));
    if (FAILED(hr))
    {
        // Error creating command queue
        cout << "Error creating command queue: " << hr << endl;
        return;
    }

    // Create and initialize the fence object and value
    DEBUG_MSG("DirectX12Renderer.cpp : Initialize() : Create and initialize the fence object and value.");
    hr = m_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence));
    if (FAILED(hr)) {
        cerr << "Error creating fence: " << hr << endl;
        return;
    }
    m_fenceValue = 1;

    // Create the swap chain
    DEBUG_MSG("DirectX12Renderer.cpp : Initialize() : Create the swap chain.");
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.BufferCount = 2;
    swapChainDesc.Width = m_width;
    swapChainDesc.Height = m_height;
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
    swapChainDesc.Flags = 0;

    // Creates a DXGI factory object that generates other DXGI objects.
    DEBUG_MSG("DirectX12Renderer.cpp : Initialize() : Set DXGI Fatory, a DirectX graphics interface factory.");
    ComPtr<IDXGIFactory4> factory;
    hr = CreateDXGIFactory1(IID_PPV_ARGS(&factory));
    if (FAILED(hr))
    {
        cerr << "Error creating DXGI factory: " << hr << endl;
        return;
    }
    m_dxgiFactory = factory;

    if (!m_commandQueue)
    {
        cerr << "Error: m_commandQueue is null" << endl;
        return; // or handle the error appropriately
    }

    if (!m_hwnd)
    {
        cerr << "Error: m_hwnd is null" << endl;
        return; // or handle the error appropriately
    }

    if (swapChainDesc.Width == 0 || swapChainDesc.Height == 0)
    {
        cerr << "Error: swapChainDesc has invalid dimensions" << endl;
        return; // or handle the error appropriately
    }

    if (swapChainDesc.BufferCount == 0)
    {
        cerr << "Error: swapChainDesc has invalid buffer count" << endl;
        return; // or handle the error appropriately
    }

    // Creates a DirectX swap chain for the specified window using the provided DXGI factory, command queue, and swap chain description.
    DEBUG_MSG("DirectX12Renderer.cpp : Initialize() : Creates a DirectX swap chain for the  window using the provided DXGI factory.");
    ComPtr<IDXGISwapChain1> swapChain;
    ThrowIfFailed(m_dxgiFactory->CreateSwapChainForHwnd(
        m_commandQueue.Get(),
        m_hwnd,
        &swapChainDesc,
        nullptr,
        nullptr,
        &swapChain
    ));

    // Prevents DXGI from responding to the ALT+ENTER shortcut.
    DEBUG_MSG("DirectX12Renderer.cpp : Initialize() : Prevents DXGI from responding to the ALT+ENTER shortcut.");
    ThrowIfFailed(m_dxgiFactory->MakeWindowAssociation(m_hwnd, DXGI_MWA_NO_ALT_ENTER));
    ThrowIfFailed(swapChain.As(&m_swapChain));

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
    DEBUG_MSG("DirectX12Renderer.cpp : Initialize() : Query the swap chain for its back buffer.");
    auto backBuffer = Microsoft::WRL::ComPtr<ID3D12Resource>{};

    hr = m_swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
    if (FAILED(hr)) {
        cerr << "Failed to get back buffer from swap chain" << endl;
        return;
    }

    DEBUG_MSG("DirectX12Renderer.cpp : Initialize() : Initialize completed.");

}
