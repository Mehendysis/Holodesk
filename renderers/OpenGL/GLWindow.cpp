// GLWindow.cpp

#include "GLWindow.h"
#include "Window.h"
#include "Debug.h"

#include <glad/glad.h>
#include <imgui_impl_sdl2.h>
#include <SDL_syswm.h>
#include <SDL.h>
#include <locale>
#include <codecvt>


using namespace std;

GLWindow::GLWindow(unsigned short int width, unsigned short int height, std::wstring title) :
    m_CurrentWidth(width),
    m_CurrentHeight(height),
    m_WindowTitle(title)
{
    DEBUG_MSG("GLWindow.cpp : GLWindow() : Enters GLWindow() constructor.");

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        DEBUG_MSG("GLWindow.cpp : GLWindow() : Failed to initialize SDL: ");
        cout << std::string(SDL_GetError()) << endl;
        exit(EXIT_FAILURE);
    }

    // Create an SDL window
    Window initialWindow;
    std::wstring wideTitle = initialWindow.GetHoloWinTitle();
    int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wideTitle.c_str(), -1, nullptr, 0, nullptr, nullptr);
    std::string titleStr(bufferSize, 0);
    WideCharToMultiByte(CP_UTF8, 0, wideTitle.c_str(), -1, titleStr.data(), bufferSize, nullptr, nullptr);
    m_sdlWindow = SDL_CreateWindow(titleStr.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (!m_sdlWindow)
    {
        DEBUG_MSG("GLWindow.cpp : GLWindow() : Failed to create SDL window: ");
        cout << std::string(SDL_GetError());
        exit(EXIT_FAILURE);
    }
    int* intPointerWidth = reinterpret_cast<int*>(&width);
    int* intPointerHeight = reinterpret_cast<int*>(&height);
    // Get the actual window size
    SDL_GetWindowSize(m_sdlWindow, intPointerWidth, intPointerHeight);

}

GLWindow::~GLWindow()
{
    //if (glContext != nullptr)
    //{
    //    SDL_GL_DeleteContext(glContext);
    //}
    if (m_sdlWindow != nullptr) 
    {
        SDL_DestroyWindow(m_sdlWindow);
    }
}

void GLWindow::GetCurrentWindowSize(unsigned short int* pWidth, unsigned short int* pHeight) const
{
    int intWidth;
    int intHeight;
    SDL_GetWindowSize(m_sdlWindow, &intWidth, &intHeight);
    *pWidth = static_cast<unsigned short int>(intWidth);
    *pHeight = static_cast<unsigned short int>(intHeight);
}

unsigned short int GLWindow::GetCurrentWidth() const
{
    return m_CurrentWidth;
}

unsigned short int GLWindow::GetCurrentHeight() const
{
    return m_CurrentHeight;
}

const std::wstring GLWindow::getTitle() const
{
    return m_WindowTitle;
}
void GLWindow::SetWidth(unsigned short int width)
{
    m_CurrentWidth = width;
}

void GLWindow::SetHeight(unsigned short int height)
{
    m_CurrentHeight = height;
}

void GLWindow::Quit()
{
    m_IsClosed = true;
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

    Window initialWindow;
    unsigned short int windowWidth = initialWindow.GetInitialWidth();
    unsigned short int windowHeight = initialWindow.GetInitialHeight();

    DEBUG_MSG("GLWindow.cpp : Create() : m_sdlWindow = SDL_CreateWindow().");
    m_sdlWindow = SDL_CreateWindow("OpenGL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!m_sdlWindow)
    {
        DEBUG_MSG("¢RGLWindow.cpp : Create() : Failed.");
        return false;
    }

    DEBUG_MSG("GLWindow.cpp : Create() : SDL_GL_CreateContext(m_sdlWindow);.");
    SDL_GLContext glContext = SDL_GL_CreateContext(m_sdlWindow); // Assign the context to the member variable
    if (glContext == nullptr)
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

    SDL_GL_MakeCurrent(m_sdlWindow, glContext);

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
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(m_sdlWindow);
    m_sdlWindow = nullptr;
    glContext = nullptr;
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

void GLWindow::OnResize(unsigned short int newWidth, unsigned short int newHeight)
{
    DEBUG_MSG("¢GGLWindow.cpp : OnResize() : Enters OnResize. ");
    // Add debug messages to print the new dimensions
    DEBUG_MSG("¢GGLWindow.cpp : OnResize() : newWidth = ");
    cout << newWidth << endl;
    DEBUG_MSG("¢GnewHeight = ");
    cout << newHeight << endl;

    SetWidth(newWidth);
    SetHeight(newHeight);

    // Update the viewport with the new dimensions
    glViewport(0, 0, newWidth, newHeight);
}

void GLWindow::Resize(unsigned short int width, unsigned short int height)
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

SDL_Window* GLWindow::GetWindowHandle() const
{
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(m_sdlWindow, &wmInfo);
    return wmInfo.info.win.window;
}

SDL_Window* GLWindow::GetSDLWindow() const
{
    return m_sdlWindow;
}
