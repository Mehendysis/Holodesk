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
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");

    if (!ImGui::DockBuilderGetNode(dockspace_id))
    {
    DEBUG_MSG("UI.cpp : MainInterface() : Enters MainInterface().");
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");

    // Dockspace layout creation should only happen once
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoDockingInCentralNode;

    // Render dockspace
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), dockspace_flags);

    // Create dockable windows
    ImGui::DockBuilderRemoveNode(dockspace_id);
    ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
    ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetIO().DisplaySize);

    ImGui::DockBuilderDockWindow("Scene Tree", ImGui::GetID("Scene Tree"));
    ImGui::DockBuilderDockWindow("Project Explorer", ImGui::GetID("Project Explorer"));
    ImGui::DockBuilderDockWindow("Viewport", ImGui::GetID("Viewport"));
    ImGui::DockBuilderDockWindow("Folder Content", ImGui::GetID("Folder Content"));
    ImGui::DockBuilderDockWindow("Inspector", ImGui::GetID("Inspector"));

    ImGui::DockBuilderFinish(dockspace_id);
    }

    // Dockable windows creation should happen in each frame
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 window_size = io.DisplaySize;

    DEBUG_MSG("UI.cpp : MainInterface() : Create Scene Tree window.");
    ImGui::SetNextWindowPos(ImVec2(0, 20));
    ImGui::SetNextWindowSize(ImVec2(window_size.x * 0.2f, (window_size.y - 20) * 0.5f));
    ImGui::Begin("Scene Tree");
    // TODO: add Scene Tree content
    ImGui::End();

    DEBUG_MSG("UI.cpp : MainInterface() : Create Project Explorer window.");
    ImGui::SetNextWindowPos(ImVec2(0, 20 + (window_size.y - 20) * 0.5f));
    ImGui::SetNextWindowSize(ImVec2(window_size.x * 0.2f, (window_size.y - 20) * 0.5f));
    ImGui::Begin("Project Explorer");
    // TODO: add project explorer content
    ImGui::End();

    DEBUG_MSG("UI.cpp : MainInterface() : Create 3D Viewport window.");
    ImGui::SetNextWindowPos(ImVec2(window_size.x * 0.2f, 20));
    ImGui::SetNextWindowSize(ImVec2(window_size.x * 0.6f, (window_size.y - 20) * 0.5f));
    ImGui::Begin("Viewport");
    // TODO: add 3D viewport content
    ImGui::End();

    DEBUG_MSG("UI.cpp : MainInterface() : Create Folder Content window.");
    ImGui::SetNextWindowPos(ImVec2(window_size.x * 0.2f, 20 + (window_size.y - 20) * 0.5f));
    ImGui::SetNextWindowSize(ImVec2(window_size.x * 0.6f, (window_size.y - 20) * 0.5f));
    ImGui::Begin("Folder Content");
    // TODO: add folder content content
    ImGui::End();

    DEBUG_MSG("UI.cpp : MainInterface() : Create Inspector window.");
    ImGui::SetNextWindowPos(ImVec2(window_size.x * 0.8f, 20));
    ImGui::SetNextWindowSize(ImVec2(window_size.x * 0.2f, window_size.y - 20));
    ImGui::Begin("Inspector");
    // TODO: add inspector content
    ImGui::End();
    
}


void UI::RenderUIElements()
{
    DEBUG_MSG("UI.cpp : RenderUIElements() : Enters RenderUIElements().");

    static ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");

    MainTopMenu();
    MainInterface();

    // Show ImGui demo window
    //static bool show_demo_window = true;
    //ImGui::ShowDemoWindow(&show_demo_window);
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