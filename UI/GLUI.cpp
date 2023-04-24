// GLUI.cpp

#ifndef GLUI_CPP
#define GLUI_CPP

#include "Debug.h"
#include "GLRenderer.h"

#include "GLUI.h"

#define IMGUI_CONFIG_FLAGS_HAS_DOCKING

#include <SDL.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

using namespace std;

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

void GLUI::MainTopMenu()
{
    DEBUG_MSG("GLUI.cpp : MainMenu() : Enters MainMenu().");

    // Render a top bar menu
    DEBUG_MSG("GLUI.cpp : MainMenu() : Render a top bar menu.");
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

void GLUI::MutualResizeWindow()
{
    DEBUG_MSG("GLUI.cpp : MutualResizeWindow() : Enters MutualResizeWindow().");
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 window_size = io.DisplaySize;

    float window_width = window_size.x / 2;

    // Create left child window
    DEBUG_MSG("GLUI.cpp : MutualResizeWindow() : Create left child window.");
    ImGui::BeginChild("Left Pane", ImVec2(window_width, window_size.y), true);
    ImGui::Text("Left Pane");
    ImGui::EndChild();

    ImGui::SameLine();

    // Create right child window
    DEBUG_MSG("GLUI.cpp : MutualResizeWindow() : Create right child window.");
    ImGui::BeginChild("Right Pane", ImVec2(window_width, window_size.y), true);
    ImGui::Text("Right Pane");
    ImGui::EndChild();

    // Handle resizing
    DEBUG_MSG("GLUI.cpp : MutualResizeWindow() : Handle resizing.");
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
    DEBUG_MSG("GLUI.cpp : MutualResizeWindow() : Set child window sizes.");
    ImGui::SetCursorPosX(0);
    ImGui::SetWindowSize("Left Pane", ImVec2(window_width, window_size.y));
    ImGui::SetCursorPosX(window_width);
    ImGui::SetWindowSize("Right Pane", ImVec2(window_size.x - window_width, window_size.y));

    DEBUG_MSG("GLUI.cpp : MutualResizeWindow() : MutualResizeWindow has ended.");
}

void GLUI::DockSetting()
{
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");

    if (!ImGui::DockBuilderGetNode(dockspace_id))
    {
        DEBUG_MSG("GLUI.cpp : MainInterface() : Enters MainInterface().");

        // Dockspace layout creation should only happen once
        DEBUG_MSG("GLUI.cpp : MainInterface() : Dockspace layout creation should only happen once.");
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoDockingInCentralNode;

        // Render dockspace
        DEBUG_MSG("GLUI.cpp : MainInterface() : Render dockspace.");
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), dockspace_flags);

        MutualResizeWindow();

        // Create dockable windows
        DEBUG_MSG("GLUI.cpp : MainInterface() :Create dockable windows.");
        ImGui::DockBuilderRemoveNode(dockspace_id);
        ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetIO().DisplaySize);

        ImGui::DockBuilderDockWindow("Scene Tree", ImGui::GetID("Scene Tree"));
        ImGui::DockBuilderDockWindow("Project Explorer", ImGui::GetID("Project Explorer"));
        ImGui::DockBuilderDockWindow("Viewport", ImGui::GetID("Viewport"));
        ImGui::DockBuilderDockWindow("Folder Content", ImGui::GetID("Folder Content"));
        ImGui::DockBuilderDockWindow("Inspector", ImGui::GetID("Inspector"));

        ImGui::DockBuilderFinish(dockspace_id);
        DEBUG_MSG("GLUI.cpp : MainInterface() : Dockable windows created.");
    }
    DEBUG_MSG("GLUI.cpp : MainInterface() : MainInterface completed.");
}


