//GLDefaultCamera.h
#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GLDefaultCamera {
public:
    GLDefaultCamera() :
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

    glm::vec3 GetPosition() const { return m_position; }
    glm::vec3 GetDirection() const { return m_front; }
    glm::vec3 GetUp() const { return m_up; }
    glm::vec3 GetFront() const { return m_front; }
    glm::mat4 GetViewMatrix() const
    {
        return glm::lookAt(m_position, m_position + m_front, m_up);
    }
    void processKeyboardInput(float deltaTime, glm::vec3 direction);
    void processMouseInput(float xoffset, float yoffset, bool constrainPitch);

    void updateCameraVectors();


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
