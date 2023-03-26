//DirectX12Renderer.h
#include <d3d12.h>
#include <Renderer.h>
#include <wrl/client.h>
#include <dxgi1_5.h>
#include <wrl.h>
#include <comdef.h>

using Microsoft::WRL::ComPtr;


class DirectX12Renderer : public Renderer 
{
public:
    DirectX12Renderer(Window& window);
    virtual ~DirectX12Renderer();

    void Initialize() override;
    void Render() override;
    void CleanUp() override;
    void Draw() {}

private:
    HWND m_windowHandle;
    ComPtr<ID3D12Device> m_device;
    ComPtr<ID3D12CommandQueue> m_commandQueue;
    ComPtr<IDXGISwapChain4> m_swapChain;
    ComPtr<ID3D12Resource> m_renderTargets[2];
    ComPtr<ID3D12CommandAllocator> m_commandAllocator;
    ComPtr<ID3D12GraphicsCommandList> m_commandList;
    ComPtr<ID3D12Resource> m_depthStencilBuffer;

    ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
    UINT m_rtvDescriptorSize;
    ComPtr<ID3D12DescriptorHeap> m_dsvHeap;

    UINT m_dsvDescriptorSize;

    ComPtr<ID3D12Fence> m_fence;
    UINT64 m_fenceValue;
    HANDLE m_fenceEvent;

    //void CreateDevice();
    //void CreateCommandQueue();
    //void CreateSwapChain();
    //void CreateRenderTargets();
    //void CreateCommandList();
    //void CreateFence();
    void WaitForPreviousFrame();
};