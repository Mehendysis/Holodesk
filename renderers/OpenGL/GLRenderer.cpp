// GLRenderer.cpp

#include "GLRenderer.h"
#include "HoloMath.h"
#include "ErrorCheck.h"
#include "GLWindow.h" 

#include <iostream>
#include <Eigen/Core>
#include <imgui.h>
#include <Debug.h>


using namespace std;
using namespace Eigen;


GLRenderer::GLRenderer(GLWindow& window, unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera)
    : Renderer(window), m_window(window), m_windowWidth(windowWidth), m_windowHeight(windowHeight), m_camera(camera)
{
    // Calculate the aspect ratio
    int width, height;
    m_window.GetWindowSize(&width, &height);
    m_aspectRatio = static_cast<float>(width) / static_cast<float>(height);

    // Update window size if it doesn't match the given dimensions
    if (windowWidth != width || windowHeight != height)
    {
        m_window.SetWindowSize(width, height);
    }
}

GLRenderer::~GLRenderer()
{
    glDeleteFramebuffers(1, &m_fbo);
    glDeleteTextures(1, &colorAttachment);
    glDeleteRenderbuffers(1, &depthStencilAttachment);
}

bool GLRenderer::Initialize(GLWindow& window, unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera)
{
    DEBUG_MSG("GLRenderer.cpp : Initialize() : Enters GLRenderer Initializer.");

    // Calculate the aspect ratio
    int width, height;
    window_.GetWindowSize(&width, &height);
    m_aspectRatio = static_cast<float>(width) / static_cast<float>(height);

    if (windowWidth != width || windowHeight != height)
    {
        window_.SetWindowSize(windowWidth, windowHeight);
    }

    // Initialize GLAD
    DEBUG_MSG("GLRenderer.cpp : Initialize() : Initialize GLAD.");
    if (!gladLoadGL())
    {
        cerr << "Error: GLAD failed to initialize" << endl;
        return false;
    }

    // Set up the shader program
    DEBUG_MSG("GLRenderer.cpp : Initialize() : Set up the shader program.");
    m_shaderProgram = make_unique<GLShaderProgram>();
    m_shaderProgram->LoadShader("path/to/vertex/shader", "path/to/fragment/shader");
    m_shaderProgram->Compile();
    m_shaderProgram->Link();
    m_shaderProgram->Use();

    // Initialize the framebuffer object
    DEBUG_MSG("GLRenderer.cpp : Initialize() : Initialize the framebuffer object.");
    InitializeFBO(m_fboWidth, m_fboHeight);

    return true;
}


void GLRenderer::InitializeFBO(int width, int height)
{
    DEBUG_MSG("GLRenderer.cpp : InitializeFBO() : Enters InitializeFBO().");
    m_fboWidth = width;
    m_fboHeight = height;
    m_aspectRatio = static_cast<float>(m_fboWidth) / static_cast<float>(m_fboHeight);

    // Set up the framebuffer object
    DEBUG_MSG("GLRenderer.cpp : InitializeFBO() : Set up the framebuffer object.");
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    // Create the texture attachment
    DEBUG_MSG("GLRenderer.cpp : InitializeFBO() : Create the texture attachment.");
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_fboWidth, m_fboHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

    // Create the render buffer object
    DEBUG_MSG("GLRenderer.cpp : InitializeFBO() : Create the render buffer object.");
    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_fboWidth, m_fboHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

    // Check if the framebuffer is complete
    DEBUG_MSG("GLRenderer.cpp : InitializeFBO() : Check if the framebuffer is complete.");
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        cout << "Error: Framebuffer is not complete" << endl;
    }

    // Unbind the framebuffer
    DEBUG_MSG("GLRenderer.cpp : InitializeFBO() : Unbind the framebuffer.");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    DEBUG_MSG("GLRenderer.cpp : InitializeFBO() : InitializeFBO() completed.");
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
    DEBUG_MSG("GLRenderer.cpp : Render() :Update the aspect ratio.");
    m_aspectRatio = static_cast<float>(m_windowWidth) / static_cast<float>(m_windowHeight);

    // Set up the projection matrix using GLM
    DEBUG_MSG("GLRenderer.cpp : Render() : Set up the projection matrix using GLM.");
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), m_aspectRatio, 0.1f, 100.0f);

    // Define the view matrix
    DEBUG_MSG("GLRenderer.cpp : Render() : Define the view matrix.");
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
 
    // Define the projection parameters
    DEBUG_MSG("GLRenderer.cpp : Render() : Define the projection parameters.");
    float fov = 45.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    float aspectRatio = m_aspectRatio;

    // Calculate the projection matrix
    DEBUG_MSG("GLRenderer.cpp : Render() : Calculate the projection matrix.");
    projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);

    // Set up the model-view-projection matrix
    DEBUG_MSG("GLRenderer.cpp : Render() : Set up the model-view-projection matrix.");
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 mvp = projection * view * model;

    // Corrected line: Get the program ID and use it with glUseProgram
    DEBUG_MSG("GLRenderer.cpp : Render() : Corrected line: Get the program ID and use it with glUseProgram.");
    GLuint programID = m_shaderProgram->GetProgramId();
    glUseProgram(m_shaderProgram->GetProgramId());
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram->GetProgramId(), "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram->GetProgramId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // Render the scene objects
    DEBUG_MSG("GLRenderer.cpp : Render() : Render the scene objects.");
    for (auto& object : m_sceneObjects)
    {
        DEBUG_MSG("GLRenderer.cpp : Render() : object->Render();");
        object.Render();
    }
   
    DEBUG_MSG("GLRenderer.cpp : Render() : Render function completed");
}

