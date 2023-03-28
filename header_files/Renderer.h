// Renderer.h
#pragma once

#include "Window.h"

class Renderer {
public:
    Renderer(Window& window) : window_(window) {}
    virtual ~Renderer() {}

    virtual void Initialize() = 0;
    virtual void Render() = 0;
    virtual void CleanUp() = 0;

    virtual void* GetContext() const = 0; 

protected:
    Window& window_;
};