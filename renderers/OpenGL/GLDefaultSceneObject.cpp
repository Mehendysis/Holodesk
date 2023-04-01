//#include <windows.h>

//GLDefaultSceneObject.cpp
#include "GLDefaultSceneObject.h"
#include "GLVertex.h"
#include "GLVertexBuffer.h"

#include <glad/glad.h>

GLDefaultSceneObject::GLDefaultSceneObject(GLDefaultMeshes* mesh, GLDefaultMaterial* material)
    : m_mesh(mesh), m_material(material), m_mvpMatrix(glm::mat4(1.0f))
{
    // Constructor implementation
}

GLDefaultSceneObject::~GLDefaultSceneObject()
{
}

void GLDefaultSceneObject::SetPosition(const glm::vec3& position)
{
	m_cube.SetPosition(position); // Update the position of the cube mesh
}

void GLDefaultSceneObject::SetRotation(const glm::vec3& rotation)
{
	// TODO: Implement
}

void GLDefaultSceneObject::SetScale(const glm::vec3& scale)
{
	m_cube.SetSize(scale.x); // Update the size of the cube mesh based on the x-axis scale
}

void GLDefaultSceneObject::SetMaterial(GLDefaultMaterial* material)
{
}

GLDefaultMaterial* GLDefaultSceneObject::GetMaterial() const
{
    return nullptr;
}

glm::vec3 GLDefaultSceneObject::GetPosition() const
{
	return m_cube.GetPosition(); // Return the position of the cube mesh
}

glm::vec3 GLDefaultSceneObject::GetRotation() const
{
	// TODO: Implement
	return glm::vec3();
}

glm::vec3 GLDefaultSceneObject::GetScale() const
{
	return glm::vec3(m_cube.GetSize()); // Return the size of the cube mesh as the scale
}

glm::mat4 GLDefaultSceneObject::GetModelMatrix() const
{
	return m_cube.GetModelMatrix(); // Return the model matrix of the cube mesh
}

void GLDefaultSceneObject::Update(float deltaTime)
{
	m_cube.Update(deltaTime); // Update the cube mesh
}

void GLDefaultSceneObject::Render()
{
    // Bind the VBO and IBO
    glBindBuffer(GL_ARRAY_BUFFER, m_cube.GetVertexBuffer());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_cube.GetIndexBuffer());

    // Set the vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLVertex), (void*)offsetof(GLVertex, position));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLVertex), (void*)offsetof(GLVertex, normal));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLVertex), (void*)offsetof(GLVertex, texCoord));

    // Enable the vertex attribute arrays
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // Set any uniform variables for the shader program
    m_material->SetUniforms(m_mvpMatrix);

    // Draw the cube using the indices in the IBO
    glDrawElements(GL_TRIANGLES, m_cube.GetIndexCount(), GL_UNSIGNED_INT, 0);

    // Disable the vertex attribute arrays
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}
