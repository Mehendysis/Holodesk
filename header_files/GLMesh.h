// GLMesh.h
#ifndef GLMESH_H
#define GLMESH_H

#include "GLIndexBuffer.h"
#include "GLVertexBuffer.h"
#include "GLMaterial.h"
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>

class GLMesh
{
public:
    GLMesh();
    ~GLMesh();

    void Render() const;
    void SetPosition(const glm::vec3& position);
    void SetRotation(const glm::vec3& rotation);
    const GLVertexBuffer* GetVertexBuffer() const { return m_vertexBuffer.get(); }
    const GLIndexBuffer* GetIndexBuffer() const { return m_indexBuffer.get(); }
    std::unique_ptr<GLVertexBuffer> m_vertexBuffer;
    std::unique_ptr<GLIndexBuffer> m_indexBuffer;
    GLMaterial* m_material;
    glm::mat4 m_transform;
};

using GLMeshList = std::vector<GLMesh>;

#endif
