//ErrorCheck.cpp
#include "ErrorCheck.h"
#include "Debug.h"

#include <SDL.h>
#include <iostream>
#include <glad/glad.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_clip_space.hpp>

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
    DEBUG_MSG("¢YOpenGL Debug Message (source: ");
    cout << source;
    DEBUG_MSG("¢Y, type: ");
    cout << type;
    DEBUG_MSG("¢Y, id: ");
    cout << id;
    DEBUG_MSG("¢Y, severity: ");
    cout << severity;
    DEBUG_MSG("¢Y): ");
    cout << message;
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

bool initialize_sdl_and_opengl(SDL_Window*& window, SDL_GLContext& context)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        DEBUG_MSG("¢RErrorCheck.cpp : initialize_sdl_and_opengl() : Error below.");
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // set OpenGL context version to 4.3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow("OpenGL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window)
    {
        DEBUG_MSG("¢RErrorCheck.cpp : initialize_sdl_and_opengl() : Error below.");
        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    context = SDL_GL_CreateContext(window);
    if (!context)
    {
        DEBUG_MSG("¢RErrorCheck.cpp : initialize_sdl_and_opengl() : Error below.");
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    if (gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress) == 0)
    {
        DEBUG_MSG("¢RErrorCheck.cpp : initialize_sdl_and_opengl() : Error below.");
        std::cerr << "Failed to initialize GLAD" << std::endl;
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    glm::mat4 projection_matrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    if (check_aspect_ratio_error(projection_matrix))
    {
        DEBUG_MSG("¢RErrorCheck.cpp : initialize_sdl_and_opengl() : Error Quit.");
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    return true;
}

