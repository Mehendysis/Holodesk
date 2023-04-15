// Camera.h
#pragma once
#include <glm/glm.hpp>

class Camera {
public:
    virtual ~Camera() {}

    virtual void SetPosition(glm::vec3 position) = 0;
    virtual void SetRotation(const glm::quat& rotation) = 0;
    virtual void SetFOV(float fov) = 0;
    virtual void SetAspectRatio(float aspectRatio) = 0;
    virtual void SetNearClip(float nearClip) = 0;
    virtual void SetFarClip(float farClip) = 0;

    virtual glm::vec3 GetPosition() const = 0;
    virtual glm::quat GetRotation() const = 0;
    virtual float GetFOV() const = 0;
    virtual float GetAspectRatio() const = 0;
    virtual float GetNearClip() const = 0;
    virtual float GetFarClip() const = 0;

    virtual glm::mat4 GetViewMatrix() const = 0;
    virtual glm::mat4 GetProjectionMatrix() const = 0;
};