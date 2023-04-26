// GLRenderer.cpp

#include <Eigen/Core>
#include <imgui.h>
#include <iostream>
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLRenderer.h"
#include "GLWindow.h"
#include "Window.h"
#include "GLVertexArray.h"
#include "HoloMath.h"
#include "ErrorCheck.h"
#include "Debug.h"
#include "GLMemoryWrapper.h"
#include "GLVertexArray.h"

using namespace std;
using namespace Eigen;

//GLRenderer::GLRenderer(unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera, GLWindow& window, std::shared_ptr<SDL_GLContext> glContext) :
//    m_windowWidth(windowWidth),
//    m_windowHeight(windowHeight),
//    m_glcamera(camera),
//    m_window(window),
//    m_glContext(glContext)
//{
//    DEBUG_MSG("¢BGLRenderer.cpp : GLRenderer() : Enters GLRenderer constructor.");
//    // Initialize the OpenGL context and create the window
//    DEBUG_MSG("GLRenderer.cpp : GLRenderer() : Initializing the OpenGL context and creating the window.");
//    //m_glContext = SDL_GL_CreateContext(window->GetNativeWindowHandle());
//    m_shaderProgram = std::make_unique<GLShaderProgram>(this);
//    m_glContext = glContext;
//    
//    if (!m_glContext) 
//    {
//        DEBUG_MSG("¢RGLRenderer.cpp : GLRenderer() : Failed to create the OpenGL context.");
//        cout << std::string(SDL_GetError());
//        throw std::runtime_error("Failed to create the OpenGL context.");
//    }
//    else
//    {
//        DEBUG_MSG("¢YGLRenderer.cpp : GLRenderer() : OpenGL context not null.");
//    }
//    DEBUG_MSG("¢CGLRenderer.cpp : GLRenderer() : GLRenderer constructor completed.");
//}

GLRenderer::GLRenderer(GLWindow* window, GLCamera* camera, GLuint shaderProgram, GLVertexArray* vertexOfArrayObject) :
    m_glWindow(window),
    m_glCamera(camera),
    m_shaderProgram(shaderProgram),
    m_vao(vertexOfArrayObject)
{
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Create VAO for triangle
    //GLVertexArray triangle_vao;
    //GLuint vertex_array_object;
    //triangle_vao.CreateTriangleVAO(vertex_array_object);
    //m_vao = vertex_array_object;

    // Get location of viewMatrix uniform
    SetViewMatrixLocation(glGetUniformLocation(shaderProgram, "viewMatrix"));

    // Get location of projectionMatrix uniform
    SetProjectionMatrixLocation(glGetUniformLocation(shaderProgram, "projectionMatrix"));

    // Initialize matrices
    m_projectionMatrix = glm::perspective(glm::radians(45.0f), window->GetAspectRatio(), 0.1f, 100.0f);
    m_modelViewMatrix = glm::mat4(1.0f);
}

GLRenderer::GLRenderer()
{
}

GLRenderer::~GLRenderer()
{
    //glDeleteTextures(1, &colorAttachment);
    //glDeleteRenderbuffers(1, &depthStencilAttachment);
}

void GLRenderer::Holodesk3DViewport(float* viewportWidht, float* viewportHeight, ImVec2* viewportWsize)
{
    // Set the viewport
    glViewport(0, 0, *viewportWidht, *viewportHeight);

    // Because we use the texture from OpenGL, we need to invert the V from the UV.
    ImGui::Image((ImTextureID)HolodeskViewportTexture, *viewportWsize, ImVec2(0, 1), ImVec2(1, 0));
}

