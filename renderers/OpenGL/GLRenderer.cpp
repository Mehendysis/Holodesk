// GLRenderer.cpp

#include "GLRenderer.h"
#include "GLWindow.h"
#include "Window.h"
#include "GLShaderProgram.h"
#include "HoloMath.h"
#include "ErrorCheck.h"
#include "Debug.h"
#include "GLMemoryWrapper.h"

#include <Eigen/Core>
#include <imgui.h>
#include <iostream>
//#include <glad/glad.h>
#include <SDL.h>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace Eigen;

GLRenderer::GLRenderer(unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera, GLWindow& window, SDL_GLContext& glContext) :
    m_windowWidth(windowWidth),
    m_windowHeight(windowHeight),
    m_glcamera(camera),
    m_window(window),
    m_glContext(glContext)
{
    // Initialize the OpenGL context and create the window
    DEBUG_MSG("@BGLRenderer.cpp : GLRenderer() : Initializing the OpenGL context and creating the window.");
    //m_glContext = SDL_GL_CreateContext(window->GetNativeWindowHandle());
    m_glContext = glContext;
    
    if (!m_glContext) 
    {
        DEBUG_MSG("¢RGLRenderer.cpp : GLRenderer() : Failed to create the OpenGL context.");
        cout << std::string(SDL_GetError());
        throw std::runtime_error("Failed to create the OpenGL context.");
    }
}


GLRenderer::~GLRenderer()
{
    glDeleteTextures(1, &colorAttachment);
    glDeleteRenderbuffers(1, &depthStencilAttachment);
}

bool GLRenderer::GLInitialize(unsigned short int windowWidth, unsigned short int windowHeight, GLCamera& camera, GLWindow* window)
{
    DEBUG_MSG("GLRenderer.cpp : Initialize() : Enters GLRenderer Initializer.");

    DEBUG_MSG("¢BGLRenderer.cpp : Initialize() : GL version: ");
    cout << GLVersion.major << "." << GLVersion.minor << endl;

    float vertices[] = {
        // positions        // colors
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // bottom left
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // bottom right
        0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f, // top
    };

    // In the initialization function
    DEBUG_MSG("GLRenderer.cpp : Initialize() : glGenVertexArrays.");
    glGenVertexArrays(1, &m_VAO);
    DEBUG_MSG("GLRenderer.cpp : Initialize() : glBindVertexArray.");
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set up vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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

    // Unbind the VAO
    glBindVertexArray(0);

    DEBUG_MSG("¢GGLRenderer.cpp : Initialize() : Initialize completed.");
    return true;
}

void InitializeRenderingObjects()
{
    //// Create and initialize the renderer object
    //Renderer* renderer = new Renderer();

    //// Create and initialize the camera object
    //Camera* camera = new Camera();

    //// Set up the viewport and camera projection
    //renderer->SetViewport(0, 0, windowWidth, windowHeight);
    //camera->SetProjection(FOV, aspectRatio, nearPlane, farPlane);

    //// Load shaders and set up materials
    //Shader* shader = ShaderLoader::LoadShader("standard");
    //Material* material = new Material(shader);
    //material->SetTexture("diffuseMap", TextureLoader::LoadTexture("diffuse.png"));

    //// Create and initialize meshes
    //Mesh* mesh = MeshLoader::LoadMesh("cube.obj");
    //mesh->SetMaterial(material);

    //// Create and initialize game objects
    //GameObject* gameObject = new GameObject(mesh, Transform(glm::vec3(0.0f, 0.0f, -5.0f)));

    //// Add game objects to the scene
    //Scene::AddGameObject(gameObject);

    //// Set up the lighting
    //renderer->SetAmbientLight(glm::vec3(0.2f, 0.2f, 0.2f));
    //PointLight* pointLight = new PointLight(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 0.09f, 0.032f);
    //renderer->AddLight(pointLight);
}



//std::shared_ptr<GLRenderer> GLRenderer::Create(unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera, GLWindow& window, SDL_GLContext& glContext)
//{
//    return std::make_shared<GLRenderer>(static_cast<unsigned short>(windowWidth), static_cast<unsigned short>(windowHeight), camera, window, glContext);
//}

std::shared_ptr<GLRenderer> GLRenderer::Create(unsigned short int windowWidth, unsigned short int windowHeight, GLCamera& camera, GLWindow& window, SDL_GLContext& glContext)
{
    return std::make_shared<GLRenderer>(windowWidth, windowHeight, camera, window, glContext);
}


void GLRenderer::Render()
{
    DEBUG_MSG("GLRenderer.cpp : Render() : Enters Render().");

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3); // Assuming you have a single triangle with 3 vertices
    glBindVertexArray(0); // Unbind the VAO

    // Clear the color and depth buffers
    DEBUG_MSG("GLRenderer.cpp : Render() : Clear the color and depth buffers.");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update the aspect ratio
    DEBUG_MSG("GLRenderer.cpp : Render() : Update the aspect ratio.");
    unsigned short int width, height;
    m_window.GetCurrentWindowSize(&width, &height);
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
    SDL_GL_SwapWindow(m_window.GetSDLWindow());
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

    glm::vec3 glm_glcameraPos(m_glcamera.GetPosition().x, m_glcamera.GetPosition().y, m_glcamera.GetPosition().z);
    glm::vec3 glm_glcameraFront(m_glcamera.GetDirection().x, m_glcamera.GetDirection().y, m_glcamera.GetDirection().z);
    glm::vec3 glm_glcameraUp(m_glcamera.GetUp().x, m_glcamera.GetUp().y, m_glcamera.GetUp().z);

    // Get the window dimensions using SDL
    int windowWidth, windowHeight;
    SDL_GetWindowSize(m_window.GetSDLWindow(), &windowWidth, &windowHeight);
    DEBUG_MSG("¢GWindow dimensions: width = ");
    cout << to_string(windowWidth) << endl;
    DEBUG_MSG("¢Gheight = ");
    cout << to_string(windowHeight) << endl;

    // Set up the camera
    DEBUG_MSG("GLRenderer.cpp : GL3DViewport() : Set up the camera.");
    glm::mat4 view = m_glcamera.GetViewMatrix();
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
//    glm::mat4 view = glm::lookAt(m_glcamera.GetPosition(), m_glcamera.GetPosition() + m_glcamera.GetFront(), m_glcamera.GetUp());
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

void GLRenderer::CallPrivateClean()
{
    PrivateClean();
}

void GLRenderer::PrivateClean()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteTextures(1, &colorAttachment);
    glDeleteTextures(1, &depthStencilAttachment);
    m_shaderProgram.reset();
}
