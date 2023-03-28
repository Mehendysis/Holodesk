// UI.cpp

#include "UI.h"
#include <Window.h>
#include <Renderer.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

//IMGUI_CHECKVERSION();
//ImGui::CreateContext();
//ImGuiIO& io = ImGui::GetIO(); (void)io;
//ImGui::StyleColorsDark();
//ImGui_ImplGlfw_InitForOpenGL(window, true);
//ImGui_ImplOpenGL3_Init("#version 330");

void UI::SetDisplay(Window* window)
{
    ImGuiIO& io = ImGui::GetIO();
    int windowWidth, windowHeight;
    m_window->GetWindowSize(&windowWidth, &windowHeight);
    io.DisplaySize = ImVec2((float)windowWidth, (float)windowHeight);
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
    ImGui_ImplSDL2_InitForOpenGL(static_cast<SDL_Window*>(m_window->GetNativeWindowHandle()), m_renderer->GetContext());
    ImGui_ImplOpenGL3_Init("#version 330");

    // Set up ImGui style and settings here if desired
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

    // Add your ImGui widgets here

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
