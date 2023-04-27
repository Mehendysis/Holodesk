#include "GLShaderLoader.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include "utils.h"

GLShaderLoader::GLShaderLoader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
    m_shaderProgram = loadShaders(vertexShaderPath, fragmentShaderPath);
}

GLShaderLoader::~GLShaderLoader()
{
    // Delete the shader program if it exists
    if (m_shaderProgram != 0)
    {
        glDeleteProgram(m_shaderProgram);
        m_shaderProgram = 0;
    }
}
GLuint GLShaderLoader::loadShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    // Create the shader program
    GLuint programID = glCreateProgram();

    // Load and compile vertex shader
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    std::string vertexShaderCode = loadShaderSource(vertexShaderPath.c_str());
    const char* vertexShaderSource = vertexShaderCode.c_str();
    glShaderSource(vertexShaderID, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShaderID);
    checkShaderErrors(vertexShaderID);

    // Load and compile fragment shader
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentShaderCode = loadShaderSource(fragmentShaderPath.c_str());
    const char* fragmentShaderSource = fragmentShaderCode.c_str();
    glShaderSource(fragmentShaderID, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShaderID);
    checkShaderErrors(fragmentShaderID);

    // Attach shaders and link the shader program
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);
    checkProgramErrors(programID);

    // Clean up
    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return programID;
}

std::string GLShaderLoader::loadShaderSource(const char* shaderPath) const
{
    std::ifstream shaderFile;
    std::stringstream shaderStream;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        shaderFile.open(shaderPath);
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
    }
    catch (std::ifstream::failure& e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << shaderPath << "\n";
        std::cerr << "Exception message: " << e.what() << "\n";
    }

    std::string shaderCode = shaderStream.str();

    if (shaderCode.empty()) {
        std::cerr << "ERROR::SHADER::SOURCE_NOT_LOADED: " << shaderPath << "\n";
    }
    else {
        std::cout << "Shader loaded successfully: " << shaderPath << "\n";
    }

    return shaderCode;
}

void GLShaderLoader::checkShaderErrors(GLuint shaderID)
{
    GLint result = GL_FALSE;
    int infoLogLength;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 0) {
        std::vector<char> errorMessage(infoLogLength + 1);
        glGetShaderInfoLog(shaderID, infoLogLength, NULL, &errorMessage[0]);
        std::cerr << &errorMessage[0] << std::endl;
    }
}

void GLShaderLoader::checkProgramErrors(GLuint programID) {
    GLint success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);

    if (!success) {
        GLchar infoLog[1024];
        glGetProgramInfoLog(programID, 1024, NULL, infoLog);
        std::cerr << "ERROR::PROGRAM_LINKING_FAILED\n" << infoLog << "\n";
    }

    glValidateProgram(programID);
    glGetProgramiv(programID, GL_VALIDATE_STATUS, &success);

    if (!success) {
        GLchar infoLog[1024];
        glGetProgramInfoLog(programID, 1024, NULL, infoLog);
        std::cerr << "ERROR::PROGRAM_VALIDATION_FAILED\n" << infoLog << "\n";
    }
}



void GLShaderLoader::use() const
{
    glUseProgram(m_shaderProgram);
}

GLuint GLShaderLoader::getProgram() const
{
    return m_shaderProgram;
}


