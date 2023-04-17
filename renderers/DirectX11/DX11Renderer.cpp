// DX11Renderer.cpp

#include "DX11Renderer.h"
#include "Camera.h"

#include <Debug.h>
#include <DirectXMath.h>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <chrono>

using namespace std;

DX11Renderer::DX11Renderer(HWND& window) : m_DXWindow(window)
{

}

DX11Renderer::~DX11Renderer()
{
	if (m_swapChain)
	{
		m_swapChain->SetFullscreenState(FALSE, nullptr);
	}
}

bool DX11Renderer::DX11Initialize(HWND& window, unsigned int windowWidth, unsigned int windowHeight, Camera& camera) noexcept
{
	return false;
}

void InitializeRenderingObjects(HWND& window)
{
	//unsigned int windowWidth = DXWindow.GetWidth();
	//unsigned int windowHeight = DXWindow.GetHeight();

	// Create and initialize the DirectXCamera object
	//DXCamera camera;

	// Create a DirectXRenderer object with the required arguments
	//renderer = std::make_shared<DXRenderer>(windowWidth, windowHeight, camera);
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