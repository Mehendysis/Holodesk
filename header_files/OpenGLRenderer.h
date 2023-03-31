// OpenGLRenderer.h
#pragma once

#include "Renderer.h"
#include <GLDefaultSceneObject.h>
#include <GLDefaultCamera.h>
#include <GLShaderProgram.h>
#include <vector>

using namespace std;

class OpenGLRenderer : public Renderer
{
public:
    OpenGLRenderer(Window& window) : Renderer(window) {}
    ~OpenGLRenderer();
    void Initialize() override;
    void Render() override;
    void CleanUp() override;
    void SetFBO(unsigned int width, unsigned int height, unsigned int viewportWidth, unsigned int viewportHeight);
    void BindFBO();
    void RenderBuffer();
    void GL3DViewport();
    void GL2DViewport();
    void DefaultCameraScene();
    virtual void* GetContext() const override { return SDL_GL_GetCurrentContext(); }

private:
    unsigned int m_fbo = 0;
    unsigned int m_texture = 0;
    unsigned int m_rbo = 0;
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
    GLDefaultCamera m_camera;
    unique_ptr<GLShaderProgram> m_shaderProgram;
    vector<unique_ptr<SceneObject>> m_sceneObjects;
};

