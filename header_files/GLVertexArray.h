//GLVertexArray.h
#pragma once

#include "GLMemoryWrapper.h"

class GLVertexArray
{
public:
	GLVertexArray();
	void CreateTriangleVAO(GLuint& vertex_array_object);
	void Bind();
	void Unbind();

private:
	GLuint m_VAO, m_VBO;
};