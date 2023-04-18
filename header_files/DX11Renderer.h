// DX11Renderer.h
#pragma once

#include <Windows.h>
#include <DirectXMath.h>
#include <dxgi1_6.h>
#include <d3d11.h>
#include <d3d12.h>
#include <wrl.h>

#include "Camera.h"
#include "DX11Camera.h"

class DX11Renderer
{
public:
    DX11Renderer(HWND& window);
    ~DX11Renderer();
    bool DX11Initialize(HWND& window, unsigned short int windowWidth, unsigned short int windowHeight, DX11Camera& camera);
    void Render();
    void CleanUp();

    void Clear();
    void Present();
    void SetClearColor(const float r, const float g, const float b, const float a);

private:
    HWND& m_DXWindow;
    HWND m_windowHandle;
    ID3D11Device* m_device;
    ID3D11DeviceContext* m_deviceContext;
    IDXGISwapChain* m_swapChain;
    ID3D11RenderTargetView* m_renderTargetView;
    ID3D11DepthStencilView* m_depthStencilView;
    bool m_isInitialized;
    DirectX::XMVECTORF32 m_clearColor;
};