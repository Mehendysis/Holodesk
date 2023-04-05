// Renderer.h
#pragma once
#include "GLCamera.h"
#include "Window.h"
#include <memory>

class GLRenderer;
class GLCamera;

class Renderer {
public:
    Renderer(Window& window) : window_(window) {}
    virtual ~Renderer() {}

    virtual bool Initialize(GLWindow& window, unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera) = 0;

    virtual void Render() = 0;
    virtual void CleanUp() = 0;

    virtual void* GetContext() const = 0; 

    virtual std::unique_ptr<Renderer> Create(GLWindow& window, unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera);
    //virtual std::unique_ptr<Renderer> Create(GLWindow& window) = 0;
    //std::unique_ptr<Renderer> Create(GLWindow& window);
    //static std::unique_ptr<Renderer, void(*)(Renderer*)> Create(GLWindow& window);

    void Cleanup();
    virtual void InitializeGL3DViewport(int width, int height) = 0;
    virtual void InitializeFBO(int width, int height) = 0;
    virtual void GL3DViewport() = 0;
    virtual GLCamera& GetCamera() = 0;
    virtual void DrawIndexed(unsigned int count, unsigned int start_index, unsigned int base_vertex) = 0;


protected:
    Window& window_;
};
