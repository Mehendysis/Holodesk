
//GLShaderProgram.cpp

#include "GLShaderProgram.h"
#include "GLRenderer.h"


GLShaderProgram::~GLShaderProgram()
{
}

void GLShaderProgram::LoadShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
{
}

void GLShaderProgram::Compile()
{
}

void GLShaderProgram::Link()
{
}

void GLShaderProgram::Use() const
{
}

void GLShaderProgram::SetUniform(const std::string& name, const glm::mat4& value) const
{
	GLint location = glGetUniformLocation(m_shaderProgramId, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}


std::string GLShaderProgram::ReadShaderFile(const std::string& fileName) const
{
	return std::string();
}

GLuint GLShaderProgram::CompileShader(const std::string& shaderSource, GLenum shaderType) const
{
	return GLuint();
}
