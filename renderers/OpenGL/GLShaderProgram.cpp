
//GLShaderProgram.cpp

#include "GLShaderProgram.h"
#include "GLRenderer.h"


GLShaderProgram::~GLShaderProgram()
{
}

void GLShaderProgram::LoadShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
{
    // Load vertex shader source code
    std::string vertexShaderSource;
    if (!LoadFile(vertexShaderFile, vertexShaderSource))
    {
        throw std::runtime_error("Failed to load vertex shader from file: " + vertexShaderFile);
    }

    // Load fragment shader source code
    std::string fragmentShaderSource;
    if (!LoadFile(fragmentShaderFile, fragmentShaderSource))
    {
        throw std::runtime_error("Failed to load fragment shader from file: " + fragmentShaderFile);
    }

    // Compile and link shaders into a program
    GLuint vertexShader = CompileShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = CompileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    m_programId = LinkProgram(vertexShader, fragmentShader);

    // Clean up
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

bool GLShaderProgram::LoadFile(const std::string& fileName, std::string& fileContent)
{
    SDL_RWops* file = SDL_RWFromFile(fileName.c_str(), "rb");
    if (file == nullptr)
    {
        return false;
    }

    Sint64 fileSize = SDL_RWsize(file);
    char* buffer = new char[fileSize + 1];
    SDL_RWread(file, buffer, fileSize, 1);
    buffer[fileSize] = '\0';
    fileContent = buffer;
    delete[] buffer;
    SDL_RWclose(file);

    return true;
}


GLuint GLShaderProgram::LinkProgram(GLuint vertexShader, GLuint fragmentShader)
{
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Check for errors
    GLint success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        GLint logSize = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
        std::string log(logSize, ' ');
        glGetProgramInfoLog(program, logSize, &logSize, &log[0]);
        throw std::runtime_error("Failed to link shader program:\n" + log);
    }

    return program;
}

void GLShaderProgram::Use() const
{
    glUseProgram(m_programId);
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

GLuint GLShaderProgram::Compile(const std::string& source, GLenum type)
{
    GLuint shader = glCreateShader(type);
    const char* source_cstr = source.c_str();
    glShaderSource(shader, 1, &source_cstr, NULL);
    glCompileShader(shader);

    // Check for errors
    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        GLint logSize = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
        std::string log(logSize, ' ');
        glGetShaderInfoLog(shader, logSize, &logSize, &log[0]);
        throw std::runtime_error("Failed to compile shader:\n" + log);
    }

    return shader;
}