// GLCamera.h
#pragma once

#include <glm/gtc/quaternion.hpp>

#include "Camera.h"
#include "GLUI.h"
#include "UIElements.h"

class GLCamera{
public:
    GLCamera(UIElements* uiElements);
    glm::vec3 GetPosition() const{ return m_position; }
    glm::quat GetRotation() const{ return m_rotation; }
    float GetFOV() const{ return m_fov; }
    float GetAspectRatio() const{ return m_aspectRatio; }
    float GetNearClip() const{ return m_nearClip; }
    float GetFarClip() const{ return m_farClip; }

    glm::mat4 GetViewMatrix() const;
    glm::mat4* GetProjectionMatrix() const;
    glm::vec3 GetDirection() const { return m_front; }
    glm::vec3 GetUp() const { return m_up; }

    void SetPosition(glm::vec3 position);
    void SetRotation(const glm::quat& rotation);
    void SetFOV(float fov);
    void SetAspectRatio(float aspectRatio);
    void SetNearClip(float nearClip);
    void SetFarClip(float farClip);

    void processKeyboardInput(float deltaTime, glm::vec3 direction);
    void processMouseInput(float xoffset, float yoffset, bool constrainPitch);

    void updateCameraVectors();
    void UpdateProjectionMatrix();
    void UpdateViewMatrix();
    void Update(float deltaTime, bool* keys, float mouseX, float mouseY);

private:
    UIElements m_uiElements;
    glm::quat m_rotation;
    glm::mat4 m_viewMatrix;
    glm::mat4* m_projectionMatrix;
    glm::vec3 m_position;
    glm::vec3 m_target;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp{ 0.0f, 1.0f, 0.0f };
    float m_fov;
    float m_aspectRatio;
    float m_nearClip;
    float m_farClip;
    float m_yaw;
    float m_pitch;
    float m_movementSpeed;
    float m_mouseSensitivity;
    float m_zoom;
    float m_lastMouseX;
    float m_lastMouseY;
};