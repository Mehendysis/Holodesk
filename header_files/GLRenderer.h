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

    //GLRenderer(GLWindow* window, unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera);

    //GLRenderer(GLWindow& window, unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera);

    GLRenderer(GLWindow& window, unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera);

    ~GLRenderer();
    virtual bool Initialize(GLWindow& window, unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera) override;

    //virtual bool Initialize(GLWindow* window, unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera) override;

    //virtual bool Initialize(GLWindow* window, unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera);

    //virtual bool Initialize(GLWindow& window, unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera) override;
    //bool Initialize(GLWindow& window, unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera) override;

    void InitializeFBO(int width, int height) override;

    virtual std::unique_ptr<Renderer> Create(GLWindow& window, unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera);

    //virtual std::unique_ptr<Renderer> Create(GLWindow& window, unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera);
    //virtual std::unique_ptr<Renderer> Create(GLWindow& window) override;
    //std::unique_ptr<GLRenderer> Create(GLWindow& window, unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera);
   
    void Render() override;
    void CleanUp() override;
    void SetFBO(unsigned int width, unsigned int height, unsigned int viewportWidth, unsigned int viewportHeight);
    
    void BindFBO();
    bool RenderBuffer(const glm::mat4& viewProjection);
    void InitializeGL3DViewport(int width, int height) override;
    void GL3DViewport() override;
    //void GL2DViewport();
    virtual void* GetContext() const override { return SDL_GL_GetCurrentContext(); }
    GLCamera& GetCamera() override { return m_camera; }
    void DrawIndexed(unsigned int count, unsigned int start_index, unsigned int base_vertex) override;
    unsigned int GetTextureID() const { return m_texture; }

private:
    GLCamera& m_camera;
    GLWindow& m_window;
    unsigned int m_texture = 0;
    unsigned int m_rbo = 0;
    GLuint m_fbo = 0;
    GLuint colorAttachment = 0;
    GLuint depthStencilAttachment = 0;
    int m_width = 0;
    int m_height = 0;
    int m_fboWidth = 0;
    int m_fboHeight = 0;

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