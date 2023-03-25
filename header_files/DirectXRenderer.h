//DirectXRenderer.h
#include <d3d11.h>
#include <Renderer.h>
#pragma comment (lib, "d3d11.lib")

class DirectXRenderer : public Renderer {
public:
    DirectXRenderer(Window& window);
    virtual ~DirectXRenderer();

    void Initialize() override;
    void Render() override;
    void CleanUp() override;

private:
    HWND m_windowHandle;
    ID3D11Device* m_device = nullptr;
    ID3D11DeviceContext* m_deviceContext = nullptr;
    IDXGISwapChain* m_swapChain = nullptr;
};