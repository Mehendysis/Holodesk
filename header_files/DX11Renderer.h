// DX11Renderer.h
#pragma once

#include <d3d11.h>
//#include <d3dx11.h>
//#include <d3dx10.h>
#include <Windows.h>
#include <DirectXMath.h>
#include <dxgi1_6.h>
#include <d3d12.h>
#include <wrl.h>
#include <Renderer.h>

class DX11Renderer : public Renderer
{
public:
    DX11Renderer(Window& window);
    virtual ~DX11Renderer();

    bool Initialize(Window& window, unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera) override;
    void Render() override;
    void CleanUp() override;

    void Clear();
    void Present();
    void SetClearColor(const float r, const float g, const float b, const float a);

private:
    HWND m_windowHandle;
    ID3D11Device* m_device;
    ID3D11DeviceContext* m_deviceContext;
    IDXGISwapChain* m_swapChain;
    ID3D11RenderTargetView* m_renderTargetView;
    ID3D11DepthStencilView* m_depthStencilView;
    bool m_isInitialized;
    DirectX::XMVECTORF32 m_clearColor;
};