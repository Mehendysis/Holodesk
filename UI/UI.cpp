// UI.cpp

#ifndef UI_CPP
#define UI_CPP
#include "UI.h"
#include "Debug.h"
#include "GLRenderer.h"
#include "GLWindow.h"

#include <memory>

#define IMGUI_CONFIG_FLAGS_HAS_DOCKING

#include <imgui_internal.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

UI::~UI()
{
    DEBUG_MSG("UI.cpp : ~UI() : Enters ~UI().");
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void UI::CleanUp() 
{
    this->~UI();
}

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
    DEBUG_MSG("UI.cpp : MutualResizeWindow() : Create left child window.");
    ImGui::BeginChild("Left Pane", ImVec2(window_width, window_size.y), true);
    ImGui::Text("Left Pane");
    ImGui::EndChild();

    ImGui::SameLine();

    // Create right child window
    DEBUG_MSG("UI.cpp : MutualResizeWindow() : Create right child window.");
    ImGui::BeginChild("Right Pane", ImVec2(window_width, window_size.y), true);
    ImGui::Text("Right Pane");
    ImGui::EndChild();

    // Handle resizing
    DEBUG_MSG("UI.cpp : MutualResizeWindow() : Handle resizing.");
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
    DEBUG_MSG("UI.cpp : MutualResizeWindow() : Set child window sizes.");
    ImGui::SetCursorPosX(0);
    ImGui::SetWindowSize("Left Pane", ImVec2(window_width, window_size.y));
    ImGui::SetCursorPosX(window_width);
    ImGui::SetWindowSize("Right Pane", ImVec2(window_size.x - window_width, window_size.y));
    
    DEBUG_MSG("UI.cpp : MutualResizeWindow() : MutualResizeWindow has ended.");
}

void UI::DockSetting()
{
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");

    if (!ImGui::DockBuilderGetNode(dockspace_id))
    {
        DEBUG_MSG("UI.cpp : MainInterface() : Enters MainInterface().");

        // Dockspace layout creation should only happen once
        DEBUG_MSG("UI.cpp : MainInterface() : Dockspace layout creation should only happen once.");
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoDockingInCentralNode;

        // Render dockspace
        DEBUG_MSG("UI.cpp : MainInterface() : Render dockspace.");
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), dockspace_flags);

        MutualResizeWindow();

        // Create dockable windows
        DEBUG_MSG("UI.cpp : MainInterface() :Create dockable windows.");
        ImGui::DockBuilderRemoveNode(dockspace_id);
        ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetIO().DisplaySize);

        ImGui::DockBuilderDockWindow("Scene Tree", ImGui::GetID("Scene Tree"));
        ImGui::DockBuilderDockWindow("Project Explorer", ImGui::GetID("Project Explorer"));
        ImGui::DockBuilderDockWindow("Viewport", ImGui::GetID("Viewport"));
        ImGui::DockBuilderDockWindow("Folder Content", ImGui::GetID("Folder Content"));
        ImGui::DockBuilderDockWindow("Inspector", ImGui::GetID("Inspector"));

        ImGui::DockBuilderFinish(dockspace_id);
        DEBUG_MSG("UI.cpp : MainInterface() : Dockable windows created.");
    }
    DEBUG_MSG("UI.cpp : MainInterface() : MainInterface completed.");
}

void UI::SceneTree(ImVec2 window_size)
{
    ImGui::SetNextWindowPos(ImVec2(0, 20));
    ImGui::SetNextWindowSize(ImVec2(window_size.x * 0.2f, (window_size.y - 20) * 0.7f)); // increased height percentage
    ImGui::Begin("Scene Tree");

    if (m_sceneTreeID == 0)
    {
        m_sceneTreeID = m_uniqueIDGenerator.GenerateUniqueID("");
    }
    //TODO: add Scene Tree content
    ImGui::End();
}

