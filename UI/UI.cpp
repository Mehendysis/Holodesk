// UI.cpp
#include "UI.h"
#include <Window.h>
#include <Renderer.h>
#include <Debug.h>
#include <ImGuiWrapper.h>

#define IMGUI_CONFIG_FLAGS_HAS_DOCKING
#include <imgui_internal.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
using namespace ImGuiWrapper;

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

void UI::MutualResizeWindow()
{
    DEBUG_MSG("UI.cpp : MutualResizeWindow() : Enters MutualResizeWindow().");
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 window_size = io.DisplaySize;

    float window_width = window_size.x / 2;

    // Create left child window
    ImGui::BeginChild("Left Pane", ImVec2(window_width, window_size.y), true);
    ImGui::Text("Left Pane");
    ImGui::EndChild();

    ImGui::SameLine();

    // Create right child window
    ImGui::BeginChild("Right Pane", ImVec2(window_width, window_size.y), true);
    ImGui::Text("Right Pane");
    ImGui::EndChild();

    // Handle resizing
    static bool is_resizing = false;
    static float resize_offset = 0.0f;
    if (ImGui::GetIO().MouseDown[0] && ImGui::IsWindowHovered() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
    {
        is_resizing = true;
    }
    if (is_resizing)
    {
        if (ImGui::GetIO().MouseReleased[0])
        {
            is_resizing = false;
        }
        else
        {
            resize_offset += ImGui::GetIO().MouseDelta.x;
            window_width += resize_offset;
            resize_offset = 0;
        }
    }

    // Set child window sizes
    ImGui::SetCursorPosX(0);
    ImGui::SetWindowSize("Left Pane", ImVec2(window_width, window_size.y));
    ImGui::SetCursorPosX(window_width);
    ImGui::SetWindowSize("Right Pane", ImVec2(window_size.x - window_width, window_size.y));
}

void UI::MainWindowsInterface()
{
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");

    if (!ImGui::DockBuilderGetNode(dockspace_id))
    {
        DEBUG_MSG("UI.cpp : MainInterface() : Enters MainInterface().");

        // Dockspace layout creation should only happen once
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoDockingInCentralNode;

        // Render dockspace
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), dockspace_flags);

        MutualResizeWindow();

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
    DEBUG_MSG("UI.cpp : MainInterface() : Assign first ID.");
    ImGuiWrapper::SetWindowID(SCENE_TREE); // assign ID to the window
    // TODO: add Scene Tree content
    ImGui::PopID();
    ImGui::End();

    DEBUG_MSG("UI.cpp : MainInterface() : Create Project Explorer window.");
    ImGui::SetNextWindowPos(ImVec2(0, 20 + (window_size.y - 20) * 0.5f));
    ImGui::SetNextWindowSize(ImVec2(window_size.x * 0.2f, (window_size.y - 20) * 0.5f));
    ImGui::Begin("Project Explorer");
    ImGuiWrapper::SetWindowID(PROJECT_EXPLORER); // assign ID to the window
    // TODO: add project explorer content
    ImGui::PopID();
    ImGui::End();

    DEBUG_MSG("UI.cpp : MainInterface() : Create 3D Viewport window.");
    ImGui::SetNextWindowPos(ImVec2(window_size.x * 0.2f, 20));
    ImGui::SetNextWindowSize(ImVec2(window_size.x * 0.6f, (window_size.y - 20) * 0.5f));
    ImGui::Begin("Viewport");
    ImGuiWrapper::SetWindowID(3); // assign ID to the window
    // TODO: add 3D viewport content
    ImGui::PopID();
    ImGui::End();

    DEBUG_MSG("UI.cpp : MainInterface() : Create Folder Content window.");
    ImGui::SetNextWindowPos(ImVec2(window_size.x * 0.2f, 20 + (window_size.y - 20) * 0.5f));
    ImGui::SetNextWindowSize(ImVec2(window_size.x * 0.6f, (window_size.y - 20) * 0.5f));
    ImGui::Begin("Folder Content");
    ImGuiWrapper::SetWindowID(4); // assign ID to the window
    // TODO: add folder content content
    ImGui::PopID();
    ImGui::End();

    DEBUG_MSG("UI.cpp : MainInterface() : Create Inspector window.");
    ImGui::SetNextWindowPos(ImVec2(window_size.x * 0.8f, 20));
    ImGui::SetNextWindowSize(ImVec2(window_size.x * 0.2f, window_size.y - 20));
    ImGui::Begin("Inspector");
    ImGuiWrapper::SetWindowID(5); // assign ID to the window
    // TODO: add inspector content
    ImGui::PopID();
    ImGui::End();
}

