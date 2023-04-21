// GLRenderer.h
#pragma once

#include "GLCamera.h"
#include "GLWindow.h"
#include "GLShaderProgram.h"
#include "GLSceneObject.h"

#include <SDL.h>

class GLRenderer
{
public:
    GLRenderer(unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera, GLWindow& window, SDL_GLContext& glContext);
    GLRenderer() = default;
    GLRenderer(const GLRenderer&) = default;
    ~GLRenderer();

    bool GLInitialize(unsigned short int windowWidth, unsigned short int windowHeight, GLCamera& camera, GLWindow* window);
    std::shared_ptr<GLRenderer> Create(unsigned short int windowWidth, unsigned short int windowHeight, GLCamera& camera, GLWindow& window, SDL_GLContext& glContext);
    void SetShaderProgramId(GLuint shaderProgramId);
    void Render();
    void CleanUp();
    void BindFramebuffer();
    void InitializeGL3DViewport(int width, int height);
    void GL3DViewport();
    void* GetContext() const { return SDL_GL_GetCurrentContext(); }
    void UpdateAspectRatio(int width, int height);
    void DrawIndexed(unsigned int count, unsigned int start_index, unsigned int base_vertex);

    GLCamera& GetCamera() { return m_glcamera; }
    
    SDL_Texture* GetTextureID() const { return m_texture; }
    void CallPrivateClean();

private:
    void PrivateClean();
    
    GLWindow& m_window;
    SDL_Texture* m_texture;
    SDL_GLContext m_glContext;
    GLCamera& m_glcamera;

    int m_width;
    int m_height;

    unsigned int m_windowWidth;
    unsigned int m_windowHeight;
    unsigned int m_rbo;

    GLuint m_VAO, m_VBO;
    GLuint colorAttachment;
    GLuint depthStencilAttachment;
    GLuint m_shaderProgramId;

    std::unique_ptr<GLShaderProgram> m_shaderProgram;


    float m_aspectRatio = 1.0f;
    float m_fov = 60.0f;
    float m_nearPlane = 0.1f;
    float m_farPlane = 1000.0f;
    float m_cameraSpeed = 0.01f;
    std::vector<GLSceneObject> m_sceneObjects;
    
};