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
    GLRenderer(GLWindow& window, unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera);
    ~GLRenderer();
    virtual bool Initialize(GLWindow& window, unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera) override;
    virtual std::unique_ptr<Renderer> Create(GLWindow& window, unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera);

    void Render() override;
    void CleanUp() override;
    void BindFramebuffer();
    void InitializeGL3DViewport(int width, int height) override;
    void GL3DViewport() override;
    virtual void* GetContext() const override { return SDL_GL_GetCurrentContext(); }
    GLCamera& GetCamera() override { return m_camera; }
    void DrawIndexed(unsigned int count, unsigned int start_index, unsigned int base_vertex) override;
    SDL_Texture* GetTextureID() const { return m_texture; }
    void UpdateAspectRatio(int width, int height);

private:
    GLuint m_VAO, m_VBO;
    GLCamera& m_camera;
    GLWindow* m_window;
    SDL_Texture* m_texture;
    unsigned int m_rbo = 0;
    GLuint colorAttachment = 0;
    GLuint depthStencilAttachment = 0;
    int m_width = 0;
    int m_height = 0;
    float m_aspectRatio = 1.0f;
    unsigned int m_windowWidth;
    unsigned int m_windowHeight;
    float m_fov = 60.0f;
    float m_nearPlane = 0.1f;
    float m_farPlane = 1000.0f;
    float m_cameraSpeed = 0.01f;
    std::vector<GLSceneObject> m_sceneObjects;
    std::unique_ptr<GLShaderProgram> m_shaderProgram;

};