void GLRenderer::RenderScene()
{
    // Set viewport size to match the viewport window
    int viewport_w, viewport_h;
    SDL_GL_GetDrawableSize(m_glWindow->GetSDLWindow(), &viewport_w, &viewport_h);
    glViewport(0, 0, viewport_w, viewport_h);

    // Clear color and depth buffers
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable the depth buffer
    glEnable(GL_DEPTH_TEST);

    // Activate shader program
    glUseProgram(m_shaderProgram);

    // Set camera view and projection matrices
    glUniformMatrix4fv(m_modelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_glCamera->GetViewMatrix()));
    glUniformMatrix4fv(m_projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_glCamera->GetProjectionMatrix()));

    // Set up model matrix
    glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
    glUniformMatrix4fv(m_modelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(model_matrix));

    // Bind vertex array object
    m_vao->Bind();

    // Issue draw call to render the geometry
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Unbind vertex array object
    glBindVertexArray(0);
}

void GLRenderer::SetCamera(GLCamera* camera)
{
    m_glCamera = camera;
    // Update camera in renderer
}

void GLRenderer::SetViewMatrixLocation(GLuint viewMatLoc)
{
    m_modelViewMatrixLocation = viewMatLoc;
}

void GLRenderer::SetProjectionMatrixLocation(GLuint projMatLoc)
{
    m_projectionMatrixLocation = projMatLoc;
}

void GLRenderer::SetProjectionMatrix(const glm::mat4& projectionMatrix)
{
    m_projectionMatrix = projectionMatrix;
    glUniformMatrix4fv(m_projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));
}

void GLRenderer::SetViewportSize(float viewport_width, float viewport_height)
{
    glViewport(0, 0, static_cast<GLsizei>(viewport_width), static_cast<GLsizei>(viewport_height));
}

void GLRenderer::SetShaderProgramId(GLuint shaderProgramId)
{
    m_shaderProgramId = shaderProgramId;
}

//void GLRenderer::RenderScene()
//{
//    // Set viewport size to match the viewport window
//    int viewport_w, viewport_h;
//    SDL_GL_GetDrawableSize(m_glWindow->GetSDLWindow(), &viewport_w, &viewport_h);
//    glViewport(0, 0, viewport_w, viewport_h);
//
//    // Clear color and depth buffers
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    // Activate shader program
//    glUseProgram(m_shaderProgram);
//
//    // Set camera view and projection matrices
//    glUniformMatrix4fv(m_viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_glCamera->GetViewMatrix()));
//    glUniformMatrix4fv(m_projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_glCamera->GetProjectionMatrix()));
//
//    // Render scene geometry
//    // ... draw calls ...
//}

//void GLRenderer::RenderCallback(ImDrawList* draw_list, const ImDrawCmd* cmd)
//{
//    // Bind the vertex buffer and shader program
//    glBindVertexArray(m_vao);
//    glUseProgram(m_shaderProgram);
//
//    // Set up the projection matrix and model-view matrix
//    glUniformMatrix4fv(m_projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));
//    glUniformMatrix4fv(m_modelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_modelViewMatrix));
//
//    // Draw the triangle
//    glDrawArrays(GL_TRIANGLES, 0, 3);
//}



//bool GLRenderer::GLInitialize(unsigned short int windowWidth, unsigned short int windowHeight, GLCamera& camera, GLWindow* window)
//{
//    DEBUG_MSG("GLRenderer.cpp : Initialize() : Enters GLRenderer Initializer.");
//
//    DEBUG_MSG("¢BGLRenderer.cpp : Initialize() : GL version: ");
//    cout << GLVersion.major << "." << GLVersion.minor << endl;
//
//    float vertices[] = {
//        // positions        // colors
//        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // bottom left
//        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // bottom right
//        0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f, // top
//    };
//
//    // In the initialization function
//    DEBUG_MSG("GLRenderer.cpp : Initialize() : glGenVertexArrays.");
//    glGenVertexArrays(1, &m_VAO);
//    DEBUG_MSG("GLRenderer.cpp : Initialize() : glBindVertexArray.");
//    glBindVertexArray(m_VAO);
//
//    glGenBuffers(1, &m_VBO);
//    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    // Set up vertex attribute pointers
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//
//    GLenum err;
//    while ((err = glGetError()) != GL_NO_ERROR)
//    {
//        DEBUG_MSG("¢RGLRenderer.cpp : Initialize() : OpenGL error: ");
//        std::cerr << err << std::endl;
//    }
//
//    // Set up the shader program
//    DEBUG_MSG("GLRenderer.cpp : Initialize() : Set up the shader program.");
//    m_shaderProgram = make_unique<GLShaderProgram>();
//    GLShaderProgram shaderProgram;
//    bool shaderLoaded = m_shaderProgram->LoadShader(shaderProgram.GetVertexShaderFile(), shaderProgram.GetFragmentShaderFile());
//
//    if (!shaderLoaded)
//    {
//        DEBUG_MSG("¢RGLRenderer.cpp : Initialize() : Error loading shaders.");
//        return false;
//    }
//
//    // Set the viewport
//    DEBUG_MSG("GLRenderer.cpp : Initialize() : Set the viewport.");
//    glViewport(0, 0, windowWidth, windowHeight);
//
//    // Unbind the VAO
//    glBindVertexArray(0);
//
//    DEBUG_MSG("¢CGLRenderer.cpp : Initialize() : Initialize completed.");
//    return true;
//}

