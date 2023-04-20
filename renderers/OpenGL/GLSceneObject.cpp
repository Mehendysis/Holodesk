//GLSceneObject.cpp
#include "GLSceneObject.h"
#include "GLVertex.h"
#include "GLVertexBuffer.h"
#include "GLMesh.h"
#include "GLMemoryWrapper.h"

#include <glm/gtx/quaternion.hpp>
//#include <glad/glad.h>

GLSceneObject::GLSceneObject(GLMesh* mesh, GLMaterial* material)
    : m_mesh(mesh), m_material(material), m_mvpMatrix(glm::mat4(1.0f)), m_position(glm::vec3(0.0f)), m_rotation(glm::vec3(0.0f)), m_scale(glm::vec3(1.0f))
{
    // Constructor implementation
}

GLSceneObject::~GLSceneObject()
{
}

void GLSceneObject::SetPosition(const glm::vec3& position)
{
    m_position = position;
}

void GLSceneObject::SetRotation(const glm::vec3& rotation)
{
    m_mesh->SetRotation(rotation);
}

void GLSceneObject::SetScale(const glm::vec3& scale)
{
    m_scale = scale;
}

void GLSceneObject::SetMaterial(GLMaterial* material)
{
    m_material = material;
}

GLMaterial* GLSceneObject::GetMaterial() const
{
    return m_material;
}

glm::vec3 GLSceneObject::GetPosition() const
{
    return m_position;
}

glm::vec3 GLSceneObject::GetRotation() const
{
    // TODO: Implement
    return glm::vec3();
}

glm::vec3 GLSceneObject::GetScale() const
{
    return m_scale;
}

glm::mat4 GLSceneObject::GetModelMatrix() const
{
    glm::mat4 model(1.0f);
    model = glm::translate(model, m_position);
    model = glm::rotate(model, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, m_scale);
    return model;
}

void GLSceneObject::Update(float deltaTime)
{
    //m_mesh->Update(deltaTime);
}

void GLSceneObject::Render() const
{
    // Bind the VBO and IBO
    glBindBuffer(GL_ARRAY_BUFFER, m_mesh->m_vertexBuffer->GetID());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_mesh->m_indexBuffer->GetIndexBufferID());

    // Set the vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLVertex), (void*)offsetof(GLVertex, position));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLVertex), (void*)offsetof(GLVertex, normal));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLVertex), (void*)offsetof(GLVertex, texCoord));

    // Enable the vertex attribute arrays
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // Apply the transformations
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), m_position) * glm::toMat4(glm::quat(m_rotation)) * glm::scale(glm::mat4(1.0f), m_scale);

    // Set any uniform variables for the shader program
    m_material->SetUniforms(modelMatrix);

    // Draw the mesh using the indices in the IBO
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_mesh->m_indexBuffer->GetIndexCount()), GL_UNSIGNED_INT, 0);

    // Disable the vertex attribute arrays
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    // Draw the mesh
    m_mesh->Render();
}