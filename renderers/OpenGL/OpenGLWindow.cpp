// OpenGLWindow.cpp
#include "OpenGLWindow.h"
#include <Window.h>
#include <SDL.h>

void OpenGLWindow::Create()
{
    SDL_Init(SDL_INIT_VIDEO);
    m_sdlWindow = SDL_CreateWindow("OpenGL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width_, height_, SDL_WINDOW_OPENGL);
    SDL_GL_CreateContext(m_sdlWindow);
}

void OpenGLWindow::Close()
{
    SDL_DestroyWindow(m_sdlWindow);
    SDL_Quit();
}

OpenGLWindow::OpenGLWindow(unsigned int width, unsigned int height, const std::wstring& title)
    : Window(width, height, title)
{
    Create();
}

OpenGLWindow::~OpenGLWindow()
{
    SDL_DestroyWindow(m_sdlWindow);
    SDL_Quit();
}

bool OpenGLWindow::ProcessEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return false;
        }
    }
    return true;
}

void OpenGLWindow::SwapBuffers()
{
    SDL_GL_SwapWindow(m_sdlWindow);
}

void* OpenGLWindow::GetNativeWindowHandle() const
{
    return static_cast<void*>(m_sdlWindow);
}
