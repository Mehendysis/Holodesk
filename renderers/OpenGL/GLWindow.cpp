// GLWindow.cpp

#include "GLWindow.h"
#include <Window.h>
#include <SDL.h>
#include <imgui_impl_sdl2.h>


void GLWindow::GetWindowSize(int* width, int* height) const 
{
    SDL_GetWindowSize(m_sdlWindow, width, height);
}

void GLWindow::SQLEvent(Window* window)
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

void GLWindow::Create()
{
    SDL_Init(SDL_INIT_VIDEO);
    m_sdlWindow = SDL_CreateWindow("OpenGL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width_, height_, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_GL_CreateContext(m_sdlWindow);
}

void GLWindow::Close()
{
    SDL_DestroyWindow(m_sdlWindow);
    SDL_Quit();
}

GLWindow::GLWindow(unsigned int width, unsigned int height, const std::wstring& title)
    : Window(width, height, title)
{
    Create();
}

GLWindow::~GLWindow()
{
    SDL_DestroyWindow(m_sdlWindow);
    SDL_Quit();
}

bool GLWindow::ProcessEvents()
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

GLWindow& GLWindow::GetInstance()
{
    static GLWindow instance;
    return instance;
}

void GLWindow::SwapBuffers()
{
    SDL_GL_SwapWindow(m_sdlWindow);
}

void* GLWindow::GetNativeWindowHandle() const
{
    return static_cast<void*>(m_sdlWindow);
}

