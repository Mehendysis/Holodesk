//GLDefaultCamera.cpp
#include "GLDefaultCamera.h"

void GLDefaultCamera::processKeyboardInput(float deltaTime, glm::vec3 direction) {
    float velocity = m_movementSpeed * deltaTime;
    m_position += glm::normalize(m_front) * direction.z * velocity +
        glm::normalize(m_right) * direction.x * velocity +
        glm::normalize(m_up) * direction.y * velocity;
}

void GLDefaultCamera::processMouseInput(float xoffset, float yoffset, bool constrainPitch) 
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

void GLDefaultCamera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);

    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}
