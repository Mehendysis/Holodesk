//SceneObject.h
#pragma once
#include <glm/glm.hpp>

class SceneObject
{
public:
    virtual ~SceneObject() {}

    virtual void SetPosition(const glm::vec3& position) = 0;
    virtual void SetRotation(const glm::vec3& rotation) = 0;
    virtual void SetScale(const glm::vec3& scale) = 0;

    virtual glm::vec3 GetPosition() const = 0;
    virtual glm::vec3 GetRotation() const = 0;
    virtual glm::vec3 GetScale() const = 0;

    virtual glm::mat4 GetModelMatrix() const = 0;

    virtual void Update(float deltaTime) = 0;
    virtual void Render() const;
};
