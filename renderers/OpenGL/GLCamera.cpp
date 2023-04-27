//GLCamera.cpp

#include <SDL.h>
#include <iostream>

#include "GLCamera.h"
#include "Window.h"
#include "Debug.h"


GLCamera::GLCamera(UIElements* uiElements) :
    m_position(0.0f, 0.0f, 3.0f),
    m_target(0.0f, 0.0f, 0.0f),
    m_rotation(1.0f, 0.0f, 0.0f, 0.0f),
    m_up(0.0f, 1.0f, 0.0f),
    m_fov(45.0f),
    m_aspectRatio(1.0f),
    m_nearClip(0.1f),
    m_farClip(100.0f),
    m_yaw(-90.0f),
    m_pitch(0.0f),
    m_movementSpeed(2.5f),
    m_mouseSensitivity(0.1f),
    m_zoom(45.0f),
    m_lastMouseX(0.0f),
    m_lastMouseY(0.0f),
    m_uiElements(*uiElements)
{
    DEBUG_MSG("¢BGLCamera.cpp : GLCamera(UIElements* uiElements) : Enters GLCamera(UIElements* uiElements) constructor.");
    UpdateProjectionMatrix();
    UpdateCameraVectors();
    DEBUG_MSG("¢CGLCamera.cpp : GLCamera(UIElements* uiElements) : GLCamera(UIElements* uiElements) constructor completed.");
}

glm::mat4 GLCamera::GetViewMatrix() const
{
    return glm::mat4();
}

glm::mat4* GLCamera::GetProjectionMatrix() const
{
    DEBUG_MSG("¢BGLCamera.cpp : GetProjectionMatrix() : Enters GetProjectionMatrix().");
    if (m_projectionMatrix == nullptr) 
    {
        std::cout << "Projection matrix is null" << std::endl;
    }
    DEBUG_MSG("¢CGLCamera.cpp : GetProjectionMatrix() : GetProjectionMatrix() completed.");
    return m_projectionMatrix;
}

void GLCamera::SetPosition(glm::vec3 position)
{ 
    m_position = position; 
}

void GLCamera::SetRotation(const glm::quat& rotation)
{ 
    m_rotation = rotation; 
}

void GLCamera::SetFOV(float fov)
{ 
    m_fov = fov; 
}

void GLCamera::SetAspectRatio(float aspectRatio)
{ 
    m_aspectRatio = aspectRatio; 
}

void GLCamera::SetNearClip(float nearClip)
{ 
    m_nearClip = nearClip; 
}

void GLCamera::SetFarClip(float farClip)
{ 
    m_farClip = farClip; 
}

void GLCamera::processKeyboardInput(float deltaTime, glm::vec3 direction) 
{
    float velocity = m_movementSpeed * deltaTime;
    m_position += glm::normalize(m_front) * direction.z * velocity + glm::normalize(m_right) * direction.x * velocity + glm::normalize(m_up) * direction.y * velocity;
}

void GLCamera::processMouseInput(float xoffset, float yoffset, bool constrainPitch) 
{
    xoffset *= m_mouseSensitivity;
    yoffset *= m_mouseSensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    if (constrainPitch) 
    {
        if (m_pitch > 89.0f) 
        {
            m_pitch = 89.0f;
        }
        else if (m_pitch < -89.0f) 
        {
            m_pitch = -89.0f;
        }
    }

    UpdateCameraVectors();
}

void GLCamera::Update(float deltaTime, bool* keys, float mouseX, float mouseY)
{
    // Process keyboard input to move the camera
    glm::vec3 direction(0.0f);
    if (keys[SDL_SCANCODE_W]) {
        direction.z -= 1.0f;
    }
    if (keys[SDL_SCANCODE_S]) {
        direction.z += 1.0f;
    }
    if (keys[SDL_SCANCODE_A]) {
        direction.x -= 1.0f;
    }
    if (keys[SDL_SCANCODE_D]) {
        direction.x += 1.0f;
    }
    if (keys[SDL_SCANCODE_SPACE]) {
        direction.y += 1.0f;
    }
    if (keys[SDL_SCANCODE_LCTRL]) {
        direction.y -= 1.0f;
    }
    processKeyboardInput(deltaTime, direction);

    // Process mouse input to rotate the camera
    float xoffset = mouseX - m_lastMouseX;
    float yoffset = m_lastMouseY - mouseY;
    m_lastMouseX = mouseX;
    m_lastMouseY = mouseY;
    processMouseInput(xoffset, yoffset, true);

    // Update the projection matrix
    UpdateProjectionMatrix();

    // Update the view matrix
    UpdateViewMatrix();
}

void GLCamera::UpdateProjectionMatrix()
{
    DEBUG_MSG("¢BGLCamera.cpp : UpdateProjectionMatrix() : Enters UpdateProjectionMatrix().");
	float* windowWidth = static_cast<float*>(m_uiElements.GetHolodeskImGuiViewportWidth());
	float* windowHeight = static_cast<float*>(m_uiElements.GetHolodeskImGuiViewportHeight());
	m_projectionMatrix = new glm::mat4(glm::perspective(glm::radians(45.0f), *windowWidth / *windowHeight, 0.1f, 100.0f));
    DEBUG_MSG("¢CGLCamera.cpp : UpdateProjectionMatrix() : UpdateProjectionMatrix() completed.");
}

void GLCamera::UpdateViewMatrix()
{
	m_viewMatrix = glm::lookAt(m_position, m_position + m_front, m_up);
}

void GLCamera::UpdateCameraVectors()
{
    // Calculate the new front vector
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);

    // Calculate the new right vector
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));

    // Calculate the new up vector
    m_up = glm::normalize(glm::cross(m_right, m_front));

    // Calculate the view matrix
    m_viewMatrix = glm::lookAt(m_position, m_position + m_front, m_up);
}