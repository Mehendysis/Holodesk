// GLCamera.h
#pragma once
#include "Camera.h"
#include <glm/gtc/quaternion.hpp>

class GLCamera : public Camera {
public:
    GLCamera();
    glm::vec3 GetPosition() const override { return m_position; }
    glm::quat GetRotation() const override { return m_rotation; }
    float GetFOV() const override { return m_fov; }
    float GetAspectRatio() const override { return m_aspectRatio; }
    float GetNearClip() const override { return m_nearClip; }
    float GetFarClip() const override { return m_farClip; }

    glm::mat4 GetViewMatrix() const override;
    glm::mat4 GetProjectionMatrix() const override;
    glm::vec3 GetDirection() const { return m_front; }
    glm::vec3 GetUp() const { return m_up; }

    void SetPosition(glm::vec3 position) override { m_position = position; }
    void SetRotation(const glm::quat& rotation) override { m_rotation = rotation; }
    void SetFOV(float fov) override { m_fov = fov; }
    void SetAspectRatio(float aspectRatio) override { m_aspectRatio = aspectRatio; }
    void SetNearClip(float nearClip) override { m_nearClip = nearClip; }
    void SetFarClip(float farClip) override { m_farClip = farClip; }

    void processKeyboardInput(float deltaTime, glm::vec3 direction);
    void processMouseInput(float xoffset, float yoffset, bool constrainPitch);
    void updateCameraVectors();

private:
    glm::vec3 m_worldUp{ 0.0f, 1.0f, 0.0f };
    glm::mat4 m_viewMatrix;
    glm::vec3 m_position;
    glm::quat m_rotation;
    float m_fov;
    float m_aspectRatio;
    float m_nearClip;
    float m_farClip;

    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;

    float m_yaw;
    float m_pitch;
    float m_movementSpeed;
    float m_mouseSensitivity;
    float m_zoom;
};