//Renderer.cpp

#include "Renderer.h"
#include "GLRenderer.h"
#include "GLWindow.h"
#include "GLCamera.h"

std::unique_ptr<Renderer> Renderer::Create(GLWindow& window, unsigned int windowWidth, unsigned int windowHeight, GLCamera& cameraArg)
{
    // Get the window dimensions from the window object
    unsigned int width = window.GetWidth();
    unsigned int height = window.GetHeight();

    // Create and initialize the GLCamera object with default values
    GLCamera camera;

    return std::make_unique<GLRenderer>(window, width, height, cameraArg);
}



void InitializeRenderingObjects(GLWindow& window)
{
    unsigned int windowWidth = window.GetWidth();
    unsigned int windowHeight = window.GetHeight();

    // Create and initialize the GLCamera object
    GLCamera camera(/* initialization parameters */);

    // Create a GLRenderer object with the required arguments
    std::shared_ptr<GLRenderer> renderer = std::make_shared<GLRenderer>(window, windowWidth, windowHeight, camera);
}



void Renderer::Cleanup()
{
    this->~Renderer();
}