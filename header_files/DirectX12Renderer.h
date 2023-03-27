//DirectX12Renderer.h
#include <d3d12.h>
#include <d3dx12.h>
#include <Renderer.h>
#include <wrl/client.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <comdef.h>

using Microsoft::WRL::ComPtr;

// Declare types
struct Viewport
{
    float TopLeftX;
    float TopLeftY;
    float Width;
    float Height;
    float MinDepth;
    float MaxDepth;
};

struct ScissorRect
{
    LONG Left;
    LONG Top;
    LONG Right;
    LONG Bottom;
};

class DirectX12Renderer : public Renderer 
{
public:
    DirectX12Renderer(Window& window);
    virtual ~DirectX12Renderer();

    void Initialize() override;
private:
    bool m_vsync;
    RECT m_outputSize;
    Viewport m_viewport;
    ScissorRect m_scissorRect;
    HANDLE m_fenceEvent;
    Window& m_window;
    HRESULT m_hr;

    ComPtr<ID3D12Device> m_device;
    ComPtr<ID3D12CommandQueue> m_commandQueue;
    ComPtr<IDXGISwapChain4> m_swapChain;
    ComPtr<ID3D12Resource> m_renderTargets[2];
    ComPtr<ID3D12CommandAllocator> m_commandAllocator;
    ComPtr<ID3D12GraphicsCommandList> m_commandList;
    ComPtr<ID3D12Resource> m_depthStencilBuffer;
    ComPtr<ID3D12Resource> m_backBuffers[2];
    ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
    ComPtr<ID3D12DescriptorHeap> m_dsvHeap;
    ComPtr<ID3D12Fence> m_fence;
    ComPtr<IDXGIFactory4> m_dxgiFactory;

    D3D12_CPU_DESCRIPTOR_HANDLE m_renderTargetView;
    D3D12_CPU_DESCRIPTOR_HANDLE m_depthStencilView;


    UINT m_rtvDescriptorSize;
    UINT m_backBufferIndex;
    UINT m_dsvDescriptorSize;
    UINT m_width;
    UINT m_height;
    UINT64 m_fenceValue;

    HWND m_windowHandle;
    HWND m_hwnd;

    CD3DX12_RESOURCE_BARRIER m_barrier;
    CD3DX12_CPU_DESCRIPTOR_HANDLE m_rtvHandle;
    CD3DX12_CPU_DESCRIPTOR_HANDLE m_dsvHandle;
    CD3DX12_CPU_DESCRIPTOR_HANDLE m_rtvHandleOMSet;
    CD3DX12_CPU_DESCRIPTOR_HANDLE m_dsvHandleOMSet;

    void SwapChainExists();
    void SetCommandAllocator();
    void PointerToAllocatorCOMInterface();
    void DX12CommandListForRecCMD();
    void CheckCMDList();
    void DrawScene();
    void ResourceBarrierTransRenderTarget();
    void CheckDesciptorHeap();
    void DefineDescriptorSizes();
    void GetRenderTargetViewHandle();
    void RetrievesDescriptorHandle();
    void HandleBackBufferIndex();
    void SetCommandList();
    void CheckTargetViewDepthStencilWidthHeightCMDAllocator();
    void CheckResource();
    void CheckIfSupportD3D12Feature();
    void SignalCMDQeue();
    void WaitForFenceValue();
    void ResetFenceValue();
    void ResetCMDAllocator();
    void ResetCMDList();
    void ResetCMDListUsingAllocator();
    void SetRenderTargetAndDepthStencilView();
    void SetRenderTargetViews();
    void SetResourceBarrierTransitionState();
    void AddResourceBarrierToCommandList();
    void TransRenderTargetToRenderState();
    void TransDepthStencilToReadState();
    void ResourceBarrierToTransRenderTargetState();
    void ResourceBarrierToTransitionDepthStencilBufferState();
    void CloseCMDList();
    void ExecuteCMDList();
    void Present();
    void SetViewerAndScissorRect();
    void SetScissorRect();
    void CheckCMDAllocator();
    void CheckCMDListAndReset();
    void Render() override;
    void CleanUp() override;
    void Draw() {}
    void WaitForPreviousFrame();
    void CalculDescrHandlForRenderTargDepthStencil();
    void SetRenderTargDepthStencilView();
    void ClearRenderTargetDepthStencil();
    void GetBackBuffIndex();
};

inline void ThrowIfFailed(HRESULT hr);