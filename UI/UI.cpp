// UI.cpp
#include "UI.h"
#include <Window.h>
#include <Renderer.h>
#include <imgui_internal.h>
//#include <GL/gl.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

//IMGUI_CHECKVERSION();
//ImGui::CreateContext();
//ImGuiIO& io = ImGui::GetIO(); (void)io;
//ImGui::StyleColorsDark();
//ImGui_ImplGlfw_InitForOpenGL(window, true);
//ImGui_ImplOpenGL3_Init("#version 330");

void UI::RenderUI()
{
    // Start a new ImGui frame
    ImGui::Begin("My UI");

    // Render a top bar menu
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

    // Add UI elements here
    ImGui::Text("Hello, world!");

    // End the ImGui frame
    ImGui::End();
}

void UI::Render()
{
    // Initialize platform backend if it hasn't already been initialized
    if (!m_backendInitialized) {
        ImGui_ImplSDL2_NewFrame(static_cast<SDL_Window*>(m_window->GetNativeWindowHandle()));
        ImGui_ImplOpenGL3_NewFrame();
        m_backendInitialized = true;
    }

    ImGui::NewFrame();

    // Call RenderUI() to render the UI elements
    RenderUI();

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
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // Set up ImGui style
    ImGui::StyleColorsDark();

    // Set up SDL2 input
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;  // Enable mouse position reporting
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;     // Enable gamepad navigation
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;    // Enable mouse cursors

    // Set up display size
    int windowWidth, windowHeight;
    m_window->GetWindowSize(&windowWidth, &windowHeight);
    io.DisplaySize = ImVec2((float)windowWidth, (float)windowHeight);

    // Initialize backends
    ImGui_ImplSDL2_InitForOpenGL(static_cast<SDL_Window*>(m_window->GetNativeWindowHandle()), m_renderer->GetContext());
    ImGui_ImplOpenGL3_Init("#version 330");

    // Set up ImGui style and settings here if desired
}