void UI::CursorOverMutualWindows()
{
    DEBUG_MSG("UI.cpp : CursorOverMutualWindows() : Enters CursorOverMutualWindows().");

    // Set cursor to arrow when hovering between windows
    static uint8_t last_hovered_window_ID;
    static uint8_t hovered_window_ID;

    // Get the ID of the hovered window using the wrapper
    hovered_window_ID = ImGuiWrapper::GetCurrentID();

    // Check if the mouse is hovering between windows
    if (ImGui::IsWindowHovered(ImGuiHoveredFlags_None) && !ImGui::IsAnyItemActive())
    {
        // Get the name of the current window being hovered
        hovered_window_ID = ImGuiWrapper::GetCurrentID();

        // Set cursor to resize cursor if hovering between windows
        ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);

        // If the mouse is moving from one window to another, toggle the cursor to the arrow
        if (last_hovered_window_ID != 0 && last_hovered_window_ID != hovered_window_ID)
        {
            ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
        }

        // Keep track of the last window hovered
        last_hovered_window_ID = hovered_window_ID;
    }
    else
    {
        // Reset the last hovered window if the mouse is not hovering over any windows
        ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
        last_hovered_window_ID = 0;
    }

    //const bool hoveredIsSceneTree = (hovered_window_ID == SCENE_TREE);
    //const bool lastHoveredIsSceneTree = (last_hovered_window_ID == SCENE_TREE);
    //const bool hoveredIsProjectExplorer = (hovered_window_ID == PROJECT_EXPLORER);
    //const bool lastHoveredIsProjectExplorer = (last_hovered_window_ID == PROJECT_EXPLORER);
    //const bool transSceneTreeProjectExplorer = (hoveredIsSceneTree && lastHoveredIsProjectExplorer) || (hoveredIsProjectExplorer && lastHoveredIsSceneTree);

    //// Condition loop for two windows intersections
    //if (transSceneTreeProjectExplorer)
    //{
    //    ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
    //}

    const uint8_t TOUCHING_WINDOWS = SCENE_TREE | PROJECT_EXPLORER | VIEWPORT | FOLDER_CONTENT | INSPECTOR;
    if ((hovered_window_ID & TOUCHING_WINDOWS) && (last_hovered_window_ID & TOUCHING_WINDOWS))
    {
        DEBUG_MSG("UI.cpp : CursorOverMutualWindows() : Windows are touching. #########################################################################");
        ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
    }

    //// Condition loop for three windows intersections
    //if ((hovered_window_ID == SCENE_TREE && last_hovered_window_ID == PROJECT_EXPLORER && ImGui::IsWindowHovered(ImGuiWrapper::GetCurrentID() == VIEWPORT)) ||
    //    (hovered_window_ID == PROJECT_EXPLORER && last_hovered_window_ID == ImGui::IsWindowHovered(ImGuiWrapper::GetCurrentID() == VIEWPORT)) ||
    //    (hovered_window_ID == VIEWPORT && last_hovered_window_ID == SCENE_TREE && ImGui::IsWindowHovered(ImGuiWrapper::GetCurrentID() == PROJECT_EXPLORER)))
    //{
    //    ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
    //}

    //// Condition loop for four windows intersections
    //if ((hovered_window_ID == SCENE_TREE && last_hovered_window_ID == PROJECT_EXPLORER && ImGui::IsWindowHovered(ImGuiWrapper::GetCurrentID() == FOLDER_CONTENT) && ImGui::IsWindowHovered(ImGuiWrapper::GetCurrentID() == INSPECTOR)) || 
    //    (hovered_window_ID == PROJECT_EXPLORER && last_hovered_window_ID == SCENE_TREE && ImGui::IsWindowHovered(ImGuiWrapper::GetCurrentID() == FOLDER_CONTENT) && ImGui::IsWindowHovered(ImGuiWrapper::GetCurrentID() == INSPECTOR)) ||
    //    (hovered_window_ID == FOLDER_CONTENT && last_hovered_window_ID == SCENE_TREE && ImGui::IsWindowHovered(ImGuiWrapper::GetCurrentID() == PROJECT_EXPLORER) && ImGui::IsWindowHovered(ImGuiWrapper::GetCurrentID() == INSPECTOR)) ||
    //    (hovered_window_ID == INSPECTOR && last_hovered_window_ID == SCENE_TREE && ImGui::IsWindowHovered(ImGuiWrapper::GetCurrentID() == PROJECT_EXPLORER) && ImGui::IsWindowHovered(ImGuiWrapper::GetCurrentID() == FOLDER_CONTENT)))
    //{
    //    ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
    //}
}

void UI::RenderUIElements()
{
    DEBUG_MSG("UI.cpp : RenderUIElements() : Enters RenderUIElements().");

    MainTopMenu();
    CursorOverMutualWindows();
    MainWindowsInterface();

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