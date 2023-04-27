// GLUI.cpp

#ifndef GLUI_CPP
#define GLUI_CPP

#include "Debug.h"
#include "GLUI.h"
#include "UIElements.h"

#define IMGUI_CONFIG_FLAGS_HAS_DOCKING

#include "GLMemoryWrapper.h"
#include <SDL.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

using namespace std;

//GLUI::GLUI(GLWindow* glWindow, SDL_GLContext* glContext) :
//    m_glWindow(glWindow),
//    m_glContext(glContext)
//{
//    Initialize();
//}

GLUI::GLUI(GLWindow* glWindow, SDL_GLContext* glContext) :
    m_glWindow(glWindow),
    m_glContext(glContext)
{
    Initialize();
}

GLUI::~GLUI()
{
}

//GLUI::GLUI(const std::shared_ptr<const SDL_Window>& sdlWindow, const GLWindow& glWindow, GLRenderer& glRenderer, GLCamera& glCamera, SDL_GLContext& glContext) :
//    m_sdlWindow(sdlWindow),
//    m_glWindow(glWindow),
//    m_glRenderer(glRenderer),
//    m_glCamera(glCamera),
//    glContext(glContext)
//{
//
//}

//GLUI::GLUI(const std::shared_ptr<SDL_Window>& sdlWindow, GLWindow& glWindow, GLRenderer* glRenderer, GLCamera* glCamera, SDL_GLContext* glContext) :
//    m_sdlWindow(sdlWindow),
//    m_glWindow(glWindow),
//    m_glRenderer(glRenderer), 
//    m_glCamera(glCamera),
//    m_glContext(glContext)
//{
//    // Initialize ImGui
//    IMGUI_CHECKVERSION();
//    ImGui::CreateContext();
//    ImGuiIO& io = ImGui::GetIO(); (void)io;
//
//    //ImGui_ImplSDL2_InitForSDLRenderer(sdlWindow.get(), renderer.get()); already in main
//    ImGui_ImplOpenGL3_Init("#version 430");
//
//    // Setup style
//    ImGui::StyleColorsDark();
//}

//GLUI::~GLUI()
//{
//    DEBUG_MSG("GLUI.cpp : ~UI() : Enters ~UI().");
//    ImGui_ImplOpenGL3_Shutdown();
//    ImGui_ImplSDL2_Shutdown();
//    ImGui::DestroyContext();
//    SDL_DestroyWindow(m_sdlWindow.get());
//}


void GLUI::CleanUp()
{
    this->~GLUI();
}

void GLUI::SetRenderer(GLRenderer* glRenderer)
{
    m_glRenderer = glRenderer;
}


void GLUI::Render()
{
    DEBUG_MSG("¢BGLUI.cpp : Render() : Enters Render().");

    // Call ImGui::NewFrame() to start a new frame
    DEBUG_MSG("GLUI.cpp : Render() : ImGui::NewFrame().");
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(m_glWindow->GetSDLWindow());
    ImGui::NewFrame();

    // Call RenderUI() to render the UI elements
    DEBUG_MSG("GLUI.cpp : Render() : Call RenderUI() to render the UI elements.");
    UIElements renderUIElements;
    renderUIElements.RenderUIElements();

    //// Clear the framebuffer
    //ImVec4 clear_color = ImGui::GetStyleColorVec4(ImGuiCol_WindowBg);
    //glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    ////glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    ////glClear(GL_COLOR_BUFFER_BIT);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    // Render the UI
    DEBUG_MSG("GLUI.cpp : Render() : Render the UI.");
    ImGui::Render();

    // Render the UI to the framebuffer
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Set the viewport
    //glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);

    DEBUG_MSG("GLUI.cpp : Render() : Render() completed.");
}

