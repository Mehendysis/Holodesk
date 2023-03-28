// OpenGLRenderer.cpp
#include "OpenGLRenderer.h"
#include <windows.h>
#include <GL/gl.h>

// In the OpenGLRenderer class:
void OpenGLRenderer::Initialize() 
{
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
}

void OpenGLRenderer::Render() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Render your 3D scene here
}

void OpenGLRenderer::CleanUp()
{
}
