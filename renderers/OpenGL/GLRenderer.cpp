// GLRenderer.cpp

#include "GLRenderer.h"
#include "GLWindow.h"
#include "GLShaderProgram.h"
#include "HoloMath.h"
#include "ErrorCheck.h"

#include <Debug.h>
#include <Eigen/Core>
#include <imgui.h>
#include <iostream>
#include <glad/glad.h>
#include <SDL.h>

using namespace std;
using namespace Eigen;

GLRenderer::GLRenderer(GLWindow& window, unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera)
    : Renderer(window), m_window(&window), m_windowWidth(windowWidth), m_windowHeight(windowHeight), m_camera(camera)
{
    // Update the aspect ratio
    UpdateAspectRatio(windowWidth, windowHeight);

    // Get the actual window size
    int actualWidth, actualHeight;
    m_window->GetWindowSize(&actualWidth, &actualHeight); 

    // Update window size if it doesn't match the desired dimensions
    if (windowWidth != actualWidth || windowHeight != actualHeight)
    {
        m_window->SetWindowSize(windowWidth, windowHeight);
    }
}


GLRenderer::~GLRenderer()
{
    //glDeleteFramebuffers(1, &m_fbo);
    glDeleteTextures(1, &colorAttachment);
    glDeleteRenderbuffers(1, &depthStencilAttachment);
}

bool GLRenderer::Initialize(GLWindow& window, SDL_Renderer* renderer, unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera)
{
    DEBUG_MSG("GLRenderer.cpp : Initialize() : Enters GLRenderer Initializer.");

    m_camera = camera;
    m_window = &window;

    // Initialize GLAD
    DEBUG_MSG("GLRenderer.cpp : Initialize() : Initialize GLAD.");
    if (!gladLoadGL())
    {
        DEBUG_MSG("¢RGLRenderer.cpp : Initialize() : Error: GLAD failed to initialize");
        return false;
    }

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        DEBUG_MSG("¢RGLRenderer.cpp : Initialize() : OpenGL error: ");
        std::cerr << err << std::endl;
    }

    // Set up the shader program
    DEBUG_MSG("GLRenderer.cpp : Initialize() : Set up the shader program.");
    m_shaderProgram = make_unique<GLShaderProgram>();

    bool shaderLoaded = m_shaderProgram->LoadShader("vertex_shaders/GLSL_files/unlit_vertex.glsl", "vertex_shaders/GLSL_files/unlit_fragment.glsl");

    if (!shaderLoaded)
    {
        DEBUG_MSG("¢RGLRenderer.cpp : Initialize() : Error loading shaders.");
        return false;
    }

    // Set the viewport
    DEBUG_MSG("GLRenderer.cpp : Initialize() : Set the viewport.");
    glViewport(0, 0, windowWidth, windowHeight);

    // Initialize the framebuffer object
    DEBUG_MSG("GLRenderer.cpp : Initialize() : Initialize the framebuffer object.");
    m_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, windowWidth, windowHeight);
    if (!m_texture)
    {
        DEBUG_MSG("¢RGLRenderer.cpp : Initialize() : Error: Failed to create texture");
        return false;
    }
    SDL_SetRenderTarget(renderer, m_texture);

    DEBUG_MSG("¢GGLRenderer.cpp : Initialize() : Initialize completed.");
    return true;
}


std::unique_ptr<Renderer> GLRenderer::Create(GLWindow& window, unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera)
{
    //// Get the window dimensions from the window object
    //unsigned int windowWidth = window.GetWidth();
    //unsigned int windowHeight = window.GetHeight();

    //// Create and initialize the GLCamera object with default values
    //GLCamera camera;

    //// Create and return a std::unique_ptr<GLRenderer> as a std::unique_ptr<Renderer>
    //return std::make_unique<GLRenderer>(window, windowWidth, windowHeight, camera);
    return std::make_unique<GLRenderer>(window, windowWidth, windowHeight, camera);
}

