// OpenGLRenderer.h
#pragma once

#include "Renderer.h"

class OpenGLRenderer : public Renderer
{
public:
    OpenGLRenderer(Window& window) : Renderer(window) {}
    ~OpenGLRenderer();
    void Initialize() override;
    void Render() override;
    void CleanUp() override;
    void SetFBO(unsigned int width, unsigned int height);
    void BindFBO();
    void RenderBuffer();
    void GL3DViewport();
    void GL2DViewport();
    void CameraScene();
    virtual void* GetContext() const override { return SDL_GL_GetCurrentContext(); }

private:
    ShaderProgram m_shaderProgram;
    std::vector<SceneObject*> m_sceneObjects;
    Mesh m_mesh;
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
    glm::vec3 m_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    float m_cameraSpeed = 0.01f;
};

#endif // OPENGL_RENDERER_H