void UI::ProjectExplorer(ImVec2 window_size)
{
    ImGui::SetNextWindowPos(ImVec2(0, 20 + (window_size.y - 20) * 0.7f));
    ImGui::SetNextWindowSize(ImVec2(window_size.x * 0.2f, (window_size.y - 20) * 0.3f)); // decreased height percentage
    ImGui::Begin("Project Explorer");

    if (m_sceneTreeID == 0)
    {
        m_sceneTreeID = m_uniqueIDGenerator.GenerateUniqueID("");
    }
    // TODO: add project explorer content
    ImGui::End();
}

struct Custom3DRenderingData {
    ImVec2 canvas_pos;
    ImVec2 canvas_size;
};

void Custom3DRendering(const ImDrawList* parent_list, const ImDrawCmd* cmd)
{
    Custom3DRenderingData* data = static_cast<Custom3DRenderingData*>(cmd->UserCallbackData);

    int x = static_cast<int>(data->canvas_pos.x);
    int y = static_cast<int>(data->canvas_pos.y);
    int width = static_cast<int>(data->canvas_size.x);
    int height = static_cast<int>(data->canvas_size.y);
    glViewport(x, y, width, height);
    glEnable(GL_SCISSOR_TEST);
    glScissor(x, y, width, height);

    // Render your 3D scene here
    // ...

    // Don't forget to disable the scissor test after rendering
    glDisable(GL_SCISSOR_TEST);
}

void UI::Viewport(ImVec2 window_size)
{
    DEBUG_MSG("UI.cpp : Viewport() : Enters Viewport().");

    ImGui::SetNextWindowPos(ImVec2(window_size.x * 0.2f, 20));
    ImGui::SetNextWindowSize(ImVec2(window_size.x * 0.6f, (window_size.y - 20) * 0.7f)); // increased height percentage
    ImGui::Begin("Viewport");

    if (m_sceneTreeID == 0)
    {
        m_sceneTreeID = m_uniqueIDGenerator.GenerateUniqueID("");
    }

    ImVec2 viewportSize = ImGui::GetContentRegionAvail();

    int width = static_cast<int>(window_size.x);
    int height = static_cast<int>(window_size.y);

    if (width <= 0 || height <= 0)
    {
        // Handle invalid width and height values, e.g., by returning early from the function
        ImGui::End();
        return;
    }

    // TODO: create and bind an FBO and render buffer
    // Set up the renderer and initialize the framebuffer
    DEBUG_MSG("UI.cpp : Viewport() : Set up the renderer and initialize the framebuffer.");
    if (!m_renderer)
    {
        // Create a new renderer object
        DEBUG_MSG("UI.cpp : Viewport() : Create a new renderer object.");
        GLCamera* camera = m_camera;
        m_renderer = new GLRenderer(*m_window, static_cast<unsigned int>(window_size.x), static_cast<unsigned int>(window_size.y), *m_camera);

        // Initialize the 3D viewport
        DEBUG_MSG("UI.cpp : Viewport() : Initialize the 3D viewport.");
        m_renderer->InitializeGL3DViewport(static_cast<int>(window_size.x), static_cast<int>(window_size.y));

        //// Initialize the framebuffer
        //DEBUG_MSG("UI.cpp : Viewport() : Initialize the framebuffer.");
        //m_renderer->InitializeFBO(static_cast<int>(window_size.x), static_cast<int>(window_size.y));
    }

    // Set up the renderer for rendering the 3D viewport
    DEBUG_MSG("UI.cpp : Viewport() : Set up the renderer for rendering the 3D viewport.");
    m_renderer->GL3DViewport();

    ImVec2 canvas_pos = ImGui::GetCursorScreenPos(); // Get the position of the ImGui window
    ImVec2 canvas_size = ImGui::GetContentRegionAvail(); // Get the available size of the ImGui window

    Custom3DRenderingData data;
    data.canvas_pos = canvas_pos;
    data.canvas_size = canvas_size;

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    draw_list->AddCallback(Custom3DRendering, &data);

    //ImVec2 data[2] = { canvas_pos, canvas_size };

    //draw_list->AddCallback([](const ImDrawList* parent_list, const ImDrawCmd* cmd, void* user_data)
    //    {
    //        ImVec2* data = static_cast<ImVec2*>(user_data);
    //        Custom3DRendering(parent_list, cmd, data[0], data[1]);
    //    }, data);

    DEBUG_MSG("UI.cpp : Viewport() :  GLRenderer* glRenderer = dynamic_cast<GLRenderer*>(m_renderer);.");
    GLRenderer* glRenderer = dynamic_cast<GLRenderer*>(m_renderer);

    DEBUG_MSG("UI.cpp : Viewport() : if (glRenderer) .");
    if (glRenderer) 
    {
        DEBUG_MSG("UI.cpp : Viewport() : GLCamera& camera = glRenderer->GetCamera();.");
        GLCamera& camera = glRenderer->GetCamera();
        // Continue with your rendering logic
    }
    else 
    {
        DEBUG_MSG("�RUI.cpp : Viewport() :  Handle the case where the cast fails.");
        // Handle the case where the cast fails (i.e., m_renderer is not an instance of GLRenderer)
    }

    DEBUG_MSG("UI.cpp : Viewport() : ImGui::End();.");
    ImGui::End();
    DEBUG_MSG("UI.cpp : Viewport() : Completed.");
}

