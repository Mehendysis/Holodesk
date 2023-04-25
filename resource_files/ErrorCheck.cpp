//ErrorCheck.cpp
#include "ErrorCheck.h"
#include "Debug.h"
#include <vector>
#include <GLShaderProgram.h>

//#include <glm/ext/matrix_float4x4.hpp>

using namespace std;

void check_frame_buffer(GLuint framebufferObject)
{
    // Bind the framebuffer object
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferObject);

    // Check if the framebuffer is complete
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        // Print out the error message
        GLenum err = glGetError();
        switch (err)
        {
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            std::cerr << "Error: Framebuffer incomplete attachment" << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            std::cerr << "Error: Framebuffer incomplete missing attachment" << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
            std::cerr << "Error: Framebuffer incomplete draw buffer" << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
            std::cerr << "Error: Framebuffer incomplete read buffer" << std::endl;
            break;
        case GL_FRAMEBUFFER_UNSUPPORTED:
            std::cerr << "Error: Framebuffer unsupported" << std::endl;
            break;
        default:
            std::cerr << "Error: Unknown framebuffer error (" << err << ")" << std::endl;
            break;
        }

        // Print out the attachment status for each attachment in the framebuffer object
        GLint numAttachments;
        glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &numAttachments);
        for (GLint i = 0; i < numAttachments; i++)
        {
            GLenum attachment = GL_COLOR_ATTACHMENT0 + i;
            GLint attachmentStatus;
            glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &attachmentStatus);
            if (attachmentStatus != GL_NONE)
            {
                std::cerr << "Attachment " << attachment << " status: " << attachmentStatus << std::endl;
            }
        }
    }

    // Unbind the framebuffer object
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void check_frame_buffer_additonal_message(GLuint framebufferObject)
{
    // Bind the framebuffer object
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferObject);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        // Print out framebuffer object ID
        std::cerr << "Error: Framebuffer object ID: " << framebufferObject << std::endl;

        GLenum err = glGetError();

        // Print out error code
        std::cerr << "Error: glGetError code: " << err << std::endl;

        // Print out attachment's status
        GLint attachmentStatus = 0;
        glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &attachmentStatus);
        std::cerr << "Attachment status: " << attachmentStatus << std::endl;

        switch (status)
        {
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            std::cerr << "Error: Framebuffer incomplete attachment" << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            std::cerr << "Error: Framebuffer incomplete missing attachment" << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
            std::cerr << "Error: Framebuffer incomplete draw buffer" << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
            std::cerr << "Error: Framebuffer incomplete read buffer" << std::endl;
            break;
        case GL_FRAMEBUFFER_UNSUPPORTED:
            std::cerr << "Error: Framebuffer unsupported" << std::endl;
            break;
        default:
            std::cerr << "Error: Unknown framebuffer error (" << status << ")" << std::endl;
            break;
        }
    }

    // Unbind the framebuffer object
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void APIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    DEBUG_MSG("¢YErrorCheck.cpp : debugCallback()");
    DEBUG_MSG("¢YOpenGL Debug Message source: ");
    cout << source;
    DEBUG_MSG("¢Y, type: ");
    cout << type;
    DEBUG_MSG("¢Y, id: ");
    cout << id;
    DEBUG_MSG("¢Y, severity: ");
    cout << severity;
    DEBUG_MSG("¢Y): ");
    cout << message;
    // Log the debug message
    printf("OpenGL Debug Message (source: %d, type: %d, id: %d, severity: %d):\n%s\n", source, type, id, severity, message);
    cout << endl;
    if (severity == GL_DEBUG_SEVERITY_HIGH || severity == GL_DEBUG_SEVERITY_MEDIUM) 
    {
        std::cerr << "OpenGL Debug Message (source: " << source << ", type: " << type << ", id: " << id
            << ", severity: " << severity << "):\n" << message << std::endl;
    }
}

bool check_aspect_ratio_error(const glm::mat4& projection_matrix)
{
    const float aspect = projection_matrix[1][1] / projection_matrix[0][0];
    constexpr float epsilon = std::numeric_limits<float>::epsilon();
    const bool aspect_ratio_error = std::abs(aspect - epsilon) < epsilon;

    if (aspect_ratio_error) 
    {
        DEBUG_MSG("¢RErrorCheck.cpp : check_aspect_ratio_error() : Error below.");
        std::cerr << "Aspect ratio error detected: "
            << "aspect = " << aspect << ", "
            << "epsilon = " << epsilon << std::endl;
    }

    return aspect_ratio_error;
}

//bool ShadersCompiled(const std::unique_ptr<GLShaderProgram>& shaderProgram)
//{
//    // Check if vertex shader compiled successfully
//    GLint isCompiled = 0;
//    GLuint shaderProgramId = shaderProgram->GetProgramId();
//    glGetShaderiv(shaderProgram->GetVertexShaderId(), GL_COMPILE_STATUS, &isCompiled);
//    if (isCompiled == GL_FALSE) {
//        GLint maxLength = 0;
//        glGetShaderiv(shaderProgram->GetVertexShaderId(), GL_INFO_LOG_LENGTH, &maxLength);
//        std::vector<GLchar> errorLog(maxLength);
//        glGetShaderInfoLog(shaderProgram->GetVertexShaderId(), maxLength, &maxLength, &errorLog[0]);
//        // Output error log to console or log file
//        return false;
//    }
//
//    // Check if fragment shader compiled successfully
//    glGetShaderiv(shaderProgram->GetFragmentShaderId(), GL_COMPILE_STATUS, &isCompiled);
//    if (isCompiled == GL_FALSE) {
//        GLint maxLength = 0;
//        glGetShaderiv(shaderProgram->GetFragmentShaderId(), GL_INFO_LOG_LENGTH, &maxLength);
//        std::vector<GLchar> errorLog(maxLength);
//        glGetShaderInfoLog(shaderProgram->GetFragmentShaderId(), maxLength, &maxLength, &errorLog[0]);
//        // Output error log to console or log file
//        return false;
//    }
//
//    // Check if program linked successfully
//    GLint isLinked = 0;
//   
//    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &isLinked);
//    if (isLinked == GL_FALSE) {
//        GLint maxLength = 0;
//        glGetProgramiv(shaderProgramId, GL_INFO_LOG_LENGTH, &maxLength);
//        std::vector<GLchar> errorLog(maxLength);
//        glGetProgramInfoLog(shaderProgramId, maxLength, &maxLength, &errorLog[0]);
//        // Output error log to console or log file
//        return false;
//    }
//
//    // Program is valid, can be used for rendering
//    return true;
//
//}