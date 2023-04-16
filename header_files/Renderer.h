// Renderer.h
#pragma once
#include "GLCamera.h"
#include "Window.h"
#include <memory>

class GLRenderer;
class GLCamera;

class Renderer {
public:
    Renderer(Window* window) : m_window(window) {}
    virtual ~Renderer() {};
    virtual void Render() = 0;
    static std::unique_ptr<Renderer> Create(unsigned int windowWidth, unsigned int windowHeight, Camera& camera);
    virtual void CleanUp() = 0;
    virtual void* GetContext() const = 0;
    virtual void GL3DViewport() = 0;
    virtual Camera& GetCamera() = 0;
    virtual void DrawIndexed(unsigned int count, unsigned int start_index, unsigned int base_vertex) = 0;
    Window* GetWindow() const;

protected:
    Window* m_window;
};
