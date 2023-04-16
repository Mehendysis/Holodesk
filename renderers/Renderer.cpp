//Renderer.cpp

#include "Renderer.h"
#include "GLRenderer.h"
#include "GLWindow.h"
#include "GLCamera.h"
#include "Debug.h"

#include <SDL.h>

void InitializeRenderingObjects(Window& window)
{
    unsigned int windowWidth = window.GetWidth();
    unsigned int windowHeight = window.GetHeight();

    // Create and initialize the GLCamera object
    GLCamera camera;

    // Create a GLRenderer object with the required arguments
    std::shared_ptr<GLRenderer> renderer = std::make_shared<GLRenderer>(windowWidth, windowHeight, camera);
}

void Renderer::CleanUp()
{
    this->~Renderer();
}

Window* Renderer::GetWindow() const
{
    DEBUG_MSG("Renderer.cpp : GetWindow() : Enters GetWindow()");
    return m_window;
}