void GLRenderer::Render()
{
    DEBUG_MSG("GLRenderer.cpp : Render() : Enters Render().");

    // Clear the color and depth buffers
    DEBUG_MSG("GLRenderer.cpp : Render() : Clear the color and depth buffers.");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update the aspect ratio
    DEBUG_MSG("GLRenderer.cpp : Render() : Update the aspect ratio.");
    int width, height;
    m_window->GetWindowSize(&width, &height);
    UpdateAspectRatio(width, height);

    // Set up the projection matrix using GLM
    DEBUG_MSG("GLRenderer.cpp : Render() : Set up the projection matrix using GLM.");
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), m_aspectRatio, 0.1f, 100.0f);

    // Define the view matrix
    DEBUG_MSG("GLRenderer.cpp : Render() : Define the view matrix.");
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    // Set up the model-view-projection matrix
    DEBUG_MSG("GLRenderer.cpp : Render() : Set up the model-view-projection matrix.");
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 mvp = projection * view * model;

    // Get the program ID and use it with glUseProgram
    DEBUG_MSG("GLRenderer.cpp : Render() : Get the program ID and use it with glUseProgram.");
    GLuint programID = m_shaderProgram->GetProgramId();

    DEBUG_MSG("GLRenderer.cpp : Render() : Shader Program ID: ");
    cout << programID << endl;

    glUseProgram(programID);

    // Check if the program is active
    DEBUG_MSG("GLRenderer.cpp : Render() : Check if the program is active.");
    int currentProgramID;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgramID);
    if (currentProgramID != (int)programID) 
    {
        DEBUG_MSG("¢RGLRenderer.cpp : Render() : Error - the program is not active.");
    }

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        DEBUG_MSG("¢RGLRenderer.cpp : Render() : OpenGL error: ");
        std::cerr << err << std::endl;
    }

    // Check for errors after calling glUseProgram
    err = glGetError();
    if (err != GL_NO_ERROR)
    {
        DEBUG_MSG("¢RGLRenderer.cpp : Render() : Error after calling glUseProgram(): ");
        cout << err << endl;
    }

    // Set the view and projection matrices as uniform variables
    DEBUG_MSG("GLRenderer.cpp : Render() : Set the view and projection matrices as uniform variables.");
    glUniformMatrix4fv(glGetUniformLocation(programID, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(programID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // Render the scene objects
    DEBUG_MSG("GLRenderer.cpp : Render() : Render the scene objects.");
    for (auto& object : m_sceneObjects)
    {
        DEBUG_MSG("¢BGLRenderer.cpp : Render() : object->Render();");
        object.Render();
    }
   
    DEBUG_MSG("¢GGLRenderer.cpp : Render() : Render function completed");
}

void GLRenderer::CleanUp()
{
}

void GLRenderer::BindFramebuffer()
{
    // Create a framebuffer object
    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    // Attach a texture to the framebuffer
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    // Check for framebuffer completeness
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        // Handle framebuffer error
        printf("Framebuffer is not complete!\n");
        return;
    }

    // Render to the framebuffer
    glViewport(0, 0, m_width, m_height);
    glClear(GL_COLOR_BUFFER_BIT);
    // Render your scene here

    // Bind the default framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Render the framebuffer to the screen
    glViewport(0, 0, m_windowWidth, m_windowHeight);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, texture);
    //glUseProgram(screen_shader);
    // Render a full-screen quad to display the texture

    // Swap the window buffer
    SDL_GL_SwapWindow(m_window->GetSDLWindow());
}

