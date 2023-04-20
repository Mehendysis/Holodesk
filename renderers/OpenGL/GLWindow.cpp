// GLWindow.cpp

#include "GLWindow.h"
#include "Window.h"
#include "Debug.h"
#include "GLMemoryWrapper.h"

//#include <glad/glad.h>
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

GLWindow::GLWindow() : m_sdlWindow(nullptr), m_glContext(nullptr)
{
    DEBUG_MSG("GLWindow.cpp : GLWindow() : Constructor.");

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        DEBUG_MSG("¢RErrorCheck.cpp : GLWindow() : Error below.");
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        throw std::runtime_error("Failed to initialize SDL.");
    }

    // Set the OpenGL context attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // Update the major version to 4
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3); // Update the minor version to 3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    Window initialWindow;
    unsigned short int windowWidth = initialWindow.GetInitialWidth();
    unsigned short int windowHeight = initialWindow.GetInitialHeight();
    std::wstring wTitle = initialWindow.GetHoloWinTitle();
    int len = WideCharToMultiByte(CP_UTF8, 0, wTitle.c_str(), -1, NULL, 0, NULL, NULL);
    std::string title(len, 0);
    WideCharToMultiByte(CP_UTF8, 0, wTitle.c_str(), -1, &title[0], len, NULL, NULL);

    // Create an SDL window
    m_sdlWindow = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_OPENGL);

    if (!m_sdlWindow)
    {
        DEBUG_MSG("¢RErrorCheck.cpp : GLWindow() : Error below.");
        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
        throw std::runtime_error("Failed to create SDL window.");
    }

    // Create an OpenGL context
    m_glContext = SDL_GL_CreateContext(m_sdlWindow);
    if (!m_glContext)
    {
        DEBUG_MSG("¢RErrorCheck.cpp : GLWindow() : Error below.");
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_sdlWindow);
        throw std::runtime_error("Failed to create OpenGL context.");
    }

    SDL_GL_MakeCurrent(m_sdlWindow, m_glContext);

    DEBUG_MSG("GLWindow.cpp : GLWindow() : gladLoadGL.");
    if (!gladLoadGL())
    {
        DEBUG_MSG("¢RGLWindow.cpp : GLWindow() : Error: GLAD failed to initialize");
        throw std::runtime_error("Failed to initialize GLAD.");
    }

    DEBUG_MSG("¢BGLWindow.cpp : GLWindow() : GL version: ");
    cout << GLVersion.major << "." << GLVersion.minor << endl;
}


GLWindow::~GLWindow()
{
    if (m_glContext != nullptr)
    {
        SDL_GL_DeleteContext(m_glContext);
    }
    if (m_sdlWindow != nullptr) 
    {
        SDL_DestroyWindow(m_sdlWindow);
    }
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
void GLWindow::SDLEvent()
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
bool GLWindow::Create()
{
    DEBUG_MSG("GLWindow.cpp : Create() : Enters GLWindow() Create() function.");

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        DEBUG_MSG("GLWindow.cpp : Create() : Failed to initialize SDL: ");
        cout << std::string(SDL_GetError()) << endl;
        return false;
    }

    // Create an SDL window
    std::wstring wideTitle = m_WindowTitle;
    int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wideTitle.c_str(), -1, nullptr, 0, nullptr, nullptr);
    std::string titleStr(bufferSize, 0);
    WideCharToMultiByte(CP_UTF8, 0, wideTitle.c_str(), -1, titleStr.data(), bufferSize, nullptr, nullptr);
    m_sdlWindow = SDL_CreateWindow(titleStr.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        m_CurrentWidth,
        m_CurrentHeight,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (!m_sdlWindow)
    {
        DEBUG_MSG("GLWindow.cpp : Create() : Failed to create SDL window: ");
        cout << std::string(SDL_GetError());
        return false;
    }

    // Create an OpenGL context for the window
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    m_glContext = SDL_GL_CreateContext(m_sdlWindow);
    if (!m_glContext)
    {
        DEBUG_MSG("GLWindow.cpp : Create() : Failed to create OpenGL context: ");
        cout << std::string(SDL_GetError());
        return false;
    }

    // Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        DEBUG_MSG("GLWindow.cpp : Create() : Failed to initialize GLAD");
        return false;
    }

    // Enable VSync
    SDL_GL_SetSwapInterval(1);

    // Set clear color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Set viewport
    glViewport(0, 0, m_CurrentWidth, m_CurrentHeight);

    return true;
}


void GLWindow::Close()
{
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_sdlWindow);
    m_sdlWindow = nullptr;
    m_glContext = nullptr;
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

SDL_Window* GLWindow::GetWindowHandle() const
{
    return m_sdlWindow;
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



SDL_Window* GLWindow::GetSDLWindow() const
{
    return m_sdlWindow;
}

void GLWindow::CallPrivateClean()
{
    DEBUG_MSG("GLWindow.cpp : CallPrivateClean() : Enters CallPrivateClean().");

    this->PrivateClean();
}

void GLWindow::PrivateClean()
{
    DEBUG_MSG("GLWindow.cpp : PrivateClean() : Enters PrivateClean().");

    if (m_glContext)
    {
        SDL_GL_DeleteContext(m_glContext);
        m_glContext = nullptr;
    }

    if (m_sdlWindow)
    {
        SDL_DestroyWindow(m_sdlWindow);
        m_sdlWindow = nullptr;
    }
}