void GLRenderer::CleanUp()
{
}

void GLRenderer::SetFBO(unsigned int width, unsigned int height, unsigned int viewportWidth, unsigned int viewportHeight)
{
    m_fboWidth = width;
    m_fboHeight = height;
    m_windowWidth = viewportWidth;
    m_windowHeight = viewportHeight;
    m_aspectRatio = static_cast<float>(m_fboWidth) / static_cast<float>(m_fboHeight);

    // Create a new framebuffer object if it hasn't been created yet
    if (m_fbo == 0)
    {
        glm::mat4 view = glm::mat4(m_camera.GetViewMatrix());
        glm::mat4 projection;
        float fov = 45.0f;
        float nearPlane = 0.1f;
        float farPlane = 100.0f;

        float aspectRatio;
        if (viewportWidth > 0 && viewportHeight > 0)
        {
            aspectRatio = static_cast<float>(viewportWidth) / static_cast<float>(viewportHeight);
        }
        else
        {
            aspectRatio = 1.0f; // Or any other default value you prefer
        }

        projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);

        glUseProgram(m_shaderProgram->GetProgramId());
        glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram->GetProgramId(), "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram->GetProgramId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // Set the values of m_fboWidth and m_fboHeight
        m_fboWidth = width;
        m_fboHeight = height;

        // Check if the framebuffer is complete
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            cout << "Error: Framebuffer is not complete" << endl;
        }

        // Unbind the framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    // Bind the framebuffer and set the viewport to its size
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glViewport(0, 0, width, height);
}

void GLRenderer::BindFBO()
{
    // Bind the FBO
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    // Set the viewport to the size of the FBO
    glViewport(0, 0, m_width, m_height);
}

