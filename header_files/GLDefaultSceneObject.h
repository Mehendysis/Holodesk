//GLDefaultSceneObject.h
#ifndef GL_DEFAULT_SCENE_OBJECT_H
#define GL_DEFAULT_SCENE_OBJECT_H

#include <glm/glm.hpp>
#include "GLDefaultMeshes.h"
#include "GLDefaultMaterial.h"
#include "VertexCube.h"

class GLDefaultSceneObject
{
public:
	GLDefaultSceneObject(GLDefaultMeshes* mesh, GLDefaultMaterial* material);


	virtual ~GLDefaultSceneObject();

	void SetPosition(const glm::vec3& position);
	void SetRotation(const glm::vec3& rotation);
	void SetScale(const glm::vec3& scale);
	void SetMaterial(GLDefaultMaterial* material);

	GLDefaultMaterial* GetMaterial() const;

	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;

	glm::mat4 GetModelMatrix() const;

	virtual void Update(float deltaTime);
	virtual void Render();

private:
	GLDefaultMeshes* m_mesh;
	GLDefaultMaterial* m_material;
	VertexCube m_cube;
	glm::mat4 m_mvpMatrix;
};

#endif // GL_DEFAULT_SCENE_OBJECT_H