//void InitializeRenderingObjects()
//{
//    // Create and initialize the renderer object
//    Renderer* renderer = new Renderer();
//
//    // Create and initialize the camera object
//    Camera* camera = new Camera();
//
//    // Set up the viewport and camera projection
//    renderer->SetViewport(0, 0, windowWidth, windowHeight);
//    camera->SetProjection(FOV, aspectRatio, nearPlane, farPlane);
//
//    // Load shaders and set up materials
//    Shader* shader = ShaderLoader::LoadShader("standard");
//    Material* material = new Material(shader);
//    material->SetTexture("diffuseMap", TextureLoader::LoadTexture("diffuse.png"));
//
//    // Create and initialize meshes
//    Mesh* mesh = MeshLoader::LoadMesh("cube.obj");
//    mesh->SetMaterial(material);
//
//    // Create and initialize game objects
//    GameObject* gameObject = new GameObject(mesh, Transform(glm::vec3(0.0f, 0.0f, -5.0f)));
//
//    // Add game objects to the scene
//    Scene::AddGameObject(gameObject);
//
//    // Set up the lighting
//    renderer->SetAmbientLight(glm::vec3(0.2f, 0.2f, 0.2f));
//    PointLight* pointLight = new PointLight(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 0.09f, 0.032f);
//    renderer->AddLight(pointLight);
//}



//std::shared_ptr<GLRenderer> GLRenderer::Create(unsigned int windowWidth, unsigned int windowHeight, GLCamera& camera, GLWindow& window, SDL_GLContext& glContext)
//{
//    return std::make_shared<GLRenderer>(static_cast<unsigned short>(windowWidth), static_cast<unsigned short>(windowHeight), camera, window, glContext);
//}

//std::shared_ptr<GLRenderer> GLRenderer::Create(unsigned short int windowWidth, unsigned short int windowHeight, GLCamera& camera, GLWindow& window, SDL_GLContext& glContext)
//{
//    return std::make_shared<GLRenderer>(windowWidth, windowHeight, camera, window, glContext);
//}

