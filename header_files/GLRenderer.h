// GLRenderer.h
#pragma once

#include "GLCamera.h"
#include "GLWindow.h"
#include "GLVertexArray.h"
#include "GLSceneObject.h"

#include <SDL.h>
#include <imgui.h>

class GLRenderer
{
public:
    GLRenderer(GLWindow* window, GLCamera* camera, GLuint shaderProgram, GLVertexArray* vertexOfArrayObject);
    ~GLRenderer();
    void SetCamera(GLCamera* camera);
    void RenderScene();
    void SetViewMatrixLocation(GLuint viewMatLoc);
    void SetProjectionMatrixLocation(GLuint projMatLoc);
    void SetViewportSize(float viewport_width, float viewport_height);
    void SetProjectionMatrix(const glm::mat4& projectionMatrix);
    void RenderCallback(ImDrawList* draw_list, const ImDrawCmd* cmd);

    //GLRenderer(unsigned int width, unsigned int height, GLCamera& camera, GLWindow& window, std::shared_ptr<SDL_GLContext> context);
//    bool GLInitialize(unsigned short int windowWidth, unsigned short int windowHeight, GLCamera& camera, GLWindow* window);
//    std::shared_ptr<GLRenderer> Create(unsigned short int windowWidth, unsigned short int windowHeight, GLCamera& camera, GLWindow& window, SDL_GLContext& glContext);
//    void SetShaderProgramId(GLuint shaderProgramId);
//    void Render();
//    void CleanUp();
//    void BindFramebuffer();
//    void InitializeGL3DViewport(int width, int height);
//    void GL3DViewport();
//    void* GetContext() const { return SDL_GL_GetCurrentContext(); }
//    void UpdateAspectRatio(int width, int height);
//    void DrawIndexed(unsigned int count, unsigned int start_index, unsigned int base_vertex);
//
//    GLCamera& GetCamera() { return m_glcamera; }
//    
//    SDL_Texture* GetTextureID() const { return m_texture; }
//    void CallPrivateClean();
//
private:
    GLCamera* m_glCamera;
    GLWindow* m_glWindow;
    GLuint m_shaderProgram;
    //GLuint m_vertexOfArrayObject;
    GLVertexArray* m_vao;

    GLint m_modelViewMatrixLocation;
    glm::mat4 m_modelViewMatrix;

    GLuint m_projectionMatrixLocation;
    glm::mat4 m_projectionMatrix;


//    void PrivateClean();
//    SDL_Texture* m_texture;
//    std::shared_ptr<SDL_GLContext> m_glContext;
//    GLCamera& m_glcamera;
//
//    int m_width;
//    int m_height;
//
//    unsigned int m_windowWidth;
//    unsigned int m_windowHeight;
//    unsigned int m_rbo;
//
//    GLuint m_VAO, m_VBO;
//    GLuint colorAttachment;
//    GLuint depthStencilAttachment;
//    GLuint m_shaderProgramId;
//
//    std::unique_ptr<GLShaderProgram> m_shaderProgram;
//
//
//    float m_aspectRatio = 1.0f;
//    float m_fov = 60.0f;
//    float m_nearPlane = 0.1f;
//    float m_farPlane = 1000.0f;
//    float m_cameraSpeed = 0.01f;
//    std::vector<GLSceneObject> m_sceneObjects;
//    
};