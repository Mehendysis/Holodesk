// GLWindow.cpp

#include "GLWindow.h"
#include "Window.h"
#include "Debug.h"

//#include <SDL.h>
#include <glad/glad.h>
#include <imgui_impl_sdl2.h>
//#include <stdexcept>

#include <SDL_syswm.h>

using namespace std;

GLWindow::GLWindow(int windowWidth, int windowHeight, const std::wstring& title)
    : Window(windowWidth, windowHeight, title)
{
    DEBUG_MSG("GLWindow.cpp : GLWindow() : Enters GLWindow() constructor.");
}

GLWindow::~GLWindow()
{
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_sdlWindow);
    //SDL_Quit();
}

void GLWindow::GetWindowSize(int* width, int* height) const
{
    SDL_GetWindowSize(m_sdlWindow, width, height);
}

void GLWindow::SetWidth(unsigned int width) 
{
    m_width = width;
}

void GLWindow::SetHeight(unsigned int height)
{
    m_height = height;
}

void GLWindow::SQLEvent()
{
    DEBUG_MSG("GLWindow.cpp : SQLEvent() : Enters SQLEvent().");
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);

        if (event.type == SDL_QUIT)
        {
            DEBUG_MSG("GLWindow.cpp : SQLEvent() : window->Quit();.");
            Quit();
        }
        else if (event.type == SDL_WINDOWEVENT)
        {
            DEBUG_MSG("GLWindow.cpp : SQLEvent() : Set SQL window size.");
            int width, height;
            SDL_GetWindowSize(m_sdlWindow, &width, &height);
            SetWidth(width);
            SetHeight(height);

            // Update ImGui display size
            DEBUG_MSG("GLWindow.cpp : SQLEvent() : Update ImGui display size.");
            DEBUG_MSG("GLWindow.cpp : SQLEvent() : Get ImGui io.");
            ImGuiIO& io = ImGui::GetIO();
            DEBUG_MSG("GLWindow.cpp : SQLEvent() : Update ImGui display size : io.DisplaySize");
            io.DisplaySize = ImVec2((float)width, (float)height);
        }
    }
    DEBUG_MSG("¢GGLWindow.cpp : SQLEvent() :  SQLEvent() completed.");
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
    m_sdlWindow = SDL_CreateWindow("OpenGL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!m_sdlWindow)
    {
        DEBUG_MSG("¢RGLWindow.cpp : Create() : Failed.");
        return false;
    }

    DEBUG_MSG("GLWindow.cpp : Create() : SDL_GL_CreateContext(m_sdlWindow);.");
    m_glContext = SDL_GL_CreateContext(m_sdlWindow); // Assign the context to the member variable
    if (m_glContext == nullptr)
    {
        DEBUG_MSG("¢RGLWindow.cpp : Create() : Failed to create OpenGL context.");
        return false;
    }

    DEBUG_MSG("GLWindow.cpp : Create() : gladLoadGL.");
    if (!gladLoadGL())
    {
        DEBUG_MSG("¢RGLWindow.cpp : Create() : Error: GLAD failed to initialize");
        return false;
    }

    SDL_GL_MakeCurrent(m_sdlWindow, m_glContext);

    DEBUG_MSG("¢BGLWindow.cpp : Create() : GL version: ");
    cout << GLVersion.major << "." << GLVersion.minor << endl;

    // Update the width and height of the GLWindow object
    DEBUG_MSG("GLWindow.cpp : Create() : Update the width and height of the GLWindow object.");
    int windowWidth, windowHeight;
    SDL_GetWindowSize(m_sdlWindow, &windowWidth, &windowHeight);
    this->SetWidth(windowWidth);
    this->SetHeight(windowHeight);

    DEBUG_MSG("¢GGLWindow.cpp : Create() : Create() Completed");
    return true;
}

void GLWindow::Close()
{
    SDL_DestroyWindow(m_sdlWindow);
    SDL_Quit();
}

bool GLWindow::ProcessEvents()
{
    DEBUG_MSG("¢YGLWindow.cpp : ProcessEvents() : Enters ProcessEvents.");
    SDL_Event event;
    int newWidth;
    int newHeight;
    DEBUG_MSG("¢YGLWindow.cpp : ProcessEvents() : Polling events.");
    while (SDL_PollEvent(&event))
    {
        DEBUG_MSG("¢YGLWindow.cpp : ProcessEvents() : Enters while (SDL_PollEvent(&event)).");
        switch (event.type)
        {
        case SDL_WINDOWEVENT:
        DEBUG_MSG("¢YGLWindow.cpp : ProcessEvents() : Enters case SDL_WINDOWEVENT.");
            switch (event.window.event)
            {
            case SDL_WINDOWEVENT_RESIZED:
            DEBUG_MSG("¢YGLWindow.cpp : ProcessEvents() : Enters case SDL_WINDOWEVENT_RESIZED.");
                newWidth = event.window.data1;
                newHeight = event.window.data2;
                OnResize(newWidth, newHeight);
                break;
            default:
                DEBUG_MSG("¢YGLWindow.cpp : ProcessEvents() : Enters (event.window.event) default case.");
                break;
            }
            break;
        default:
        DEBUG_MSG("¢YGLWindow.cpp : ProcessEvents() : Enters (event.type) default case.");
            break;
        }
    }
    return true;
}

GLWindow& GLWindow::GetInstance()
{
    static std::unique_ptr<GLWindow> instance;
    if (!instance)
    {
        instance = std::make_unique<GLWindow>(1280, 720, L"Holodesk");
    }

    if (instance->m_sdlWindow == nullptr)
    {
        throw std::runtime_error("GLWindow instance not initialized.");
    }
    return *instance;
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
    DEBUG_MSG("¢GGLWindow.cpp : OnResize() : Enters OnResize. ");
    // Add debug messages to print the new dimensions
    DEBUG_MSG("¢GGLWindow.cpp : OnResize() : newWidth = ");
    cout << newWidth << endl;
    DEBUG_MSG("¢GnewHeight = ");
    cout << newHeight << endl;

    m_width = newWidth;
    m_height = newHeight;

    // Update the viewport with the new dimensions
    glViewport(0, 0, newWidth, newHeight);
}

void GLWindow::Resize(int width, int height) 
{
    SDL_SetWindowSize(m_sdlWindow, width, height);
}

void GLWindow::Minimize()
{
    SDL_MinimizeWindow(m_sdlWindow);
}

void GLWindow::Maximize()
{
    SDL_MaximizeWindow(m_sdlWindow);
}

HWND GLWindow::GetWindowHandle() const 
{
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(m_sdlWindow, &wmInfo);
    return wmInfo.info.win.window;
}

SDL_Window* GLWindow::GetSDLWindow() const
{
    return m_sdlWindow; // Assuming m_window is the SDL_Window* member variable
}

SDL_GLContext GLWindow::GetOpenGLContext() const
{
    return m_glContext;
}
