//GLDefaultSceneObject.h
#pragma once

#include <glm/glm.hpp>
#include <GLDefaultMeshes.h>
#include <GLDefaultMaterial.h>
#include <GLDefaultMeshes.h>

class SceneObject
{
public:
 
    SceneObject(GLDefaultMeshes* mesh, GLDefaultMaterial* material);

    ~SceneObject();

    void SetPosition(const glm::vec3& position);
    void SetRotation(const glm::vec3& rotation);
    void SetScale(const glm::vec3& scale);

    glm::vec3 GetPosition() const;
    glm::vec3 GetRotation() const;
    glm::vec3 GetScale() const;

    glm::mat4 GetModelMatrix() const;

    void Update(float deltaTime);
    void Render();

private:
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;

    GLDefaultMeshes* m_mesh;
    GLDefaultMaterial* m_material;
};
