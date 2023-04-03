// GLRenderer.h
#pragma once

#include "Renderer.h"
#include "GLCamera.h"
#include "GLShaderProgram.h"
#include "GLSceneObject.h"

#include <memory>
#include <vector>

class GLRenderer : public Renderer
{
public:
    //GLRenderer(Window& window) : Renderer(window) {}
    GLRenderer(Window& window);
    ~GLRenderer();
    void Initialize() override;
    void initializeFrameBuffer(int width, int height);
    void Render() override;
    void CleanUp() override;
    void SetFBO(unsigned int width, unsigned int height, unsigned int viewportWidth, unsigned int viewportHeight);
    void InitializeFBO(int width, int height) override;
    void BindFBO();
    void RenderBuffer();
    void InitializeGL3DViewport(int width, int height) override;
    void GL3DViewport() override;
    void GL2DViewport();
    void DefaultCameraScene();
    virtual void* GetContext() const override { return SDL_GL_GetCurrentContext(); }
    GLCamera& GetCamera() override { return m_camera; }
    void DrawIndexed(unsigned int count, unsigned int start_index, unsigned int base_vertex) override;
    unsigned int GetTextureID() const { return m_texture; }

private:
    //unsigned int m_fbo = 0;
    unsigned int m_texture = 0;
    unsigned int m_rbo = 0;
    GLuint m_fbo = 0;
    GLuint colorAttachment = 0;
    GLuint depthStencilAttachment = 0;
    int m_width = 0;
    int m_height = 0;
    int m_fboWidth = 0;
    int m_fboHeight = 0;
    int m_windowWidth = 0;
    int m_windowHeight = 0;
    float m_aspectRatio = 1.0f;
    float m_fov = 60.0f;
    float m_nearPlane = 0.1f;
    float m_farPlane = 1000.0f;
    float m_cameraSpeed = 0.01f;
    GLCamera m_camera;
    std::vector<GLSceneObject> m_sceneObjects;
    std::unique_ptr<GLShaderProgram> m_shaderProgram;
    //std::vector<GLSceneObject> m_sceneObjects = {};
};