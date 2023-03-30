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

UI::~UI()
{
}

void UI::MainTopMenu()
{
    //DEBUG_MSG("UI.cpp : MainMenu() : Enters MainMenu().");

    // Render a top bar menu
    //DEBUG_MSG("UI.cpp : MainMenu() : Render a top bar menu.");
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
    //DEBUG_MSG("UI.cpp : MutualResizeWindow() : Enters MutualResizeWindow().");
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
        //DEBUG_MSG("UI.cpp : MainInterface() : Enters MainInterface().");

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

    ImGui::SetNextWindowPos(ImVec2(0, 20));
    ImGui::SetNextWindowSize(ImVec2(window_size.x * 0.2f, (window_size.y - 20) * 0.7f)); // increased height percentage
    ImGui::Begin("Scene Tree");
    if (m_sceneTreeID == 0)
    {
        m_sceneTreeID = ImGui::GetID("Scene Tree");
    }
    // TODO: add Scene Tree content
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(0, 20 + (window_size.y - 20) * 0.7f));
    ImGui::SetNextWindowSize(ImVec2(window_size.x * 0.2f, (window_size.y - 20) * 0.3f)); // decreased height percentage
    ImGui::Begin("Project Explorer");
    if (m_projectExplorerID == 0)
    {
        m_projectExplorerID = ImGui::GetID("Project Explorer");
    }
    // TODO: add project explorer content
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(window_size.x * 0.2f, 20));
    ImGui::SetNextWindowSize(ImVec2(window_size.x * 0.6f, (window_size.y - 20) * 0.7f)); // increased height percentage
    ImGui::Begin("Viewport");
    if (m_viewportID == 0)
    {
        m_viewportID = ImGui::GetID("Viewport");
    }
    // TODO: add 3D viewport content
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(window_size.x * 0.2f, 20 + (window_size.y - 20) * 0.7f));
    ImGui::SetNextWindowSize(ImVec2(window_size.x * 0.6f, (window_size.y - 20) * 0.3f)); // decreased height percentage
    ImGui::Begin("Folder Content");
    if (m_folderContentID == 0)
    {
        m_folderContentID = ImGui::GetID("Folder Content");
    }
    // TODO: add folder content content
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(window_size.x * 0.8f, 20));
    ImGui::SetNextWindowSize(ImVec2(window_size.x * 0.2f, window_size.y - 20));
    ImGui::Begin("Inspector");
    if (m_inspectorID == 0)
    {
        m_inspectorID = ImGui::GetID("Inspector");
    }
    // TODO: add inspector content
    ImGui::End();
}

void UI::CursorOverMutualWindows()
{
    //DEBUG_MSG("UI.cpp : CursorOverMutualWindows() : Enters CursorOverMutualWindows().");

    static ImGuiID last_hovered_window_ID = 0;
    static ImGuiID hovered_window_ID = 0;

    // Get the ID of the hovered window
    ImGuiWindow* hovered_window = ImGui::GetCurrentContext()->HoveredWindow;
    //DEBUG_MSG("UI.cpp : CursorOverMutualWindows() : Hovered Window :");
    
    if (hovered_window)
    {
        hovered_window_ID = ImGui::GetID(hovered_window->Name);
    }
    else
    {
        hovered_window_ID = 0;
    }

    // Check if the mouse is hovering between windows
    bool anyHovered = (hovered_window_ID & (m_sceneTreeID | m_projectExplorerID | m_viewportID | m_folderContentID | m_inspectorID));
    //cout << "anyHovered = " << anyHovered << "\n";
    bool anyLastHovered = (last_hovered_window_ID & (m_sceneTreeID | m_projectExplorerID | m_viewportID | m_folderContentID | m_inspectorID));
    cout << "anyLastHovered = " << anyLastHovered << "\n";
    if (anyHovered && anyLastHovered)
    {
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
}

void UI::RenderUIElements()
{
    //DEBUG_MSG("UI.cpp : RenderUIElements() : Enters RenderUIElements().");

    MainTopMenu();
    MainWindowsInterface();
    //CursorOverMutualWindows();

    // Show ImGui demo window
    //static bool show_demo_window = true;
    //ImGui::ShowDemoWindow(&show_demo_window);
}

void UI::Render()
{
    //DEBUG_MSG("UI.cpp : Render() : Enters Render().");

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



void UI::Initialize()
{
    //DEBUG_MSG("UI.cpp : Initialize() : Enters Initialize().");

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