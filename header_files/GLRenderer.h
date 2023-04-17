// GLRenderer.h
#pragma once

#include "GLCamera.h"
#include "GLShaderProgram.h"
#include "GLSceneObject.h"

#include <SDL.h>

class GLRenderer
{
public:
    GLRenderer(unsigned short int windowWidth, unsigned short int windowHeight, GLCamera& camera);
    ~GLRenderer();
    bool GLInitialize(unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera) noexcept;
    std::unique_ptr<GLRenderer> Create(unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera);

    void Render();
    void CleanUp();
    void BindFramebuffer();
    void InitializeGL3DViewport(int width, int height);
    void GL3DViewport();
    void* GetContext() const { return SDL_GL_GetCurrentContext(); }
    GLCamera& GetCamera() { return m_glcamera; }
    void DrawIndexed(unsigned int count, unsigned int start_index, unsigned int base_vertex);
    SDL_Texture* GetTextureID() const { return m_texture; }
    void UpdateAspectRatio(int width, int height);
private:

    GLCamera& m_glcamera;

    unsigned int m_windowWidth;
    unsigned int m_windowHeight;

    GLuint m_VAO, m_VBO;
    SDL_Texture* m_texture;
    unsigned int m_rbo;
    GLuint colorAttachment;
    GLuint depthStencilAttachment;
    int m_width;
    int m_height;
    float m_aspectRatio = 1.0f;
    float m_fov = 60.0f;
    float m_nearPlane = 0.1f;
    float m_farPlane = 1000.0f;
    float m_cameraSpeed = 0.01f;
    std::vector<GLSceneObject> m_sceneObjects;
    std::unique_ptr<GLShaderProgram> m_shaderProgram;

};