bool GLRenderer::RenderBuffer(const glm::mat4& viewProjection)
{
    DEBUG_MSG("GLRenderer.cpp : RenderBuffer() : Enters RenderBuffer().");

    // Bind the FBO for rendering
    DEBUG_MSG("GLRenderer.cpp : RenderBuffer() : Bind the FBO for rendering.");
    BindFBO();

    // Clear the color and depth buffers
    DEBUG_MSG("GLRenderer.cpp : RenderBuffer() : Clear the color and depth buffers.");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up the viewport and projection matrix
    DEBUG_MSG("GLRenderer.cpp : RenderBuffer() : Set up the viewport and projection matrix.");
    glViewport(0, 0, m_width, m_height);

    // Generate the projection matrix
    DEBUG_MSG("GLRenderer.cpp : RenderBuffer() : Generate the projection matrix.");
    glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)m_width / (float)m_height, 0.1f, 1000.0f);

    if (check_aspect_ratio_error(projection))
    {
        DEBUG_MSG("¢RGLRenderer.cpp : RenderBuffer() : Error: aspect ratio error detected.");
        return false;
    }

    // Set up the view matrix based on the camera's position and orientation
    DEBUG_MSG("GLRenderer.cpp : RenderBuffer() : Set up the view matrix based on the camera's position and orientation.");
    glm::vec3 cameraPos = m_camera.GetPosition();
    glm::vec3 cameraDir = m_camera.GetDirection();
    glm::vec3 cameraUp = m_camera.GetUp();
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraDir, cameraUp);

    // Set up the model matrix for the object being rendered
    DEBUG_MSG("GLRenderer.cpp : RenderBuffer() : Set up the model matrix for the object being rendered.");
    glm::mat4 model = glm::mat4(1.0f);

    // Set up the shader program
    DEBUG_MSG("GLRenderer.cpp : RenderBuffer() : Set up the shader program.");
    m_shaderProgram->Use();
    m_shaderProgram->SetUniform("viewProjection", viewProjection);
    m_shaderProgram->SetUniform("uProjection", projection);
    m_shaderProgram->SetUniform("uView", view);
    m_shaderProgram->SetUniform("uModel", model);

    // Render the objects in the scene
    DEBUG_MSG("GLRenderer.cpp : RenderBuffer() : Render the objects in the scene.");
    for (const auto& object : m_sceneObjects) 
    {
        object.Render();
    }

    // Unbind the FBO
    DEBUG_MSG("GLRenderer.cpp : RenderBuffer() : Unbind the FBO.");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return true;
}

void GLRenderer::GL3DViewport()
{
    DEBUG_MSG("GLRenderer.cpp : GL3DViewport() : Enters GL3DViewport().");

    // Bind the framebuffer object and set the viewport to the framebuffer size
    DEBUG_MSG("GLRenderer.cpp : GL3DViewport() : Bind the framebuffer object and set the viewport to the framebuffer size.");
    BindFBO();
    glViewport(0, 0, m_fboWidth, m_fboHeight);

    // Clear the color and depth buffers
    DEBUG_MSG("GLRenderer.cpp : GL3DViewport() : Clear the color and depth buffers.");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::vec3 glm_cameraPos(m_camera.GetPosition().x, m_camera.GetPosition().y, m_camera.GetPosition().z);
    glm::vec3 glm_cameraFront(m_camera.GetDirection().x, m_camera.GetDirection().y, m_camera.GetDirection().z);
    glm::vec3 glm_cameraUp(m_camera.GetUp().x, m_camera.GetUp().y, m_camera.GetUp().z);

    // Set up the camera
    DEBUG_MSG("GLRenderer.cpp : GL3DViewport() : Set up the camera.");
    glm::mat4 view = m_camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(m_fov), static_cast<float>(m_fboWidth) / static_cast<float>(m_fboHeight), m_nearPlane, m_farPlane);
    glm::mat4 viewProjection = projection * view;

    if (!check_aspect_ratio_error(projection))
    {
        DEBUG_MSG("¢RGLRenderer.cpp : GL3DViewport() : Failed to initialize the projection matrix.");
    }

    // Render the scene using the shader program
    DEBUG_MSG("GLRenderer.cpp : GL3DViewport() : Render the scene using the shader program.");
    m_shaderProgram->Use();
    m_shaderProgram->SetUniform("viewProjection", viewProjection);

    // Render scene geometry here using VAOs and draw calls
    DEBUG_MSG("GLRenderer.cpp : GL3DViewport() : Render scene geometry here using VAOs and draw calls.");
    RenderBuffer(viewProjection);

    // Unbind the framebuffer object and reset the viewport to the window size
    DEBUG_MSG("GLRenderer.cpp : GL3DViewport() : Unbind the framebuffer object and reset the viewport to the window size.");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, m_windowWidth, m_windowHeight);

    DEBUG_MSG("GLRenderer.cpp : GL3DViewport() :Completed.");
}

void GLRenderer::InitializeGL3DViewport(int width, int height)
{
    // Set the viewport dimensions
    glViewport(0, 0, width, height);

    // Initialize the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
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