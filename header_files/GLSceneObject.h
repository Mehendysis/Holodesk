// GLSceneObject.h
#ifndef GLSCENEOBJECT_H
#define GLSCENEOBJECT_H

#include "GLVertexBuffer.h"
#include "GLIndexBuffer.h"
#include "GLMaterial.h"
#include "GLMesh.h"

//#include <memory>
#include <glm/glm.hpp>

class GLSceneObject
{
public:
    GLSceneObject(GLMesh* mesh, GLMaterial* material);
    ~GLSceneObject();

    void SetPosition(const glm::vec3& position);
    void SetRotation(const glm::vec3& rotation);
    void SetScale(const glm::vec3& scale);
    void SetMaterial(GLMaterial* material);
    GLMaterial* GetMaterial() const;

    glm::vec3 GetPosition() const;
    glm::vec3 GetRotation() const;
    glm::vec3 GetScale() const;
    glm::mat4 GetModelMatrix() const;

    void Update(float deltaTime);
    void Render() const;

private:
    //GLRenderer* m_renderer;
    GLMesh* m_mesh;
    GLMaterial* m_material;
    glm::mat4 m_mvpMatrix;
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
};

#endif // GLSCENEOBJECT_H
