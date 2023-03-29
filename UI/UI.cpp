// UI.cpp
#include "UI.h"
#include <Window.h>
#include <Renderer.h>
#include <Debug.h>

#define IMGUI_CONFIG_FLAGS_HAS_DOCKING
#include <imgui_internal.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

void UI::MainTopMenu()
{
    DEBUG_MSG("UI.cpp : MainMenu() : Enters MainMenu().");

    // Render a top bar menu
    DEBUG_MSG("UI.cpp : MainMenu() : Render a top bar menu.");
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::MenuItem("New", "Ctrl+N");
            ImGui::MenuItem("Open", "Ctrl+O");
            ImGui::MenuItem("Save", "Ctrl+S");
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit"))
        {
            ImGui::MenuItem("Cut", "Ctrl+X");
            ImGui::MenuItem("Copy", "Ctrl+C");
            ImGui::MenuItem("Paste", "Ctrl+V");
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

void UI::MainInterface()
{
    DEBUG_MSG("UI.cpp : MainInterface() : Enters MainInterface().");

    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoDockingInCentralNode;
    //ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoDockingInCentralNode;

    // Render dockspace
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), dockspace_flags);

    // Define variables for dock space
    DEBUG_MSG("UI.cpp : MainInterface() : Define variables for dock space.");
    static bool dockspace_open = true;

    ImGui::SetNextWindowPos(ImVec2(0, 20));
    ImGui::Begin("MyDockSpace", &dockspace_open, dockspace_flags);
    ImGui::End();

    // Create dockable windows
    DEBUG_MSG("UI.cpp : MainInterface() : Create dockable windows.");

    DEBUG_MSG("UI.cpp : MainInterface() : Create Hierarchy window.");
    ImGui::SetNextWindowDockID(ImGui::GetID("Hierarchy"));
    ImGui::Begin("Hierarchy");
    // TODO: add hierarchy content
    ImGui::End();

    DEBUG_MSG("UI.cpp : MainInterface() : Create Project Explorer window.");
    ImGui::SetNextWindowDockID(ImGui::GetID("Project Explorer"));
    ImGui::Begin("Project Explorer");
    // TODO: add project explorer content
    ImGui::End();

    DEBUG_MSG("UI.cpp : MainInterface() : Create 3D Viewport window.");
    ImGui::SetNextWindowDockID(ImGui::GetID("3D Viewport"));
    ImGui::Begin("3D Viewport");
    // TODO: add 3D viewport content
    ImGui::End();

    DEBUG_MSG("UI.cpp : MainInterface() : Create Folder Content window.");
    ImGui::SetNextWindowDockID(ImGui::GetID("Folder Content"));
    ImGui::Begin("Folder Content");
    // TODO: add folder content content
    ImGui::End();
}


void UI::RenderUIElements()
{
    DEBUG_MSG("UI.cpp : RenderUIElements() : Enters RenderUIElements().");

    static ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");

    MainTopMenu();
    MainInterface();
}


void UI::Render()
{
    DEBUG_MSG("UI.cpp : Render() : Enters Render().");

    // Initialize platform backend if it hasn't already been initialized
    if (!m_backendInitialized) {
        ImGui_ImplSDL2_NewFrame(static_cast<SDL_Window*>(m_window->GetNativeWindowHandle()));
        ImGui_ImplOpenGL3_NewFrame();
        m_backendInitialized = true;
    }

    ImGui::NewFrame();

    // Call RenderUI() to render the UI elements
    RenderUIElements();

    ImGui::Render();

    // Clear the screen with the background color set by ImGui
    int display_w, display_h;
    SDL_GL_GetDrawableSize(static_cast<SDL_Window*>(m_window->GetNativeWindowHandle()), &display_w, &display_h);
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(static_cast<float>(display_w), static_cast<float>(display_h)));
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

UI::UI(Window* window, Renderer* renderer) : m_window(window), m_renderer(renderer)
{
}

UI::~UI()
{
}

void UI::Initialize()
{
    DEBUG_MSG("UI.cpp : Initialize() : Enters Initialize().");
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(static_cast<SDL_Window*>(m_window->GetNativeWindowHandle()), m_renderer->GetContext());
    ImGui_ImplOpenGL3_Init("#version 460");

    // Enable docking
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Set up SDL2 input
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;  // Enable mouse position reporting
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;     // Enable gamepad navigation
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;    // Enable mouse cursors

    // Set up display size
    int windowWidth, windowHeight;
    m_window->GetWindowSize(&windowWidth, &windowHeight);
    io.DisplaySize = ImVec2((float)windowWidth, (float)windowHeight);
}