//struct Custom3DRenderingData {
//    ImVec2 canvas_pos;
//    ImVec2 canvas_size;
//};
//
//void Custom3DRendering(const ImDrawList* parent_list, const ImDrawCmd* cmd)
//{
//    Custom3DRenderingData* data = static_cast<Custom3DRenderingData*>(cmd->UserCallbackData);
//
//    int x = static_cast<int>(data->canvas_pos.x);
//    int y = static_cast<int>(data->canvas_pos.y);
//    int width = static_cast<int>(data->canvas_size.x);
//    int height = static_cast<int>(data->canvas_size.y);
//    glViewport(x, y, width, height);
//    glEnable(GL_SCISSOR_TEST);
//    glScissor(x, y, width, height);
//
//    // Render your 3D scene here
//    // ...
//
//    // Don't forget to disable the scissor test after rendering
//    glDisable(GL_SCISSOR_TEST);
//}

void GLUI::SceneTree(ImVec2 window_size)
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

void GLUI::ProjectExplorer(ImVec2 window_size)
{
    ImGui::SetNextWindowPos(ImVec2(0, 20 + (window_size.y - 20) * 0.7f));
    ImGui::SetNextWindowSize(ImVec2(window_size.x * 0.2f, (window_size.y - 20) * 0.3f)); // decreased height percentage
    ImGui::Begin("Project Explorer");

    if (m_projectExplorerID == 0)
    {
        m_projectExplorerID = m_uniqueIDGenerator.GenerateUniqueID("");
    }
    // TODO: add project explorer content
    ImGui::End();
}

void GLUI::Viewport(ImVec2 window_size)
{
    DEBUG_MSG("GLUI.cpp : Viewport() : Enters Viewport().");

    ImGui::SetNextWindowPos(ImVec2(window_size.x * 0.2f, 20));
    ImGui::SetNextWindowSize(ImVec2(window_size.x * 0.6f, (window_size.y - 20) * 0.7f)); // increased height percentage
    ImGui::Begin("Viewport");

    if (m_viewportID == 0)
    {
        m_viewportID = m_uniqueIDGenerator.GenerateUniqueID("");
    }

    ImGui::End();
    DEBUG_MSG("GLUI.cpp : Viewport() : Completed.");
}

