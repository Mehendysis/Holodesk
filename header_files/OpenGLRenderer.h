// OpenGLRenderer.h
#pragma once
#include <Renderer.h>
#include <Window.h>
#include <GLFW/glfw3.h>

class OpenGLRenderer : public Renderer
{
public:
    OpenGLRenderer(Window& window) : Renderer(window), m_window(window) {
        m_deviceContext = GetDC(static_cast<HWND>(window.GetNativeWindowHandle()));
        int pixelFormat = ChoosePixelFormat(m_deviceContext, &pfd);
        SetPixelFormat(m_deviceContext, pixelFormat, &pfd);
        m_openGLContext = wglCreateContext(m_deviceContext);
        wglMakeCurrent(m_deviceContext, m_openGLContext);
    }
    virtual ~OpenGLRenderer() {}

    virtual void Initialize(GLFW glfw) = 0;

    void Render() override;
    void CleanUp() override;

private:
    GLFW m_glfw
    Window& m_window;
    HDC m_deviceContext;
    HGLRC m_openGLContext;
    PIXELFORMATDESCRIPTOR pfd;
};
