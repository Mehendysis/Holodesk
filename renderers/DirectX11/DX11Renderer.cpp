// DX11Renderer.cpp

#include "DX11Renderer.h"

#include <Debug.h>
#include <DirectXMath.h>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <chrono>

using namespace std;

DX11Renderer::DX11Renderer(Window& window) : Renderer(&window), m_window(window)
{
	// DX11 initialization code
}

DX11Renderer::~DX11Renderer()
{
	if (m_swapChain)
	{
		m_swapChain->SetFullscreenState(FALSE, nullptr);
	}
}

bool DX11Renderer::DX11Initialize(Window& window, unsigned int windowWidth, unsigned int windowHeight, Camera& camera) noexcept
{
	return true;
}

void DX11Renderer::Render()
{
	// implementation for rendering goes here
}

void DX11Renderer::CleanUp()
{
}

void DX11Renderer::Clear()
{
	if (!m_isInitialized)
	{
		cerr << "Renderer has not been initialized" << endl;
		return;
	}
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, reinterpret_cast<const float*>(&m_clearColor));
	m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void DX11Renderer::Present()
{
	if (!m_isInitialized)
	{
		cerr << "Renderer has not been initialized" << endl;
		return;
	}
	m_swapChain->Present(1, 0);
}

void DX11Renderer::SetClearColor(const float r, const float g, const float b, const float a)
{
	m_clearColor = DirectX::XMVECTORF32{ r, g, b, a };
}