//GLCamera.h
#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GLCamera {
public:
    GLCamera() :
        m_position(0.0f, 0.0f, 0.0f),
        m_front(0.0f, 0.0f, -1.0f),
        m_up(0.0f, 1.0f, 0.0f),
        m_right(1.0f, 0.0f, 0.0f),
        m_worldUp(0.0f, 1.0f, 0.0f),
        m_yaw(-90.0f),
        m_pitch(0.0f),
        m_movementSpeed(2.5f),
        m_mouseSensitivity(0.1f),
        m_zoom(45.0f) {
        updateCameraVectors();
    }

    void processKeyboardInput(float deltaTime, glm::vec3 direction)
    {
        float velocity = m_movementSpeed * deltaTime;
        m_position += glm::normalize(m_front) * direction.z * velocity +
            glm::normalize(m_right) * direction.x * velocity +
            glm::normalize(m_up) * direction.y * velocity;
    }

    void processMouseInput(float xoffset, float yoffset, bool constrainPitch = true) {
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

    glm::mat4 GetViewMatrix() const 
    {
        return glm::lookAt(m_position, m_position + m_front, m_up);
    }

    glm::vec3 getPosition() const { return m_position; }
    glm::vec3 getFront() const { return m_front; }

    void updateCameraVectors()
    {
        glm::vec3 front;
        front.x = std::cos(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
        front.y = std::sin(glm::radians(m_pitch));
        front.z = std::sin(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
        m_front = glm::normalize(front);

        m_right = glm::normalize(glm::cross(m_front, m_worldUp));
        m_up = glm::normalize(glm::cross(m_right, m_front));
    }

private:
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;

    float m_yaw;
    float m_pitch;

    float m_movementSpeed;
    float m_mouseSensitivity;
    float m_zoom;


};