//
///*
//This is the constructor for the ShaderLoader class that takes in the paths of a vertex shader and a fragment shader as arguments.
//It first creates a GLuint variable for the vertex shader using glCreateShader(GL_VERTEX_SHADER).
//It then loads the source code of the vertex shader from the file path provided using the loadShaderSource function,
//compiles the shader using glCompileShader, and checks for any compilation errors using checkShaderCompilation.
//Next, it repeats the same process for the fragment shader, but using glCreateShader(GL_FRAGMENT_SHADER) instead.
//After the vertex and fragment shaders have been compiled and checked, it creates a shader program using glCreateProgram.
//It then attaches both the vertex and fragment shaders to the shader program using glAttachShader.Finally,
//it links the shader program using glLinkProgram and checks for any linking errors using checkProgramLinking.
//Once the shader program has been successfully linked, the constructor deletes the shader objects using glDeleteShader to free up memory.
//GLShaderLoader::ShaderLoader(const char* vertexShaderPath, const char* fragmentShaderPath)
//*/
//
//GLShaderLoader::ShaderLoader(const char* vertexShaderPath, const char* fragmentShaderPath)
//{
//    // Display shader file paths
//    std::cout << "Loading vertex shader: " << vertexShaderPath << std::endl;
//    std::cout << "Loading fragment shader: " << fragmentShaderPath << std::endl;
//
//    // Load and compile vertex shader
//    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    std::string vertexShaderSource = loadShaderSource(vertexShaderPath);
//    const GLchar* vertexShaderSourcePtr = vertexShaderSource.c_str();
//    glShaderSource(vertexShader, 1, &vertexShaderSourcePtr, NULL);
//    glCompileShader(vertexShader);
//    checkShaderCompilation(vertexShader);
//
//    // Load and compile fragment shader
//    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    std::string fragmentShaderSource = loadShaderSource(fragmentShaderPath);
//    const GLchar* fragmentShaderSourcePtr = fragmentShaderSource.c_str();
//    glShaderSource(fragmentShader, 1, &fragmentShaderSourcePtr, NULL);
//    glCompileShader(fragmentShader);
//    checkShaderCompilation(fragmentShader);
//
//    // Create and link shader program
//    m_shaderProgram = glCreateProgram();
//    glAttachShader(m_shaderProgram, vertexShader);
//    glAttachShader(m_shaderProgram, fragmentShader);
//    glLinkProgram(m_shaderProgram);
//    checkProgramLinking(m_shaderProgram);
//
//    // Delete the shader objects once the shader program is linked
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//}
//
///*
//This function loads and compiles a vertex shader and a fragment shader, and then links them to a shader program. 
//It takes two parameters: the file paths for the vertex shader and the fragment shader.
//First, it creates a shader program with glCreateProgram(). Then it loads the vertex shader with glCreateShader(GL_VERTEX_SHADER) and 
//reads the code from the specified file path with readFile(vertexPath). It compiles the vertex shader with glCompileShader(vertexShaderID) and 
//checks for any errors with checkShaderErrors(vertexShaderID).
//Next, it loads the fragment shader with glCreateShader(GL_FRAGMENT_SHADER) and reads the code from the specified file path with readFile(fragmentPath). 
//It compiles the fragment shader with glCompileShader(fragmentShaderID) and checks for any errors with checkShaderErrors(fragmentShaderID).
//Finally, it attaches both shaders to the program with glAttachShader(programID, vertexShaderID) and glAttachShader(programID, fragmentShaderID), 
//respectively. It links the program with glLinkProgram(programID) and checks for any errors with checkProgramErrors(programID).
//The function then cleans up the shader objects with glDeleteShader(vertexShaderID) and glDeleteShader(fragmentShaderID). 
//Finally, it returns the ID of the shader program.
//*/
//
//GLuint GLShaderLoader::loadShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) 
//{
//    // Create the shader program
//    GLuint programID = glCreateProgram();
//
//    // Load the vertex shader
//    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
//    std::string vertexShaderCode = loadShaderSource(vertexShaderPath.c_str());
//    const char* vertexShaderSource = vertexShaderCode.c_str();
//    glShaderSource(vertexShaderID, 1, &vertexShaderSource, NULL);
//    glCompileShader(vertexShaderID);
//    checkShaderErrors(vertexShaderID);
//
//    if (vertexShaderCode.empty()) {
//        std::cerr << "ERROR::VERTEX_SHADER::SOURCE_NOT_LOADED\n";
//    }
//    else {
//        std::cout << "Vertex shader loaded successfully.\n";
//    }
//
//    // Load the fragment shader
//    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
//    std::string fragmentShaderCode = loadShaderSource(fragmentShaderPath.c_str());
//    const char* fragmentShaderSource = fragmentShaderCode.c_str();
//    glShaderSource(fragmentShaderID, 1, &fragmentShaderSource, NULL);
//    glCompileShader(fragmentShaderID);
//    checkShaderErrors(fragmentShaderID);
//
//    if (fragmentShaderCode.empty()) {
//        std::cerr << "ERROR::FRAGMENT_SHADER::SOURCE_NOT_LOADED\n";
//    }
//    else {
//        std::cout << "Fragment shader loaded successfully.\n";
//    }
//
//    // Attach shaders and link the shader program
//    glAttachShader(programID, vertexShaderID);
//    glAttachShader(programID, fragmentShaderID);
//    glLinkProgram(programID);
//    checkProgramErrors(programID);
//
//    // Clean up
//    glDetachShader(programID, vertexShaderID);
//    glDetachShader(programID, fragmentShaderID);
//    glDeleteShader(vertexShaderID);
//    glDeleteShader(fragmentShaderID);
//
//    return programID;
//}
//
//std::string GLShaderLoader::loadShaderSource(const char* shaderPath) const
//{
//    std::ifstream shaderFile;
//    std::stringstream shaderStream;
//    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//
//    try {
//        shaderFile.open(shaderPath);
//        shaderStream << shaderFile.rdbuf();
//        shaderFile.close();
//    }
//    catch (std::ifstream::failure& e) {
//        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << shaderPath << "\n";
//        std::cerr << "Exception message: " << e.what() << "\n";
//    }
//
//    std::string shaderCode = shaderStream.str();
//
//    if (shaderCode.empty()) {
//        std::cerr << "ERROR::SHADER::SOURCE_NOT_LOADED: " << shaderPath << "\n";
//    }
//    else {
//        std::cout << "Shader loaded successfully: " << shaderPath << "\n";
//    }
//
//    return shaderCode;
//}
//
//void GLShaderLoader::checkShaderErrors(GLuint shaderID)
//{
//    GLint result = GL_FALSE;
//    int infoLogLength;
//    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
//    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
//
//    if (infoLogLength > 0) {
//        std::vector<char> errorMessage(infoLogLength + 1);
//        glGetShaderInfoLog(shaderID, infoLogLength, NULL, &errorMessage[0]);
//        std::cerr << &errorMessage[0] << std::endl;
//    }
//}
//
//void GLShaderLoader::checkProgramErrors(GLuint programID) {
//    GLint success;
//    glGetProgramiv(programID, GL_LINK_STATUS, &success);
//
//    if (!success) {
//        GLchar infoLog[1024];
//        glGetProgramInfoLog(programID, 1024, NULL, infoLog);
//        std::cerr << "ERROR::PROGRAM_LINKING_FAILED\n" << infoLog << "\n";
//    }
//
//    glValidateProgram(programID);
//    glGetProgramiv(programID, GL_VALIDATE_STATUS, &success);
//
//    if (!success) {
//        GLchar infoLog[1024];
//        glGetProgramInfoLog(programID, 1024, NULL, infoLog);
//        std::cerr << "ERROR::PROGRAM_VALIDATION_FAILED\n" << infoLog << "\n";
//    }
//}
//
//
//GLShaderLoader::~ShaderLoader()
//{
//    // Delete the shader program if it exists
//    if (m_shaderProgram != 0)
//    {
//        glDeleteProgram(m_shaderProgram);
//        m_shaderProgram = 0;
//    }
//}
//
//unsigned int GLShaderLoader::loadShader(const char* vertexPath, const char* fragmentPath) {
//    // Load the vertex shader
//    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
//    std::string vertexShaderCode = Utils::readFile(vertexPath);
//    const char* vertexShaderSource = vertexShaderCode.c_str();
//    glShaderSource(vertexShaderID, 1, &vertexShaderSource, NULL);
//    glCompileShader(vertexShaderID);
//    checkShaderErrors(vertexShaderID);
//
//    // Load the fragment shader
//    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
//    std::string fragmentShaderCode = Utils::readFile(fragmentPath);
//    const char* fragmentShaderSource = fragmentShaderCode.c_str();
//    glShaderSource(fragmentShaderID, 1, &fragmentShaderSource, NULL);
//    glCompileShader(fragmentShaderID);
//    checkShaderErrors(fragmentShaderID);
//
//    // Link the program
//    GLuint programID = glCreateProgram();
//    glAttachShader(programID, vertexShaderID);
//    glAttachShader(programID, fragmentShaderID);
//    glLinkProgram(programID);
//    checkProgramErrors(programID);
//
//    // Clean up shaders
//    glDetachShader(programID, vertexShaderID);
//    glDetachShader(programID, fragmentShaderID);
//    glDeleteShader(vertexShaderID);
//    glDeleteShader(fragmentShaderID);
//
//    return programID;
//}
//
//void GLShaderLoader::checkShaderCompilation(GLuint shader) const
//{
//    GLint success;
//    GLchar infoLog[1024];
//    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
//        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//    }
//}
//
//void GLShaderLoader::checkProgramLinking(GLuint program) const
//{
//    GLint success;
//    GLchar infoLog[1024];
//    glGetProgramiv(program, GL_LINK_STATUS, &success);
//    if (!success)
//    {
//        glGetProgramInfoLog(program, 1024, NULL, infoLog);
//        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//    }
//}
//
//void GLShaderLoader::use() const
//{
//    glUseProgram(programID);
//}
//
//GLuint GLShaderLoader::getProgram() const 
//{
//    return m_shaderProgram;
//}
//
//
