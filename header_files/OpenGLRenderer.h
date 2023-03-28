// OpenGLRenderer.h
#pragma once

#include "Renderer.h"

class OpenGLRenderer : public Renderer
{
public:
    OpenGLRenderer(Window& window) : Renderer(window) {}

    void Initialize() override;
    void Render() override;
    void CleanUp() override;
};
