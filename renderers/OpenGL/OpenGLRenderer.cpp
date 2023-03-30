// OpenGLRenderer.cpp
#include "OpenGLRenderer.h"
#include <HoloMath.h>
#include <windows.h>
#include <iostream>
#include <glad/glad.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

OpenGLRenderer::~OpenGLRenderer()
{
}

void OpenGLRenderer::Initialize()
{
    // Initialize GLAD
    if (!gladLoadGL()) {
        cerr << "Error: GLAD failed to initialize" << endl;
        return;
    }

    // Set up the shader program
    m_shaderProgram.LoadShader("path/to/vertex/shader", "path/to/fragment/shader");
    m_shaderProgram.Compile();
    m_shaderProgram.Link();
    m_shaderProgram.Use();

    // Set up the framebuffer object
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    // Create the texture attachment
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_fboWidth, m_fboHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

    // Create the render buffer object
    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_fboWidth, m_fboHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

    // Check if the framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        cout << "Error: Framebuffer is not complete" << endl;
    }

    // Unbind the framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Set the camera position and target
    m_camera.processKeyboardInput(0.0f, glm::vec3(0.0f, 0.0f, 3.0f));
    m_camera.processKeyboardInput(0.0f, glm::vec3(0.0f, 0.0f, 0.0f));

    // Set the camera up vector
    m_camera.updateCameraVectors();
}


void OpenGLRenderer::Render()
{
    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up the projection matrix using GLM
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), m_aspectRatio, 0.1f, 100.0f);

    // Get the view matrix using GLM
    glm::mat4 view = m_camera.GetViewMatrix();

    // Define the projection parameters
    float fov = 45.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    float aspectRatio = m_aspectRatio;

    // Calculate the projection matrix
    glm::mat4 projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);

    // Set up the view matrix
    glm::mat4 view = m_camera.GetViewMatrix();

    // Set up the model-view-projection matrix
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 mvp = projection * view * model;

    glUseProgram(m_shaderProgram.m_shaderProgramId)
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "mvp"), 1, GL_FALSE, glm::value_ptr(mvp));

    // Render the scene objects
    for (auto& object : m_sceneObjects)
    {
        object->Render();
    }
}


void OpenGLRenderer::CleanUp()
{
}

void OpenGLRenderer::SetFBO(unsigned int width, unsigned int height)
{
    // Create a new framebuffer object if it hasn't been created yet
    if (m_fbo == 0)
    {
        Eigen::Matrix4f view = m_camera.GetViewMatrix().cast<float>();
        Eigen::Matrix4f projection;
        float fov = 45.0f;
        float nearPlane = 0.1f;
        float farPlane = 100.0f;
        float aspectRatio = (float)viewportWidth / (float)viewportHeight;
        float tanHalfFov = tan(radians(fov / 2.0f));
        projection << 1.0f / (aspectRatio * tanHalfFov), 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f / tanHalfFov, 0.0f, 0.0f,
            0.0f, 0.0f, -(farPlane + nearPlane) / (farPlane - nearPlane), -1.0f,
            0.0f, 0.0f, -(2.0f * farPlane * nearPlane) / (farPlane - nearPlane), 0.0f;

        glUseProgram(m_shaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "view"), 1, GL_FALSE, view.data());
        glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "projection"), 1, GL_FALSE, projection.data());


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

void OpenGLRenderer::BindFBO()
{
    // Bind the FBO
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    // Set the viewport to the size of the FBO
    glViewport(0, 0, m_width, m_height);
}

void OpenGLRenderer::RenderBuffer()
{
    // Bind the FBO for rendering
    BindFBO();

    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up the viewport and projection matrix
    glViewport(0, 0, m_width, m_height);
    glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)m_width / (float)m_height, 0.1f, 1000.0f);

    // Set up the view matrix based on the camera's position and orientation
    glm::vec3 cameraPos = m_camera.GetPosition();
    glm::vec3 cameraDir = m_camera.GetDirection();
    glm::vec3 cameraUp = m_camera.GetUp();
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraDir, cameraUp);

    // Set up the model matrix for the object being rendered
    glm::mat4 model = glm::mat4(1.0f);

    // Set up the shader program
    m_shaderProgram.Use();
    m_shaderProgram.SetUniform("uProjection", projection);
    m_shaderProgram.SetUniform("uView", view);
    m_shaderProgram.SetUniform("uModel", model);

    // Render the object
    m_mesh.Render();

    // Unbind the FBO
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLRenderer::GL3DViewport()
{
    // Bind the framebuffer object and set the viewport to the framebuffer size
    BindFBO();
    glViewport(0, 0, m_fboWidth, m_fboHeight);

    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up the camera
    glm::mat4 view = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
    glm::mat4 projection = glm::perspective(glm::radians(m_fov), static_cast<float>(m_fboWidth) / static_cast<float>(m_fboHeight), m_nearPlane, m_farPlane);
    glm::mat4 viewProjection = projection * view;

    // Render the scene using the shader program
    m_shaderProgram->Use();
    m_shaderProgram->SetMat4("viewProjection", viewProjection);
    // Render scene geometry here using VAOs and draw calls
    RenderBuffer();

    // Unbind the framebuffer object and reset the viewport to the window size
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, m_windowWidth, m_windowHeight);
}

