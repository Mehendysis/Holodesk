//GLShaderProgram.cpp

#include "GLShaderProgram.h"
#include "GLRenderer.h"
#include "Debug.h"

#include <stdexcept>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

GLShaderProgram::~GLShaderProgram()
{
}

bool GLShaderProgram::LoadShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
{
    DEBUG_MSG("¢BGLShaderProgram.cpp : LoadShader() : Enters LoadShader().");

    // Load vertex shader source code
    DEBUG_MSG("GLShaderProgram.cpp : LoadShader() : Load vertex shader source code.");
    std::string vertexShaderSource;
    if (!LoadFile(vertexShaderFile, vertexShaderSource))
    {
        DEBUG_MSG("¢RGLShaderProgram.cpp : LoadShader() : Failed to load vertex shader from file: ");
        throw std::runtime_error(vertexShaderFile);
        return false;
    }

    // Load fragment shader source code
    DEBUG_MSG("GLShaderProgram.cpp : LoadShader() : Load fragment shader source code.");
    std::string fragmentShaderSource;
    if (!LoadFile(fragmentShaderFile, fragmentShaderSource))
    {
        DEBUG_MSG("¢RGLShaderProgram.cpp : LoadShader() : Failed to load fragment shader from file: ");
        throw std::runtime_error(fragmentShaderFile);
        return false;
    }

    DEBUG_MSG("¢YGLShaderProgram.cpp : LoadShader() : vertexShaderSource = ");
    cout << vertexShaderSource;
    DEBUG_MSG("¢YGLShaderProgram.cpp : LoadShader() : fragmentShaderSource = ");
    cout << fragmentShaderSource;

    // Compile and link shaders into a program
    DEBUG_MSG("GLShaderProgram.cpp : LoadShader() : Compile and link shaders into a program.");
    GLuint vertexShader = Compile(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = Compile(fragmentShaderSource, GL_FRAGMENT_SHADER);

    // Link shader program
    DEBUG_MSG("GLShaderProgram.cpp : LoadShader() : Link shader program.");
    m_shaderProgramId = Link(vertexShader, fragmentShader);
    if (m_shaderProgramId == 0) 
    {
        DEBUG_MSG("¢RGLShaderProgram.cpp : LoadShader() : Failed to create a valid shader program ID.");
        return false;
    }
    else
    {
        DEBUG_MSG("¢GGLShaderProgram.cpp : LoadShader() : Shader program ID is valid.");
    }

    // Store the IDs of the compiled vertex and fragment shaders
    DEBUG_MSG("GLShaderProgram.cpp : LoadShader() : Store the IDs of the compiled vertex and fragment shaders.");
    m_vertexShaderId = vertexShader;
    m_fragmentShaderId = fragmentShader;

    // Clean up
    DEBUG_MSG("GLShaderProgram.cpp : LoadShader() : Clean up.");
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    DEBUG_MSG("¢GGLShaderProgram.cpp : LoadShader() : LoadShader() completed.");
    return true;
}

bool GLShaderProgram::LoadFile(const std::string& fileName, std::string& fileContent)
{
    DEBUG_MSG("¢BGLShaderProgram.cpp : LoadFile() : Enters LoadFile().");

    SDL_RWops* file = SDL_RWFromFile(fileName.c_str(), "rb");
    if (file == nullptr)
    {
        DEBUG_MSG("¢RGLShaderProgram.cpp : LoadFile() : Could not load file.");
        return false;
    }

    Sint64 fileSize = SDL_RWsize(file);
    char* buffer = new char[fileSize + 1];
    SDL_RWread(file, buffer, fileSize, 1);
    buffer[fileSize] = '\0';
    fileContent = buffer;
    delete[] buffer;
    SDL_RWclose(file);

    DEBUG_MSG("¢GGLShaderProgram.cpp : LoadFile() : LoadFile() completed.");
    return true;
}

std::string LoadFile(const std::string& filename)
{
    DEBUG_MSG("GLShaderProgram.cpp : LoadFile() : Enters string LoadFile().");

    std::ifstream file(filename);

    if (!file.is_open())
    {
        DEBUG_MSG("@RGLShaderProgram.cpp : LoadFile() : Failed to open file: ");
        throw std::runtime_error(filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
    DEBUG_MSG("¢GGLShaderProgram.cpp : LoadFile() : string LoadFile() completed.");
}

GLuint GLShaderProgram::Link(GLuint vertexShader, GLuint fragmentShader)
{
    DEBUG_MSG("¢BGLShaderProgram.cpp : Link() : Enters Link().");
    m_shaderProgramId = glCreateProgram();
    DEBUG_MSG("¢YGLShaderProgram.cpp : Link() : Shader Program ID after glCreateProgram: ");
    cout << m_shaderProgramId << endl;

    glAttachShader(m_shaderProgramId, vertexShader);
    glAttachShader(m_shaderProgramId, fragmentShader);
    glLinkProgram(m_shaderProgramId);

    // Check for errors
    GLint success = 0;
    glGetProgramiv(m_shaderProgramId, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        GLint logSize = 0;
        glGetProgramiv(m_shaderProgramId, GL_INFO_LOG_LENGTH, &logSize);
        std::string log(logSize, ' ');
        glGetProgramInfoLog(m_shaderProgramId, logSize, &logSize, &log[0]);
        DEBUG_MSG("¢RGLShaderProgram.cpp : Link() : Failed to link shader program:");
        throw std::runtime_error("\n" + log);
    }

    // After glLinkProgram(shaderProgram);
    glGetProgramiv(m_shaderProgramId, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(m_shaderProgramId, 512, nullptr, infoLog);
        DEBUG_MSG("¢RGLShaderProgram.cpp : Link() : ERROR::SHADER::PROGRAM::LINKING_FAILED:");
        std::cout << "\n" << infoLog << std::endl;
        glGetProgramInfoLog(m_shaderProgramId, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "ERROR::PROGRAM_LINKING_ERROR\n" << infoLog << std::endl;
        return false;
    }

    GLint validate_status = 0;
    glValidateProgram(m_shaderProgramId);
    glGetProgramiv(m_shaderProgramId, GL_VALIDATE_STATUS, &validate_status);
    if (validate_status == GL_FALSE)
    {
        GLint logSize = 0;
        glGetProgramiv(m_shaderProgramId, GL_INFO_LOG_LENGTH, &logSize);
        std::string log(logSize, ' ');
        glGetProgramInfoLog(m_shaderProgramId, logSize, &logSize, &log[0]);
        DEBUG_MSG("¢RGLShaderProgram.cpp : Link() : Shader program validation failed: ");
        std::cout << "\n" << log << std::endl;
    }

    DEBUG_MSG("¢GGLShaderProgram.cpp : Link() : Link() completed.");
    return m_shaderProgramId;
}

void GLShaderProgram::Use() const
{
    DEBUG_MSG("¢BGLShaderProgram.cpp : Use() : Enters Use().");
    glUseProgram(m_shaderProgramId);
 
    if (m_shaderProgramId)
    {
        glUseProgram(m_shaderProgramId);
        DEBUG_MSG("¢GGLShaderProgram.cpp : Use() : Program is now in use.");
    }
    else 
    {
        DEBUG_MSG("¢RGLShaderProgram.cpp : Use() : Program is not valid.");
    }
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        DEBUG_MSG("¢RGLShaderProgram.cpp : Use() : OpenGL error: ");
        std::cerr << err << std::endl;
    }
    DEBUG_MSG("¢GGLShaderProgram.cpp : Use() : Use() completed.");
}


void GLShaderProgram::SetUniform(const std::string& name, const glm::mat4& value) const
{
    DEBUG_MSG("GLShaderProgram.cpp : SetUniform() : Enters SetUniform().");
	GLint location = glGetUniformLocation(m_shaderProgramId, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));

    if (m_shaderProgramId)
    {
        glUseProgram(m_shaderProgramId);
        DEBUG_MSG("¢GGLShaderProgram.cpp : SetUniform() : Program is now in use.");
    }
    else 
    {
        DEBUG_MSG("¢RGLShaderProgram.cpp : SetUniform() : Program is not valid.");
    }

    location = glGetUniformLocation(m_shaderProgramId, name.c_str());
    if (location == -1) 
    {
        DEBUG_MSG("¢RGLShaderProgram.cpp : SetUniform() : Uniform location not found.");
    }

    glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(value));
    if (glGetError() != GL_NO_ERROR) 
    {
        DEBUG_MSG("¢RGLShaderProgram.cpp : SetUniform() : OpenGL error while setting uniform matrix.");
    }

    DEBUG_MSG("¢GGLShaderProgram.cpp : SetUniform() : SetUniform() completed.");
}


std::string GLShaderProgram::ReadShaderFile(const std::string& fileName) const
{
    DEBUG_MSG("GLShaderProgram.cpp : ReadShaderFile() : Enters ReadShaderFile().");
	return std::string();
}

GLuint GLShaderProgram::Compile(const std::string& source, GLenum type)
{
    DEBUG_MSG("¢BGLShaderProgram.cpp : Compile() : Enters Compile().");
    GLuint shader = glCreateShader(type);
    const char* source_cstr = source.c_str();
    glShaderSource(shader, 1, &source_cstr, NULL);
    glCompileShader(shader);
    GLint success;
    //GLchar infoLog[512];

    // Check for errors
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        GLint logSize = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
        std::string log(logSize, ' ');
        glGetShaderInfoLog(shader, logSize, &logSize, &log[0]);
        DEBUG_MSG("¢RGLShaderProgram.cpp : Compile() : Failed to compile shader: ");
        throw std::runtime_error("\n" + log);
    }

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) 
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        DEBUG_MSG("¢RGLShaderProgram.cpp : Compile() : ERROR::SHADER::COMPILATION_FAILED infoLog: ");
        std::cout << "\n" << infoLog << std::endl;
        //glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
        //DEBUG_MSG("¢RGLShaderProgram.cpp : Compile() : ERROR::SHADER::COMPILATION_FAILED shaderType : ");
        //std::cout << "\n" << shaderType << std::endl;
    }

    DEBUG_MSG("¢GGLShaderProgram.cpp : Compile() : Compile() completed.");
    return shader;
}

GLuint GLShaderProgram::GetFragmentShaderId() const
{
    DEBUG_MSG("GLShaderProgram.cpp : GetFragmentShaderId() : Enters GetFragmentShaderId().");
    // Return the fragment shader ID
    DEBUG_MSG("¢GGLShaderProgram.cpp : GetFragmentShaderId() : GetFragmentShaderId() completed.");
    return m_fragmentShaderId;
}
