// GLFramebuffer.cpp

#include "GLFramebuffer.h"
#include "Debug.h"
#include "UIElements.h"
#include "GLMemoryWrapper.h"

GLFramebuffer::GLFramebuffer()
{
    CreateFramebufferObject();
}

GLFramebuffer::~GLFramebuffer()
{
}

void GLFramebuffer::CreateFramebuffer()
{
    CreateFramebufferObject();
    if (isFramebufferComplete())
    {
        BindFramebufferObject();

    }
    else
    {
        DEBUG_MSG("¢RGLRenderer.cpp : CreateOpenGLTexture() : Framebuffer incomplete.");
    }
}

void GLFramebuffer::CreateFramebufferObject()
{
    // Create a framebuffer object FBO
    GLuint framebuffer = 0;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
}

void GLFramebuffer::CreateOpenGLTexture()
{
    // Create an OpenGL texture
    GLuint texture;
    glGenTextures(1, &texture);
}

void GLFramebuffer::BindTextureToFrambuffer(GLuint* texture, unsigned short int* width, unsigned short int* height)
{
    // Attach a texture to the framebuffer
    glBindTexture(GL_TEXTURE_2D, *texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *width, *height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *texture, 0);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

bool GLFramebuffer::isFramebufferComplete()
{
    // Check for framebuffer completeness
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        // Handle error
        DEBUG_MSG("¢RGLRenderer.cpp : CreateOpenGLTexture() : Framebuffer incomplete.");
        return false;
    }
    else
    {
        DEBUG_MSG("¢YGLRenderer.cpp : CreateOpenGLTexture() : Framebuffer complete.");
        return true;
    }
}

void GLFramebuffer::RenderToFramebufferObject()
{
    // Render to the framebuffer
    UIElements uiElement;
    void* width = uiElement.GetHolodeskImGuiViewportWidth();
    void* height = uiElement.GetHolodeskImGuiViewportHeight();
    glViewport(0, 0, *(GLsizei*)width, *(GLsizei*)height);
    glClear(GL_COLOR_BUFFER_BIT);
}

void GLFramebuffer::BindFramebufferObject()
{
    // Bind the default framebuffer
    //GLuint my_fbo = 0;
    //glGenFramebuffers(1, &my_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //glBindFramebuffer(GL_FRAMEBUFFER_EXT, my_fbo);
}