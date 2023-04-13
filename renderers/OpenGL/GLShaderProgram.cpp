//GLShaderProgram.cpp

#include "GLShaderProgram.h"
#include "GLRenderer.h"
#include "Debug.h"

#include <stdexcept>
#include <fstream>
#include <sstream>


GLShaderProgram::~GLShaderProgram()
{
}

void GLShaderProgram::LoadShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
{
    DEBUG_MSG("GLShaderProgram.cpp : LoadShader() : Enters LoadShader().");

    // Load vertex shader source code
    DEBUG_MSG("GLShaderProgram.cpp : LoadShader() : Load vertex shader source code.");
    std::string vertexShaderSource;
    if (!LoadFile(vertexShaderFile, vertexShaderSource))
    {
        DEBUG_MSG("¢RGLShaderProgram.cpp : LoadShader() : Failed to load vertex shader from file: ");
        throw std::runtime_error(vertexShaderFile);
    }

    // Load fragment shader source code
    DEBUG_MSG("GLShaderProgram.cpp : LoadShader() : Load fragment shader source code.");
    std::string fragmentShaderSource;
    if (!LoadFile(fragmentShaderFile, fragmentShaderSource))
    {
        DEBUG_MSG("¢RGLShaderProgram.cpp : LoadShader() : Failed to load fragment shader from file: ");
        throw std::runtime_error(fragmentShaderFile);
    }

    // Compile and link shaders into a program
    DEBUG_MSG("GLShaderProgram.cpp : LoadShader() : Compile and link shaders into a program.");
    GLuint vertexShader = Compile(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = Compile(fragmentShaderSource, GL_FRAGMENT_SHADER);

    // Link shader program
    DEBUG_MSG("GLShaderProgram.cpp : LoadShader() : Link shader program.");
    m_shaderProgramId = Link(vertexShader, fragmentShader);

    // Store the IDs of the compiled vertex and fragment shaders
    DEBUG_MSG("GLShaderProgram.cpp : LoadShader() : Store the IDs of the compiled vertex and fragment shaders.");
    m_vertexShaderId = vertexShader;
    m_fragmentShaderId = fragmentShader;

    // Clean up
    DEBUG_MSG("GLShaderProgram.cpp : LoadShader() : Clean up.");
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

bool GLShaderProgram::LoadFile(const std::string& fileName, std::string& fileContent)
{
    DEBUG_MSG("GLShaderProgram.cpp : LoadShader() : Enters LoadFile().");

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

std::string LoadFile(const std::string& filename)
{
    DEBUG_MSG("GLShaderProgram.cpp : LoadShader() : Enters string LoadFile().");

    std::ifstream file(filename);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

GLuint GLShaderProgram::Link(GLuint vertexShader, GLuint fragmentShader)
{
    DEBUG_MSG("GLShaderProgram.cpp : LoadShader() : Enters Link().");
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
    DEBUG_MSG("GLShaderProgram.cpp : LoadShader() : Enters Use().");
    glUseProgram(m_programId);
}


void GLShaderProgram::SetUniform(const std::string& name, const glm::mat4& value) const
{
    DEBUG_MSG("GLShaderProgram.cpp : LoadShader() : Enters SetUniform().");
	GLint location = glGetUniformLocation(m_shaderProgramId, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}


std::string GLShaderProgram::ReadShaderFile(const std::string& fileName) const
{
    DEBUG_MSG("GLShaderProgram.cpp : LoadShader() : Enters ReadShaderFile().");
	return std::string();
}

GLuint GLShaderProgram::Compile(const std::string& source, GLenum type)
{
    DEBUG_MSG("GLShaderProgram.cpp : LoadShader() : Enters Compile().");
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

GLuint GLShaderProgram::GetFragmentShaderId() const
{
    DEBUG_MSG("GLShaderProgram.cpp : LoadShader() : Enters GetFragmentShaderId().");
    // Return the fragment shader ID
    return m_fragmentShaderId;
}
