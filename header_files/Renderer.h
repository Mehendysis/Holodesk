// Renderer.h
#pragma once
#include "GLDefaultCamera.h"
#include "Window.h"
#include <memory>

class GLDefaultCamera;
class Renderer {
public:
    Renderer(Window& window) : window_(window) {}
    virtual ~Renderer() {}

    virtual void Initialize() = 0;
    virtual void Render() = 0;
    virtual void CleanUp() = 0;

    virtual void* GetContext() const = 0; 

    static std::unique_ptr<Renderer> Create(Window& window);
    virtual void InitializeGL3DViewport(int width, int height) = 0;
    virtual void InitializeFBO(int width, int height) = 0;
    virtual void GL3DViewport() = 0;
    virtual GLDefaultCamera& GetCamera() = 0;


protected:
    Window& window_;
};