//void GLUI::Render()
//{
    //DEBUG_MSG("GLUI.cpp : Render() : Enters Render().");

    //// Initialize platform backend if it hasn't already been initialized
    //DEBUG_MSG("GLUI.cpp : Render() : Initialize platform backend if it hasn't already been initialized.");
    //if (!IsBackendInitialized())
    //{
    //    // Initialize platform backend
    //    DEBUG_MSG("GLUI.cpp : Render() : Initialize platform backend.");
    //    if (m_sdlWindow != nullptr)
    //    {
    //        DEBUG_MSG("GLUI.cpp : Render() : SDL Window initialized properly.");
    //        DEBUG_MSG("GLUI.cpp : Render() : ImGui_ImplSDL2_NewFrame().");
    //        ImGui_ImplSDL2_NewFrame(static_cast<SDL_Window*>((static_cast<SDL_Window*>(m_glWindow.GetNativeWindowHandle()))));
    //        DEBUG_MSG("GLUI.cpp : Render() : ImGui_ImplOpenGL3_NewFrame().");
    //        ImGui_ImplOpenGL3_NewFrame();
    //        DEBUG_MSG("GLUI.cpp : Render() : SetBackendInitialized().");
    //        SetBackendInitialized(true);
    //    }
    //    else
    //    {
    //        DEBUG_MSG("GLUI.cpp : Render() : SDL Window did not initialize properly.");
    //    }
    //}

    //// Call ImGui::NewFrame() to start a new frame
    //DEBUG_MSG("GLUI.cpp : Render() : ImGui::NewFrame().");
    //ImGui::NewFrame();

    //// Call RenderUI() to render the UI elements
    //DEBUG_MSG("GLUI.cpp : Render() : Call RenderUI() to render the UI elements.");
    //RenderUIElements();

    //// Render the UI
    //DEBUG_MSG("GLUI.cpp : Render() : Render the UI.");
    //ImGui::Render();

    //if (m_sdlWindow != nullptr)
    //{
    //    DEBUG_MSG("¢YGLUI.cpp : Render() : m_sdlWindow is not null.");
    //    // Clear the screen with the background color set by ImGui
    //    DEBUG_MSG("GLUI.cpp : Render() : Clear the screen with the background color.");
    //    int display_w, display_h;
    //    std::cout << "Current window size: ";
    //    //SDL_GL_GetDrawableSize(static_cast<SDL_Window*>(m_glWindow->GetNativeWindowHandle()), &display_w, &display_h);
    //    SDL_GL_GetDrawableSize(static_cast<SDL_Window*>(m_glWindow.GetNativeWindowHandle()), &display_w, &display_h);
    //    std::cout << display_w << " x " << display_h << std::endl;
    //    ImGui::SetNextWindowPos(ImVec2(0, 0));
    //    ImGui::SetNextWindowSize(ImVec2(static_cast<float>(display_w), static_cast<float>(display_h)));
    //    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    //}
    //else
    //{
    //    DEBUG_MSG("¢RGLUI.cpp : Render() : m_sdlWindow is null.");
    //}

    //// Update main viewport size to match the window size
    //int windowWidth, windowHeight;
    //SDL_GetWindowSize(m_glWindow.GetNativeWindowHandle(), &windowWidth, &windowHeight);


    //ImGui::GetMainViewport()->Size = ImVec2(static_cast<float>(windowWidth), static_cast<float>(windowHeight));

    //DEBUG_MSG("GLUI.cpp : Render() : Render() completed.");
//}


void GLUI::Initialize()
{
    DEBUG_MSG("¢BGLUI.cpp : Initialize() : Enters GLUI::Initialize().");

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Check if the SDL2 platform backend is already initialized
    if (io.BackendPlatformUserData == nullptr)
    {
        // If not initialized, set m_backendInitialized to true
        //m_backendInitialized = true;

        // Initialize SDL2 platform backend
        ImGui_ImplSDL2_InitForOpenGL(m_glWindow->GetSDLWindow(), m_glContext);
        //ImGui_ImplSDL2_InitForOpenGL(static_cast<SDL_Window*>(m_glWindow.GetNativeWindowHandle()), m_glRenderer->GetContext());
    }

    // Initialize ImGui OpenGL3 renderer backend
    ImGui_ImplOpenGL3_Init("#version 430");

    ImGui::StyleColorsDark();
    io.Fonts->AddFontDefault();
    //ImGui_ImplSDL2_InitForOpenGL(static_cast<SDL_Window*>(m_sdlWindow->GetNativeWindowHandle()), m_glRenderer->GetContext());
    // Check if the SDL2 platform backend is already initialized

    // Enable docking
    DEBUG_MSG("GLUI.cpp : Initialize() : Enable docking.");
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Set up SDL2 input
    DEBUG_MSG("GLUI.cpp : Initialize() : Set up SDL2 input.");
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;  // Enable mouse position reporting
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;     // Enable gamepad navigation
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;    // Enable mouse cursors

    // Set up display size
    DEBUG_MSG("GLUI.cpp : Initialize() : Set up display size.");
    io.DisplaySize = ImVec2(static_cast<float>(m_glWindow->GetCurrentWidth()), static_cast<float>(m_glWindow->GetCurrentHeight()));

    DEBUG_MSG("¢CGLUI.cpp : Initialize() : GLUI::Initialize() completed.");
}

bool GLUI::IsBackendInitialized() const
{
    //DEBUG_MSG("GLUI.cpp : IsBackendInitialized() : Enters IsBackendInitialized().");
    //ImGuiIO& io = ImGui::GetIO();

    //if (io.BackendPlatformUserData != nullptr)
    //{
    //    // The SDL2 platform backend is already initialized
    //    //DEBUG_MSG("GLUI.cpp : IsBackendInitialized() : The SDL2 platform backend is already initialized.");
    //    m_backendInitialized = true;
    //}
    //else
    //{
    //    // The SDL2 platform backend is not yet initialized
    //    //DEBUG_MSG("¢RGLUI.cpp : IsBackendInitialized() : The SDL2 platform backend is not yet initialized.");
    //    m_backendInitialized = false;
    //}
    //DEBUG_MSG("¢CGLUI.cpp : IsBackendInitialized() : IsBackendInitialized() completed.");
    //return m_backendInitialized;
    return false;
}

void GLUI::SetBackendInitialized(bool initialized)
{
    /*m_backendInitialized = initialized;*/
}

void GLUI::CallPrivateClean()
{
    PrivateClean();
}

void GLUI::PrivateClean()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

#endif // GLUI_CPP
