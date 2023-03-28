// OpenGLWindow.cpp
#include "OpenGLWindow.h"
#include <Window.h>
#include <SDL.h>
#include <imgui_impl_sdl2.h>

void OpenGLWindow::GetWindowSize(int* width, int* height) const 
{
    SDL_GetWindowSize(m_sdlWindow, width, height);
}

void OpenGLWindow::SQLEvent(Window* window)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);

        if (event.type == SDL_QUIT)
        {
            window->Quit();
        }
        else if (event.type == SDL_WINDOWEVENT)
        {
            if (event.window.event == SDL_WINDOWEVENT_MAXIMIZED)
            {
                int screenWidth, screenHeight;
                SDL_GetWindowSize(m_sdlWindow, &screenWidth, &screenHeight);
                SDL_SetWindowSize(m_sdlWindow, screenWidth, screenHeight);
            }
            // Handle window resize events
            else if (event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                int screenWidth, screenHeight;
                SDL_GetWindowSize(m_sdlWindow, &screenWidth, &screenHeight);
                ImGuiIO& io = ImGui::GetIO();
                io.DisplaySize = ImVec2((float)screenWidth, (float)screenHeight);
            }
        }
    }
}

void OpenGLWindow::Create()
{
    SDL_Init(SDL_INIT_VIDEO);
    m_sdlWindow = SDL_CreateWindow("OpenGL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width_, height_, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
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
