//DirectXRenderer.h
#include <d3d12.h>
#include <Renderer.h>
#include <wrl/client.h>
#include <dxgi1_5.h>

using Microsoft::WRL::ComPtr;


class DirectXRenderer : public Renderer {
public:
    DirectXRenderer(Window& window);
    virtual ~DirectXRenderer();

    void Initialize() override;
    void Render() override;
    void CleanUp() override;

private:
    HWND m_windowHandle;
    ComPtr<ID3D12Device> m_device;
    ComPtr<ID3D12CommandQueue> m_commandQueue;
    ComPtr<IDXGISwapChain4> m_swapChain;
    ComPtr<ID3D12Resource> m_renderTargets[2];
    ComPtr<ID3D12CommandAllocator> m_commandAllocator;
    ComPtr<ID3D12GraphicsCommandList> m_commandList;

    ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
    UINT m_rtvDescriptorSize;

    ComPtr<ID3D12Fence> m_fence;
    UINT64 m_fenceValue;
    HANDLE m_fenceEvent;

    void CreateDevice();
    void CreateCommandQueue();
    void CreateSwapChain();
    void CreateRenderTargets();
    void CreateCommandList();
    void CreateFence();
    void WaitForPreviousFrame();
};