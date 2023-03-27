// OpenGLRenderer.cpp

#include <Windows.h>
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "OpenGLRenderer.h"

void OpenGLRenderer::Initialize(GLFW glfw)
{
    m_glfw = glfw;
    // Initialize OpenGL context, shaders, etc. using window_ reference
}

void OpenGLRenderer::Render()
{
    // Render the scene using OpenGL
}

void OpenGLRenderer::CleanUp()
{
    // Make the rendering context inactive
    wglMakeCurrent(nullptr, nullptr);

    // Release the OpenGL rendering context
    if (m_openGLContext) {
        wglDeleteContext(m_openGLContext);
        m_openGLContext = nullptr;
    }

    // Release the device context
    if (m_deviceContext) {
        ReleaseDC(m_window.GetWindowHandle(), m_deviceContext);
        m_deviceContext = nullptr;
    }
}