void UI::FolderContent(ImVec2 window_size)
{
    ImGui::SetNextWindowPos(ImVec2(window_size.x * 0.2f, 20 + (window_size.y - 20) * 0.7f));
    ImGui::SetNextWindowSize(ImVec2(window_size.x * 0.6f, (window_size.y - 20) * 0.3f)); // decreased height percentage
    ImGui::Begin("Folder Content");

    if (m_sceneTreeID == 0)
    {
        m_sceneTreeID = m_uniqueIDGenerator.GenerateUniqueID("");
    }

    // TODO: add folder content content
    ImGui::End();
}

void UI::Inspector(ImVec2 window_size)
{
    ImGui::SetNextWindowPos(ImVec2(window_size.x * 0.8f, 20));
    ImGui::SetNextWindowSize(ImVec2(window_size.x * 0.2f, window_size.y - 20));
    ImGui::Begin("Inspector");
    if (m_sceneTreeID == 0) 
    {
        m_sceneTreeID = m_uniqueIDGenerator.GenerateUniqueID("");
    }
    // TODO: add inspector content
    ImGui::End();
}

void UI::MainWindowsInterface()
{
    DEBUG_MSG("UI.cpp : MainWindowsInterface() : Enters MainWindowsInterface.");
    UI::DockSetting();

    // Dockable windows creation should happen in each frame
    DEBUG_MSG("UI.cpp : MainWindowsInterface() : Dockable windows creation should happen in each frame.");
   
    DEBUG_MSG("UI.cpp : MainWindowsInterface() : ImGuiIO& io = ImGui::GetIO();.");
    ImGuiIO& io = ImGui::GetIO();
    DEBUG_MSG("UI.cpp : MainWindowsInterface() : ImVec2 window_size = io.DisplaySize;.");
    ImVec2 window_size = io.DisplaySize;
    
    DEBUG_MSG("UI.cpp : MainWindowsInterface() : UI::SceneTree(window_size);.");
    UI::SceneTree(window_size);
    DEBUG_MSG("UI.cpp : MainWindowsInterface() : UI::ProjectExplorer(window_size);.");
    UI::ProjectExplorer(window_size);
    DEBUG_MSG("UI.cpp : MainWindowsInterface() : UI::Viewport(window_size);.");
    UI::Viewport(window_size);
    DEBUG_MSG("UI.cpp : MainWindowsInterface() : UI::FolderContent(window_size);.");
    UI::FolderContent(window_size);
    DEBUG_MSG("UI.cpp : MainWindowsInterface() :UI::Inspector(window_size);.");
    UI::Inspector(window_size);

    DEBUG_MSG("UI.cpp : MainWindowsInterface() : MainWindowsInterface() completed.");
}