//void GLUI::Viewport(ImVec2 window_size)
//{
    //DEBUG_MSG("GLUI.cpp : Viewport() : Enters Viewport().");

    //ImGui::SetNextWindowPos(ImVec2(window_size.x * 0.2f, 20));
    //ImGui::SetNextWindowSize(ImVec2(window_size.x * 0.6f, (window_size.y - 20) * 0.7f)); // increased height percentage
    //ImGui::Begin("Viewport");

    //if (m_sceneTreeID == 0)
    //{
    //    m_sceneTreeID = m_uniqueIDGenerator.GenerateUniqueID("");
    //}

    //ImVec2 viewportSize = ImGui::GetContentRegionAvail();

    //int width = static_cast<int>(window_size.x);
    //int height = static_cast<int>(window_size.y);

    //if (width <= 0 || height <= 0)
    //{
    //    // Handle invalid width and height values, e.g., by returning early from the function
    //    ImGui::End();
    //    return;
    //}

    // TODO: create and bind an FBO and render buffer
    // Set up the renderer and initialize the framebuffer
    //DEBUG_MSG("GLUI.cpp : Viewport() : Set up the renderer and initialize the framebuffer.");
    //if (!m_glRenderer)
    //{
    //    // Create a new renderer object
    //    DEBUG_MSG("GLUI.cpp : Viewport() : Create a new renderer object.");
    //    GLCamera* camera = m_glCamera;
    //    m_glRenderer = new GLRenderer(static_cast<unsigned short int>(window_size.x), static_cast<unsigned short int>(window_size.y), *m_glCamera, m_sdlWindow);

    //    // Initialize the 3D viewport
    //    DEBUG_MSG("GLUI.cpp : Viewport() : Initialize the 3D viewport.");
    //    m_glRenderer->InitializeGL3DViewport(static_cast<int>(window_size.x), static_cast<int>(window_size.y));

    //    //// Initialize the framebuffer
    //    DEBUG_MSG("GLUI.cpp : Viewport() : Initialize the framebuffer.");
    //    m_glRenderer->InitializeFBO(static_cast<int>(window_size.x), static_cast<int>(window_size.y));
    //}

    // Set up the renderer for rendering the 3D viewport
    //DEBUG_MSG("GLUI.cpp : Viewport() : Set up the renderer for rendering the 3D viewport.");
    //m_glRenderer.GL3DViewport();

    //ImVec2 canvas_pos = ImGui::GetCursorScreenPos(); // Get the position of the ImGui window
    //ImVec2 canvas_size = ImGui::GetContentRegionAvail(); // Get the available size of the ImGui window

    //Custom3DRenderingData data;
    //data.canvas_pos = canvas_pos;
    //data.canvas_size = canvas_size;

    //ImDrawList* draw_list = ImGui::GetWindowDrawList();
    //draw_list->AddCallback(Custom3DRendering, &data);

    //ImVec2 data[2] = { canvas_pos, canvas_size };

    //draw_list->AddCallback([](const ImDrawList* parent_list, const ImDrawCmd* cmd, void* user_data)
    //    {
    //        ImVec2* data = static_cast<ImVec2*>(user_data);
    //        Custom3DRendering(parent_list, cmd, data[0], data[1]);
    //    }, data);

    //DEBUG_MSG("GLUI.cpp : Viewport() :  GLRenderer* glRenderer = dynamic_cast<GLRenderer*>(m_glRenderer);.");
    //GLRenderer* glRenderer = dynamic_cast<GLRenderer*>(m_glRenderer.get());

    //DEBUG_MSG("GLUI.cpp : Viewport() : if (glRenderer) .");
    //if (glRenderer)
    //{
    //    DEBUG_MSG("GLUI.cpp : Viewport() : GLCamera& camera = glRenderer->GetCamera();.");
    //    GLCamera& camera = glRenderer->GetCamera();
    //    // Continue with your rendering logic
    //}
    //else
    //{
    //    DEBUG_MSG("¢RGLUI.cpp : Viewport() :  Handle the case where the cast fails.");
    //    // Handle the case where the cast fails (i.e., m_glRenderer is not an instance of GLRenderer)
    //}

    //DEBUG_MSG("GLUI.cpp : Viewport() : ImGui::End();.");
    //ImGui::End();
    //DEBUG_MSG("GLUI.cpp : Viewport() : Completed.");
//}

void GLUI::FolderContent(ImVec2 window_size)
{
    ImGui::SetNextWindowPos(ImVec2(window_size.x * 0.2f, 20 + (window_size.y - 20) * 0.7f));
    ImGui::SetNextWindowSize(ImVec2(window_size.x * 0.6f, (window_size.y - 20) * 0.3f)); // decreased height percentage
    ImGui::Begin("Folder Content");

    if (m_folderContentID == 0)
    {
        m_folderContentID = m_uniqueIDGenerator.GenerateUniqueID("");
    }

    // TODO: add folder content content
    ImGui::End();
}

void GLUI::Inspector(ImVec2 window_size)
{
    ImGui::SetNextWindowPos(ImVec2(window_size.x * 0.8f, 20));
    ImGui::SetNextWindowSize(ImVec2(window_size.x * 0.2f, window_size.y - 20));
    ImGui::Begin("Inspector");
    if (m_inspectorID == 0)
    {
        m_inspectorID = m_uniqueIDGenerator.GenerateUniqueID("");
    }
    // TODO: add inspector content
    ImGui::End();
}

