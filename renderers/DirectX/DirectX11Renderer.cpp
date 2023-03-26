#include <d3d11.h>
#include <d3dx11.h>

#include "DirectX11Renderer.h"
#include <Debug.h>
#include <DirectXMath.h>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <chrono>

DirectX11Renderer::DirectX11Renderer(Window& window) : Renderer(window) {}

DirectX11Renderer::~DirectX11Renderer()
{
    if (m_swapChain)
    {
        m_swapChain->SetFullscreenState(FALSE, nullptr);
    }
}

void DirectX11Renderer::Initialize()
{
}

void DirectX11Renderer::Render()
{
}

void DirectX11Renderer::CleanUp()
{
}

void DirectX11Renderer::Clear()
{
    if (!m_isInitialized)
    {
        cerr << "Renderer has not been initialized" << endl;
        return;
    }
    m_deviceContext->ClearRenderTargetView(m_renderTargetView, reinterpret_cast<const float*>(&m_clearColor));
    m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void DirectX11Renderer::Present()
{
    if (!m_isInitialized)
    {
        cerr << "Renderer has not been initialized" << endl;
        return;
    }
    m_swapChain->Present(1, 0);
}

void DirectX11Renderer::SetClearColor(const float r, const float g, const float b, const float a)
{
    m_clearColor = DirectX::XMVECTORF32{ r, g, b, a };
}