//
//void GLRenderer::Render()
//{
//    DEBUG_MSG("¢BGLRenderer.cpp : Render() : Enters Render().");
//
//    glBindVertexArray(m_VAO);
//    glDrawArrays(GL_TRIANGLES, 0, 3); // Assuming you have a single triangle with 3 vertices
//    glBindVertexArray(0); // Unbind the VAO
//
//    // Clear the color and depth buffers
//    DEBUG_MSG("GLRenderer.cpp : Render() : Clear the color and depth buffers.");
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    // Update the aspect ratio
//    DEBUG_MSG("GLRenderer.cpp : Render() : Update the aspect ratio.");
//    unsigned short int width, height;
//    m_window.GetCurrentWindowSize(&width, &height);
//    UpdateAspectRatio(width, height);
//
//    // Set up the projection matrix using GLM
//    DEBUG_MSG("GLRenderer.cpp : Render() : Set up the projection matrix using GLM.");
//    glm::mat4 projection = glm::perspective(glm::radians(45.0f), m_aspectRatio, 0.1f, 100.0f);
//
//    // Define the view matrix
//    DEBUG_MSG("GLRenderer.cpp : Render() : Define the view matrix.");
//    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//
//    // Set up the model-view-projection matrix
//    DEBUG_MSG("GLRenderer.cpp : Render() : Set up the model-view-projection matrix.");
//    glm::mat4 model = glm::mat4(1.0f);
//    glm::mat4 mvp = projection * view * model;
//
//    if (!m_glContext)
//    {
//        DEBUG_MSG("¢RGLRenderer.cpp : Render() : Failed to create the OpenGL context.");
//        cout << std::string(SDL_GetError());
//        throw std::runtime_error("Failed to create the OpenGL context.");
//    }
//    else
//    {
//        DEBUG_MSG("¢YGLRenderer.cpp : Render() : OpenGL context not null.");
//    }
//
//    int status;
//    glGetProgramiv(m_shaderProgramId, GL_LINK_STATUS, &status);
//    if (status == GL_TRUE)
//    {
//        DEBUG_MSG("¢YGLRenderer.cpp : Render() : Shader program is compiled.");
//    }
//    else
//    {
//        DEBUG_MSG("¢RGLRenderer.cpp : Render() : Shader program is not compiled.");
//    }
//
//    // Get the program ID and use it with glUseProgram
//    DEBUG_MSG("GLRenderer.cpp : Render() : Get the program ID and use it with glUseProgram.");
//    GLuint programID = m_shaderProgram->GetProgramId();
//
//    DEBUG_MSG("GLRenderer.cpp : Render() : Shader Program ID: ");
//    cout << programID << endl;
//
//    glUseProgram(programID);

    //// Check if the program is active
    //DEBUG_MSG("GLRenderer.cpp : Render() : Check if the program is active.");
    //int currentProgramID;
    //glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgramID);
    //if (currentProgramID != (int)programID) 
    //{
    //    DEBUG_MSG("¢RGLRenderer.cpp : Render() : Error - the program is not active.");
    //}

    //GLenum err;
    //while ((err = glGetError()) != GL_NO_ERROR)
    //{
    //    DEBUG_MSG("¢RGLRenderer.cpp : Render() : OpenGL error: ");
    //    std::cerr << err << std::endl;
    //}

    //// Check for errors after calling glUseProgram
    //err = glGetError();
    //if (err != GL_NO_ERROR)
    //{
    //    DEBUG_MSG("¢RGLRenderer.cpp : Render() : Error after calling glUseProgram(): ");
    //    cout << err << endl;
    //}
//
//    // Set the view and projection matrices as uniform variables
//    DEBUG_MSG("GLRenderer.cpp : Render() : Set the view and projection matrices as uniform variables.");
//    glUniformMatrix4fv(glGetUniformLocation(programID, "view"), 1, GL_FALSE, glm::value_ptr(view));
//    glUniformMatrix4fv(glGetUniformLocation(programID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//
//    // Render the scene objects
//    DEBUG_MSG("GLRenderer.cpp : Render() : Render the scene objects.");
//    for (auto& object : m_sceneObjects)
//    {
//        DEBUG_MSG("¢BGLRenderer.cpp : Render() : object->Render();");
//        object.Render();
//    }
//   
//    DEBUG_MSG("¢CGLRenderer.cpp : Render() : Render function completed");
//}

//void GLRenderer::CleanUp()
//{
//}