void GLUI::MainWindowsInterface()
{
    DEBUG_MSG("GLUI.cpp : MainWindowsInterface() : Enters MainWindowsInterface.");
    GLUI::DockSetting();

    // Dockable windows creation should happen in each frame
    DEBUG_MSG("GLUI.cpp : MainWindowsInterface() : Dockable windows creation should happen in each frame.");

    DEBUG_MSG("GLUI.cpp : MainWindowsInterface() : ImGuiIO& io = ImGui::GetIO();.");
    ImGuiIO& io = ImGui::GetIO();
    DEBUG_MSG("GLUI.cpp : MainWindowsInterface() : ImVec2 window_size = io.DisplaySize;.");
    ImVec2 window_size = io.DisplaySize;

    DEBUG_MSG("GLUI.cpp : MainWindowsInterface() : GLUI::SceneTree(window_size);.");
    GLUI::SceneTree(window_size);
    DEBUG_MSG("GLUI.cpp : MainWindowsInterface() : GLUI::ProjectExplorer(window_size);.");
    GLUI::ProjectExplorer(window_size);
    DEBUG_MSG("GLUI.cpp : MainWindowsInterface() : GLUI::Viewport(window_size);.");
    GLUI::Viewport(window_size);
    DEBUG_MSG("GLUI.cpp : MainWindowsInterface() : GLUI::FolderContent(window_size);.");
    GLUI::FolderContent(window_size);
    DEBUG_MSG("GLUI.cpp : MainWindowsInterface() :UI::Inspector(window_size);.");
    GLUI::Inspector(window_size);

    DEBUG_MSG("GLUI.cpp : MainWindowsInterface() : MainWindowsInterface() completed.");
}

void GLUI::CursorOverMutualWindows()
{
//    DEBUG_MSG("GLUI.cpp : CursorOverMutualWindows() : Enters CursorOverMutualWindows().");
//
//    static ImGuiID last_hovered_window_ID = 0;
//    static ImGuiID hovered_window_ID = 0;
//
//    // Get the ID of the hovered window
//    ImGuiWindow* hovered_window = ImGui::GetCurrentContext()->HoveredWindow;
//    DEBUG_MSG("GLUI.cpp : CursorOverMutualWindows() : Hovered Window :");
//
//    if (hovered_window)
//    {
//        hovered_window_ID = m_uniqueIDGenerator.GenerateUniqueID(std::string(hovered_window->Name));
//    }
//    else {
//        hovered_window_ID = 0;
//    }
//
//    // Check if the mouse is hovering between windows
//    bool anyHovered = (hovered_window_ID & (m_sceneTreeID | m_projectExplorerID | m_viewportID | m_folderContentID | m_inspectorID));
//    //cout << "anyHovered = " << anyHovered << "\n";
//    bool anyLastHovered = (last_hovered_window_ID & (m_sceneTreeID | m_projectExplorerID | m_viewportID | m_folderContentID | m_inspectorID));
//    cout << "anyLastHovered = " << anyLastHovered << "\n";
//    if (anyHovered && anyLastHovered)
//    {
//        // Set cursor to resize cursor if hovering between windows
//        ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
//
//        // If the mouse is moving from one window to another, toggle the cursor to the arrow
//        if (last_hovered_window_ID != 0 && last_hovered_window_ID != hovered_window_ID)
//        {
//            ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
//        }
//
//        // Keep track of the last window hovered
//        last_hovered_window_ID = hovered_window_ID;
//    }
//    else
//    {
//        // Reset the last hovered window if the mouse is not hovering over any windows
//        ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
//        last_hovered_window_ID = 0;
//    }
}

void GLUI::RenderUIElements()
{
    DEBUG_MSG("GLUI.cpp : RenderUIElements() : Enters RenderUIElements().");

    MainTopMenu();
    MainWindowsInterface();
    //CursorOverMutualWindows();

    // Show ImGui demo window
    //static bool show_demo_window = true;
    //ImGui::ShowDemoWindow(&show_demo_window);

    DEBUG_MSG("GLUI.cpp : RenderUIElements() : RenderUIElements() completed.");
}

//void GLUI::Render(SDL_Window* sdlWindow)
//{
//    // Start ImGui frame
//    ImGui_ImplOpenGL3_NewFrame();
//    ImGui_ImplSDL2_NewFrame(sdlWindow);
//    ImGui::NewFrame();
//
//    // Render ImGui UI
//    ImGui::Begin("My Window");
//    // ...
//    ImGui::End();
//
//    // End ImGui frame
//    ImGui::Render();
//    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//}

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
    RenderUIElements();

    // Clear the framebuffer
    ImVec4 clear_color = ImGui::GetStyleColorVec4(ImGuiCol_WindowBg);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

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