void OpenGLRenderer::GL2DViewport()
{
	// Bind the framebuffer object and set the viewport to the framebuffer size
	BindFBO();
	glViewport(0, 0, m_fboWidth, m_fboHeight);
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Set up the camera
	glm::mat4 view = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_fboWidth), 0.0f, static_cast<float>(m_fboHeight), m_nearPlane, m_farPlane);
	glm::mat4 viewProjection = projection * view;
	// Render the scene using the shader program
	m_shaderProgram->Use();
	m_shaderProgram->SetMat4("viewProjection", viewProjection);
	// Render scene geometry here using VAOs and draw calls
	RenderBuffer();
	// Unbind the framebuffer object and reset the viewport to the window size
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, m_windowWidth, m_windowHeight);
}

void OpenGLRenderer::DefaultCameraScene()
{
    static Eigen::Vector3f cameraPosition(0.0f, 0.0f, 3.0f);
    static Eigen::Vector3f cameraTarget(0.0f, 0.0f, 0.0f);
    static Eigen::Vector3f cameraUp(0.0f, 1.0f, 0.0f);
    static float cameraFOV = 45.0f;
    static float cameraYaw = -90.0f;
    static float cameraPitch = 0.0f;

    ImGuiIO& io = ImGui::GetIO();
    Eigen::Vector2f mouseDelta(io.MouseDelta.x, io.MouseDelta.y);
    float sensitivity = 0.1f;
    mouseDelta *= sensitivity;

    cameraYaw += mouseDelta.x();
    cameraPitch += mouseDelta.y();

    if (cameraPitch > 89.0f)
        cameraPitch = 89.0f;
    if (cameraPitch < -89.0f)
        cameraPitch = -89.0f;

    Eigen::Vector3f front;
    front.x() = cos(radians(cameraYaw)) * cos(radians(cameraPitch));
    front.y() = sin(radians(cameraPitch));
    front.z() = sin(radians(cameraYaw)) * cos(radians(cameraPitch));
    cameraTarget = front.normalized();

    if (ImGui::IsKeyPressed(GLFW_KEY_W))
        cameraPosition += cameraTarget * cameraSpeed;
    if (ImGui::IsKeyPressed(GLFW_KEY_S))
        cameraPosition -= cameraTarget * cameraSpeed;
    if (ImGui::IsKeyPressed(GLFW_KEY_A))
        cameraPosition -= cameraTarget.cross(cameraUp).normalized() * cameraSpeed;
    if (ImGui::IsKeyPressed(GLFW_KEY_D))
        cameraPosition += cameraTarget.cross(cameraUp).normalized() * cameraSpeed;

    Eigen::Matrix4f view = Eigen::lookAt(cameraPosition, cameraPosition + cameraTarget, cameraUp);
    Eigen::Matrix4f projection;
    float fov = 45.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    float aspectRatio = m_aspectRatio;
    float tanHalfFov = tan(radians(fov / 2.0f));
    projection << 1.0f / (aspectRatio * tanHalfFov), 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f / tanHalfFov, 0.0f, 0.0f,
        0.0f, 0.0f, -(farPlane + nearPlane) / (farPlane - nearPlane), -1.0f,
        0.0f, 0.0f, -(2.0f * farPlane * nearPlane) / (farPlane - nearPlane), 0.0f;

    // Set the camera matrices in the shader
    glUseProgram(m_shaderProgram);
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "view"), 1, GL_FALSE, view.data());
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "projection"), 1, GL_FALSE, projection.data());

    m_camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
