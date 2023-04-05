//GLCamera.cpp
#include "GLCamera.h"

GLCamera::GLCamera() :
    m_position(0.0f, 1.0f, 0.0f),
    m_worldUp(0.0f, 1.0f, 0.0f),
    m_yaw(-90.0f),
    m_pitch(0.0f),
    m_movementSpeed(2.5f),
    m_mouseSensitivity(0.1f),
    m_zoom(45.0f)
{
    updateCameraVectors();
}


void GLCamera::processKeyboardInput(float deltaTime, glm::vec3 direction) {
    float velocity = m_movementSpeed * deltaTime;
    m_position += glm::normalize(m_front) * direction.z * velocity +
        glm::normalize(m_right) * direction.x * velocity +
        glm::normalize(m_up) * direction.y * velocity;
}

void GLCamera::processMouseInput(float xoffset, float yoffset, bool constrainPitch) 
{
    xoffset *= m_mouseSensitivity;
    yoffset *= m_mouseSensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    if (constrainPitch) {
        if (m_pitch > 89.0f) {
            m_pitch = 89.0f;
        }
        else if (m_pitch < -89.0f) {
            m_pitch = -89.0f;
        }
    }

    updateCameraVectors();
}

void GLCamera::updateCameraVectors()
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