//GLShaderProgram.cpp
#include "GLShaderProgram.h"

GLShaderProgram::GLShaderProgram()
{
}

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

void GLShaderProgram::SetUniform(const std::string& name, bool value) const
{
}

void GLShaderProgram::SetUniform(const std::string& name, int value) const
{
}

void GLShaderProgram::SetUniform(const std::string& name, float value) const
{
}

void GLShaderProgram::SetUniform(const std::string& name, const glm::vec3& value) const
{
}

void GLShaderProgram::SetUniform(const std::string& name, const glm::mat4& value) const
{
}

std::string GLShaderProgram::ReadShaderFile(const std::string& fileName) const
{
	return std::string();
}

GLuint GLShaderProgram::CompileShader(const std::string& shaderSource, GLenum shaderType) const
{
	return GLuint();
}