void UI::CursorOverMutualWindows()
{
    DEBUG_MSG("UI.cpp : CursorOverMutualWindows() : Enters CursorOverMutualWindows().");

    static ImGuiID last_hovered_window_ID = 0;
    static ImGuiID hovered_window_ID = 0;

    // Get the ID of the hovered window
    ImGuiWindow* hovered_window = ImGui::GetCurrentContext()->HoveredWindow;
    DEBUG_MSG("UI.cpp : CursorOverMutualWindows() : Hovered Window :");
    
    if (hovered_window) 
    {
        hovered_window_ID = m_uniqueIDGenerator.GenerateUniqueID(std::string(hovered_window->Name));
    }
    else {
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
    DEBUG_MSG("UI.cpp : RenderUIElements() : Enters RenderUIElements().");

    MainTopMenu();
    MainWindowsInterface();
    //CursorOverMutualWindows();
    
    // Show ImGui demo window
    //static bool show_demo_window = true;
    //ImGui::ShowDemoWindow(&show_demo_window);

    DEBUG_MSG("UI.cpp : RenderUIElements() : RenderUIElements() completed.");
}

void UI::Render()
{
    DEBUG_MSG("UI.cpp : Render() : Enters Render().");

    // Initialize platform backend if it hasn't already been initialized
    DEBUG_MSG("UI.cpp : Render() : Initialize platform backend.");
    if (!m_backendInitialized) {
        ImGui_ImplSDL2_NewFrame(static_cast<SDL_Window*>(m_window->GetNativeWindowHandle()));
        ImGui_ImplOpenGL3_NewFrame();
        m_backendInitialized = true;
    }

    ImGui::NewFrame();

    // Call RenderUI() to render the UI elements
    DEBUG_MSG("UI.cpp : Render() : Call RenderUI() to render the UI elements.");
    RenderUIElements();

    // Update main viewport size to match the window size
    int windowWidth, windowHeight;
    SDL_GetWindowSize(static_cast<SDL_Window*>(m_window->GetNativeWindowHandle()), &windowWidth, &windowHeight);
    //ImGui::GetMainViewport()->Size = ImVec2(static_cast<float>(windowWidth), static_cast<float>(windowHeight));

    ImGui::Render();

    // Set up the OpenGL backend for rendering the UI
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Clear the screen with the background color set by ImGui
    DEBUG_MSG("UI.cpp : Render() : Clear the screen with the background color.");
    int display_w, display_h;
    SDL_GL_GetDrawableSize(static_cast<SDL_Window*>(m_window->GetNativeWindowHandle()), &display_w, &display_h);
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(static_cast<float>(display_w), static_cast<float>(display_h)));
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    DEBUG_MSG("�GUI.cpp : Render() : Render() completed.");
}

void UI::Initialize()
{
    DEBUG_MSG("UI.cpp : Initialize() : Enters UI::Initialize().");

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Initialize ImGui SDL2 platform backend
    ImGui_ImplSDL2_InitForOpenGL(static_cast<SDL_Window*>(m_window->GetNativeWindowHandle()), m_window->GetOpenGLContext());

    // Initialize ImGui OpenGL3 renderer backend
    ImGui_ImplOpenGL3_Init("#version 430");

    ImGui::StyleColorsDark();
    //ImGui_ImplSDL2_InitForOpenGL(static_cast<SDL_Window*>(m_window->GetNativeWindowHandle()), m_renderer->GetContext());
    // Check if the SDL2 platform backend is already initialized
    if (io.BackendPlatformUserData == nullptr) 
    {
        ImGui_ImplSDL2_InitForOpenGL(static_cast<SDL_Window*>(m_window->GetNativeWindowHandle()), m_renderer->GetContext());
    }

    // Enable docking
    DEBUG_MSG("UI.cpp : Initialize() : Enable docking.");
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Set up SDL2 input
    DEBUG_MSG("UI.cpp : Initialize() : Set up SDL2 input.");
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;  // Enable mouse position reporting
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;     // Enable gamepad navigation
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;    // Enable mouse cursors

    // Set up display size
    DEBUG_MSG("UI.cpp : Initialize() : Set up display size.");
    int windowWidth, windowHeight;
    m_window->GetWindowSize(&windowWidth, &windowHeight);
    io.DisplaySize = ImVec2((float)windowWidth, (float)windowHeight);

    DEBUG_MSG("�GUI.cpp : Initialize() : UI::Initialize() completed.");
}
#endif // UI_CPP