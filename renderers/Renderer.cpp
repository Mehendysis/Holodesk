//Renderer.cpp
#include "Renderer.h"
#include "GLRenderer.h"

std::unique_ptr<Renderer> Renderer::Create(Window& window)
{
    return std::make_unique<GLRenderer>(window);
}
