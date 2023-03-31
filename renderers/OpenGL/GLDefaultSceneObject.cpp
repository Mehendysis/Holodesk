//GLDefaultSceneObject.cpp
#include "GLDefaultSceneObject.h"

SceneObject::SceneObject(GLDefaultMeshes* mesh, GLDefaultMaterial* material)
{
}

SceneObject::~SceneObject()
{
}

void SceneObject::SetPosition(const glm::vec3& position)
{
}

void SceneObject::SetRotation(const glm::vec3& rotation)
{
}

void SceneObject::SetScale(const glm::vec3& scale)
{
}

glm::vec3 SceneObject::GetPosition() const
{
	return glm::vec3();
}

glm::vec3 SceneObject::GetRotation() const
{
	return glm::vec3();
}

glm::vec3 SceneObject::GetScale() const
{
	return glm::vec3();
}

glm::mat4 SceneObject::GetModelMatrix() const
{
	return glm::mat4();
}

void SceneObject::Update(float deltaTime)
{
}

void SceneObject::Render()
{
}
