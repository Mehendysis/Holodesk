// GLWindow.cpp

#include "GLWindow.h"
#include <Window.h>
#include <SDL.h>
#include <imgui_impl_sdl2.h>
#include <stdexcept>
#include <Debug.h>

GLWindow::GLWindow(SDL_Window* sdlWindow)
    : Window(800, 600, L"Holodesk"), m_sdlWindow(sdlWindow)
{
    m_glContext = SDL_GL_CreateContext(m_sdlWindow);
    if (m_glContext == nullptr) 
    {
        throw std::runtime_error("Failed to create OpenGL context.");
    }
}

GLWindow::~GLWindow()
{
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_sdlWindow);
    SDL_Quit();
}

void GLWindow::GetWindowSize(int* width, int* height) const
{
    SDL_GetWindowSize(m_sdlWindow, width, height);
    const_cast<GLWindow*>(this)->SetWidth(*width);
    const_cast<GLWindow*>(this)->SetHeight(*height);
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
            int width, height;
            SDL_GetWindowSize(m_sdlWindow, &width, &height);
            window->SetWidth(width);
            window->SetHeight(height);

            // Update ImGui display size
            ImGuiIO& io = ImGui::GetIO();
            io.DisplaySize = ImVec2((float)width, (float)height);
        }
    }
}

bool GLWindow::Create()
{
    DEBUG_MSG("GLWindow.cpp : Create() : SDL_Init(SDL_INIT_VIDEO).");
    SDL_Init(SDL_INIT_VIDEO);
    DEBUG_MSG("GLWindow.cpp : Create() : m_sdlWindow = SDL_CreateWindow().");
    m_sdlWindow = SDL_CreateWindow("OpenGL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width_, height_, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!m_sdlWindow)
    {
        DEBUG_MSG("¢RGLWindow.cpp : Create() : Failed.");
        return false;
    }

    DEBUG_MSG("GLWindow.cpp : Create() : SDL_GL_CreateContext(m_sdlWindow);.");
    SDL_GL_CreateContext(m_sdlWindow);

    // Update the width and height of the GLWindow object
    DEBUG_MSG("GLWindow.cpp : Create() : Update the width and height of the GLWindow object.");

    DEBUG_MSG("GLWindow.cpp : Create() : int windowWidth, windowHeight;.");
    int windowWidth, windowHeight;
    DEBUG_MSG("GLWindow.cpp : Create() : SDL_GetWindowSize().");
    SDL_GetWindowSize(m_sdlWindow, &windowWidth, &windowHeight);
    DEBUG_MSG("GLWindow.cpp : Create() : GetInstance().SetWidth(windowWidth);.");
    this->SetWidth(windowWidth);
    DEBUG_MSG("GLWindow.cpp : Create() : GetInstance().SetHeight(windowHeight);.");
    this->SetHeight(windowHeight);

    DEBUG_MSG("GLWindow.cpp : Create() : Completed");
    return true;
}

void GLWindow::Close()
{
    SDL_DestroyWindow(m_sdlWindow);
    SDL_Quit();
}

bool GLWindow::ProcessEvents()
{
    SDL_Event event;
    int newWidth;
    int newHeight;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            // ...
        case SDL_WINDOWEVENT:
            switch (event.window.event)
            {
                // ...
            case SDL_WINDOWEVENT_RESIZED:
                newWidth = event.window.data1;
                newHeight = event.window.data2;
                OnResize(newWidth, newHeight);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
    return true;
}

GLWindow& GLWindow::GetInstance()
{
    static GLWindow instance(nullptr);
    if (instance.m_sdlWindow == nullptr) {
        throw std::runtime_error("GLWindow instance not initialized.");
    }
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

void GLWindow::OnResize(int width, int height) 
{
    width_ = width;
    height_ = height;
}
