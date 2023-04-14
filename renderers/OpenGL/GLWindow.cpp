// GLWindow.cpp

#include "GLWindow.h"
#include <Window.h>
#include <SDL.h>
#include <glad/glad.h>
#include <imgui_impl_sdl2.h>
#include <stdexcept>
#include <Debug.h>

GLWindow::GLWindow(SDL_Window* sdlWindow)
    : Window(800, 600, L"Holodesk"), m_sdlWindow(sdlWindow)
{
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
    DEBUG_MSG("GLWindow.cpp : Create() : Enters Create().");

    DEBUG_MSG("GLWindow.cpp : Create() : SDL_Init(SDL_INIT_VIDEO).");
    SDL_Init(SDL_INIT_VIDEO);

    // Set the OpenGL context attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // Update the major version to 4
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3); // Update the minor version to 3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    DEBUG_MSG("GLWindow.cpp : Create() : m_sdlWindow = SDL_CreateWindow().");
    m_sdlWindow = SDL_CreateWindow("OpenGL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width_, height_, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!m_sdlWindow)
    {
        DEBUG_MSG("�RGLWindow.cpp : Create() : Failed.");
        return false;
    }

    DEBUG_MSG("GLWindow.cpp : Create() : SDL_GL_CreateContext(m_sdlWindow);.");
    m_glContext = SDL_GL_CreateContext(m_sdlWindow); // Assign the context to the member variable
    if (m_glContext == nullptr)
    {
        DEBUG_MSG("�RGLWindow.cpp : Create() : Failed to create OpenGL context.");
        return false;
    }

    DEBUG_MSG("GLWindow.cpp : Create() : gladLoadGL.");
    if (!gladLoadGL())
    {
        DEBUG_MSG("�RGLWindow.cpp : Create() : Error: GLAD failed to initialize");
        return false;
    }
    DEBUG_MSG("�BGLWindow.cpp : Create() : GL version: ");
    cout << GLVersion.major << "." << GLVersion.minor << endl;

    // Update the width and height of the GLWindow object
    DEBUG_MSG("GLWindow.cpp : Create() : Update the width and height of the GLWindow object.");
    int windowWidth, windowHeight;
    SDL_GetWindowSize(m_sdlWindow, &windowWidth, &windowHeight);
    this->SetWidth(windowWidth);
    this->SetHeight(windowHeight);

    DEBUG_MSG("�GGLWindow.cpp : Create() : Create() Completed");
    return true;
}

void GLWindow::Close()
{
    SDL_DestroyWindow(m_sdlWindow);
    SDL_Quit();
}

bool GLWindow::ProcessEvents()
{
    DEBUG_MSG("�YGLWindow.cpp : ProcessEvents() : Enters ProcessEvents.");
    SDL_Event event;
    int newWidth;
    int newHeight;
    DEBUG_MSG("�YGLWindow.cpp : ProcessEvents() : Polling events.");
    while (SDL_PollEvent(&event))
    {
        DEBUG_MSG("�YGLWindow.cpp : ProcessEvents() : Enters while (SDL_PollEvent(&event)).");
        switch (event.type)
        {
        case SDL_WINDOWEVENT:
        DEBUG_MSG("�YGLWindow.cpp : ProcessEvents() : Enters case SDL_WINDOWEVENT.");
            switch (event.window.event)
            {
            case SDL_WINDOWEVENT_RESIZED:
            DEBUG_MSG("�YGLWindow.cpp : ProcessEvents() : Enters case SDL_WINDOWEVENT_RESIZED.");
                newWidth = event.window.data1;
                newHeight = event.window.data2;
                OnResize(newWidth, newHeight);
                break;
            default:
                DEBUG_MSG("�YGLWindow.cpp : ProcessEvents() : Enters (event.window.event) default case.");
                break;
            }
            break;
        default:
        DEBUG_MSG("�YGLWindow.cpp : ProcessEvents() : Enters (event.type) default case.");
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

void GLWindow::OnResize(int newWidth, int newHeight)
{
    DEBUG_MSG("�GGLWindow.cpp : OnResize() : Enters OnResize. ");
    // Add debug messages to print the new dimensions
    DEBUG_MSG("�GGLWindow.cpp : OnResize() : newWidth = ");
    cout << newWidth << endl;
    DEBUG_MSG("�GnewHeight = ");
    cout << newHeight << endl;

    width_ = newWidth;
    height_ = newHeight;

    // Update the viewport with the new dimensions
    glViewport(0, 0, newWidth, newHeight);
}


SDL_Window* GLWindow::GetSDLWindow() const
{
    return m_sdlWindow; // Assuming m_window is the SDL_Window* member variable
}
