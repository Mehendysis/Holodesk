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

    DEBUG_MSG("¢BGLShaderProgram.cpp : LoadShader() : vertexShaderSource = ");
    cout << vertexShaderSource;
    DEBUG_MSG("¢BGLShaderProgram.cpp : LoadShader() : fragmentShaderSource = ");
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
}

bool GLShaderProgram::LoadFile(const std::string& fileName, std::string& fileContent)
{
    DEBUG_MSG("GLShaderProgram.cpp : LoadFile() : Enters LoadFile().");

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

    return true;
    DEBUG_MSG("¢GGLShaderProgram.cpp : LoadFile() : LoadFile() completed.");
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
    DEBUG_MSG("GLShaderProgram.cpp : Link() : Enters Link().");
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
        DEBUG_MSG("¢RGLShaderProgram.cpp : Link() : Failed to link shader program:");
        throw std::runtime_error("\n" + log);
    }

    // After glLinkProgram(shaderProgram);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        DEBUG_MSG("¢RGLShaderProgram.cpp : Link() : ERROR::SHADER::PROGRAM::LINKING_FAILED:");
        std::cout << "\n" << infoLog << std::endl;
    }

    DEBUG_MSG("¢GGLShaderProgram.cpp : Link() : Link() completed.");
    return program;
}

void GLShaderProgram::Use() const
{
    DEBUG_MSG("GLShaderProgram.cpp : Use() : Enters Use().");
    glUseProgram(m_programId);
}


void GLShaderProgram::SetUniform(const std::string& name, const glm::mat4& value) const
{
    DEBUG_MSG("GLShaderProgram.cpp : SetUniform() : Enters SetUniform().");
	GLint location = glGetUniformLocation(m_shaderProgramId, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    DEBUG_MSG("¢GGLShaderProgram.cpp : SetUniform() : SetUniform() completed.");
}


std::string GLShaderProgram::ReadShaderFile(const std::string& fileName) const
{
    DEBUG_MSG("GLShaderProgram.cpp : ReadShaderFile() : Enters ReadShaderFile().");
	return std::string();
}

GLuint GLShaderProgram::Compile(const std::string& source, GLenum type)
{
    DEBUG_MSG("GLShaderProgram.cpp : Compile() : Enters Compile().");
    GLuint shader = glCreateShader(type);
    const char* source_cstr = source.c_str();
    glShaderSource(shader, 1, &source_cstr, NULL);
    glCompileShader(shader);
    GLint success;
    GLchar infoLog[512];

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
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        DEBUG_MSG("¢RGLShaderProgram.cpp : Compile() : ERROR::SHADER::COMPILATION_FAILED: ");
        std::cout << "\n" << infoLog << std::endl;
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