//void GLRenderer::GL3DViewport()
//{
//    DEBUG_MSG("GLRenderer.cpp : GL3DViewport() : Enters GL3DViewport().");
//
//    // Bind the framebuffer object and set the viewport to the framebuffer size
//    DEBUG_MSG("GLRenderer.cpp : GL3DViewport() : Bind the framebuffer object and set the viewport to the framebuffer size.");
//    //BindFramebuffer();
//
//    // Clear the color and depth buffers
//    DEBUG_MSG("GLRenderer.cpp : GL3DViewport() : Clear the color and depth buffers.");
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    glm::vec3 glm_glcameraPos(m_glcamera.GetPosition().x, m_glcamera.GetPosition().y, m_glcamera.GetPosition().z);
//    glm::vec3 glm_glcameraFront(m_glcamera.GetDirection().x, m_glcamera.GetDirection().y, m_glcamera.GetDirection().z);
//    glm::vec3 glm_glcameraUp(m_glcamera.GetUp().x, m_glcamera.GetUp().y, m_glcamera.GetUp().z);
//
//    // Get the window dimensions using SDL
//    int windowWidth, windowHeight;
//    SDL_GetWindowSize(m_window.GetSDLWindow(), &windowWidth, &windowHeight);
//    DEBUG_MSG("¢YWindow dimensions: width = ");
//    cout << to_string(windowWidth) << endl;
//    DEBUG_MSG("¢Yheight = ");
//    cout << to_string(windowHeight) << endl;
//
//    // Set up the camera
//    DEBUG_MSG("GLRenderer.cpp : GL3DViewport() : Set up the camera.");
//    glm::mat4 view = m_glcamera.GetViewMatrix();
//    glm::mat4 projection = glm::perspective(glm::radians(m_fov), static_cast<float>(windowWidth) / static_cast<float>(windowHeight), m_nearPlane, m_farPlane);
//    glm::mat4 viewProjection = projection * view;
//
//    if (!check_aspect_ratio_error(projection))
//    {
//        DEBUG_MSG("¢RGLRenderer.cpp : GL3DViewport() : Failed to initialize the projection matrix.");
//    }
//
//    // Render the scene using the shader program
//    DEBUG_MSG("GLRenderer.cpp : GL3DViewport() : Render the scene using the shader program.");
//    GLShaderProgram shaderProgram;
//    GLuint shaderProgramId = shaderProgram.GetProgramId();
//    m_shaderProgram->Use(shaderProgramId);
//    m_shaderProgram->SetUniform("viewProjection", viewProjection);
//
//    //// Render scene geometry here using VAOs and draw calls
//    //DEBUG_MSG("GLRenderer.cpp : GL3DViewport() : Render scene geometry here using VAOs and draw calls.");
//    //RenderBuffer(viewProjection);
//
//    // Unbind the framebuffer object and reset the viewport to the window size
//    DEBUG_MSG("GLRenderer.cpp : GL3DViewport() : Unbind the framebuffer object and reset the viewport to the window size.");
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//    glViewport(0, 0, m_windowWidth, m_windowHeight);
//
//    DEBUG_MSG("GLRenderer.cpp : GL3DViewport() :Completed.");
//}

//void GLRenderer::InitializeGL3DViewport(int width, int height)
//{
//    // Update the aspect ratio
//    UpdateAspectRatio(width, height);
//
//    // Set the viewport dimensions
//    glViewport(0, 0, width, height);
//
//    // Initialize the projection matrix
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glm::mat4 projection = glm::perspective(glm::radians(45.0f), m_aspectRatio, 0.1f, 100.0f);
//    glLoadMatrixf(glm::value_ptr(projection));
//
//    // Initialize the modelview matrix
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//
//    // Enable depth testing
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LEQUAL);
//}

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

//void GLRenderer::DrawIndexed(unsigned int count, unsigned int start_index, unsigned int base_vertex)
//{
//    glDrawElementsBaseVertex(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)(start_index * sizeof(unsigned int)), base_vertex);
//}

//void GLRenderer::UpdateAspectRatio(int width, int height)
//{
//    m_aspectRatio = static_cast<float>(width) / static_cast<float>(height);
//    m_windowWidth = width;
//    m_windowHeight = height;
//}

//void GLRenderer::CallPrivateClean()
//{
//    PrivateClean();
//}

//void GLRenderer::PrivateClean()
//{
//    glDeleteVertexArrays(1, &m_VAO);
//    glDeleteBuffers(1, &m_VBO);
//    glDeleteTextures(1, &colorAttachment);
//    glDeleteTextures(1, &depthStencilAttachment);
//    m_shaderProgram.reset();
//}