void GLRenderer::GL3DViewport()
{
    DEBUG_MSG("GLRenderer.cpp : GL3DViewport() : Enters GL3DViewport().");

    // Bind the framebuffer object and set the viewport to the framebuffer size
    DEBUG_MSG("GLRenderer.cpp : GL3DViewport() : Bind the framebuffer object and set the viewport to the framebuffer size.");
    //BindFramebuffer();

    // Clear the color and depth buffers
    DEBUG_MSG("GLRenderer.cpp : GL3DViewport() : Clear the color and depth buffers.");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::vec3 glm_cameraPos(m_camera.GetPosition().x, m_camera.GetPosition().y, m_camera.GetPosition().z);
    glm::vec3 glm_cameraFront(m_camera.GetDirection().x, m_camera.GetDirection().y, m_camera.GetDirection().z);
    glm::vec3 glm_cameraUp(m_camera.GetUp().x, m_camera.GetUp().y, m_camera.GetUp().z);

    // Get the window dimensions using SDL
    int windowWidth, windowHeight;
    SDL_GetWindowSize(m_window->GetSDLWindow(), &windowWidth, &windowHeight);
    DEBUG_MSG("¢GWindow dimensions: width = ");
    cout << to_string(windowWidth) << endl;
    DEBUG_MSG("¢Gheight = ");
    cout << to_string(windowHeight) << endl;

    // Set up the camera
    DEBUG_MSG("GLRenderer.cpp : GL3DViewport() : Set up the camera.");
    glm::mat4 view = m_camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(m_fov), static_cast<float>(windowWidth) / static_cast<float>(windowHeight), m_nearPlane, m_farPlane);
    glm::mat4 viewProjection = projection * view;

    if (!check_aspect_ratio_error(projection))
    {
        DEBUG_MSG("¢RGLRenderer.cpp : GL3DViewport() : Failed to initialize the projection matrix.");
    }

    // Render the scene using the shader program
    DEBUG_MSG("GLRenderer.cpp : GL3DViewport() : Render the scene using the shader program.");
    m_shaderProgram->Use();
    m_shaderProgram->SetUniform("viewProjection", viewProjection);

    //// Render scene geometry here using VAOs and draw calls
    //DEBUG_MSG("GLRenderer.cpp : GL3DViewport() : Render scene geometry here using VAOs and draw calls.");
    //RenderBuffer(viewProjection);

    // Unbind the framebuffer object and reset the viewport to the window size
    DEBUG_MSG("GLRenderer.cpp : GL3DViewport() : Unbind the framebuffer object and reset the viewport to the window size.");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, m_windowWidth, m_windowHeight);

    DEBUG_MSG("GLRenderer.cpp : GL3DViewport() :Completed.");
}

void GLRenderer::InitializeGL3DViewport(int width, int height)
{
    // Update the aspect ratio
    UpdateAspectRatio(width, height);

    // Set the viewport dimensions
    glViewport(0, 0, width, height);

    // Initialize the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), m_aspectRatio, 0.1f, 100.0f);
    glLoadMatrixf(glm::value_ptr(projection));

    // Initialize the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

//void GLRenderer::GL2DViewport()
//{
//    // Bind the framebuffer object and set the viewport to the framebuffer size
//    BindFBO();
//    glViewport(0, 0, m_fboWidth, m_fboHeight);
//
//    // Clear the color and depth buffers
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    glm::mat4 view = glm::lookAt(m_camera.GetPosition(), m_camera.GetPosition() + m_camera.GetFront(), m_camera.GetUp());
//    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_fboWidth), 0.0f, static_cast<float>(m_fboHeight), m_nearPlane, m_farPlane);
//    glm::mat4 viewProjection = projection * view;
//
//    // Render the scene using the shader program
//    m_shaderProgram->Use();
//    m_shaderProgram->SetUniform("viewProjection", viewProjection);
//
//    // Render scene geometry here using VAOs and draw calls
//    RenderBuffer(viewProjection);
//
//    // Unbind the framebuffer object and reset the viewport to the window size
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//    glViewport(0, 0, m_windowWidth, m_windowHeight);
//}

void GLRenderer::DrawIndexed(unsigned int count, unsigned int start_index, unsigned int base_vertex)
{
    glDrawElementsBaseVertex(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)(start_index * sizeof(unsigned int)), base_vertex);
}

void GLRenderer::UpdateAspectRatio(int width, int height)
{
    m_aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    m_windowWidth = width;
    m_windowHeight = height;
}
