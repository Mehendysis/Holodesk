// UIElements.cpp


#include "UIElements.h"
#include "Debug.h"
#include <imgui_internal.h>



void UIElements::RenderUIElements()
{
    DEBUG_MSG("UIElements : RenderUIElements() : Enters RenderUIElements().");

    MainTopMenu();
    MainWindowsInterface();
    //CursorOverMutualWindows();

    // Show ImGui demo window
    //static bool show_demo_window = true;
    //ImGui::ShowDemoWindow(&show_demo_window);

    DEBUG_MSG("UIElements : RenderUIElements() : RenderUIElements() completed.");
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

void UIElements::MainTopMenu()
{
    DEBUG_MSG("UIElements : MainMenu() : Enters MainMenu().");

    // Render a top bar menu
    DEBUG_MSG("UIElements : MainMenu() : Render a top bar menu.");
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

void UIElements::SceneTree(ImVec2 window_size)
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

void UIElements::ProjectExplorer(ImVec2 window_size)
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

void UIElements::Viewport(ImVec2 window_size)
{
    DEBUG_MSG("¢BGLUI.cpp : Viewport() : Enters Viewport().");

    // Get current window size
    ImVec2 viewport_size = ImGui::GetWindowSize();

    ImGui::SetNextWindowPos(ImVec2(window_size.x * 0.2f, 20));
    ImGui::SetNextWindowSize(ImVec2(window_size.x * 0.6f, (window_size.y - 20) * 0.7f)); // increased height percentage
    ImGui::Begin("Viewport");

    if (m_viewportID == 0)
    {
        m_viewportID = m_uniqueIDGenerator.GenerateUniqueID("");
    }

    //Move to a GL file like GLUI
    //// Get the size of the ImGui viewport
    //float viewport_width = ImGui::GetContentRegionAvail().x;
    //float viewport_height = ImGui::GetContentRegionAvail().y;

    //// Set the viewport size in the renderer
    //m_glRenderer->SetViewportSize(viewport_width, viewport_height);

    //// Calculate the aspect ratio of the viewport
    //float aspect_ratio = viewport_width / viewport_height;

    //// Set the projection matrix in the renderer to match the aspect ratio
    //m_glRenderer->SetProjectionMatrix(glm::perspective(glm::radians(45.0f), aspect_ratio, 0.1f, 100.0f));

    ImGui::End();

    //// Call the necessary OpenGL functions to render the 3D scene
    //m_glRenderer->RenderScene();

    //// Get the ImGui draw list
    //ImDrawList* draw_list = ImGui::GetWindowDrawList();

    //// Set the rendering viewport to the size of the ImGui viewport
    //int fb_width, fb_height;
    //SDL_GL_GetDrawableSize(m_glWindow->GetSDLWindow(), &fb_width, &fb_height);
    //glViewport(0, 0, fb_width, fb_height);

    //// Clear the rendering buffer
    //glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    DEBUG_MSG("CGLUI.cpp : Viewport() : Completed.");
}

// TODO : Try this outside of this file, maybe in GLUI and DXUI and keep this file dirctx-less and opengl-less
//To add a real - time 3D rendered scene by OpenGL in the content of your imgui window, you first need to render your scene to a Frame Buffer Object(FBO) 1. After that, you will end up with a Texture(of type GLuint) containing your rendered scene.To print it into Dear imgUI, just call a Draw Image Command 1.
//
//Here is an example of how to do it in C++:
//
//// Create an OpenGL texture
//GLuint my_opengl_texture = 0;
//glGenTextures(1, &my_opengl_texture);
//glBindTexture(GL_TEXTURE_2D, my_opengl_texture);
//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//// Render your scene to an FBO
//GLuint my_fbo = 0;
//glGenFramebuffers(1, &my_fbo);
//glBindFramebuffer(GL_FRAMEBUFFER_EXT, my_fbo);
//glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, my_opengl_texture, 0);
//
//// Draw the texture into your imgui window
//ImGui::Image((void*)(intptr_t)my_opengl_texture, ImVec2(width, height));

//// Working
//void UIElements::Viewport(ImVec2 window_size)
//{
//    DEBUG_MSG("UIElements : Viewport() : Enters Viewport().");
//
//    // Get current window size
//    ImVec2 viewport_size = ImGui::GetWindowSize();
//
//    ImGui::SetNextWindowPos(ImVec2(window_size.x * 0.2f, 20));
//    ImGui::SetNextWindowSize(ImVec2(window_size.x * 0.6f, (window_size.y - 20) * 0.7f)); // increased height percentage
//    ImGui::Begin("Viewport");
//
//    if (m_viewportID == 0)
//    {
//        m_viewportID = m_uniqueIDGenerator.GenerateUniqueID("");
//    }
//
//    // Get the size of the ImGui viewport
//    float viewport_width = ImGui::GetContentRegionAvail().x;
//    float viewport_height = ImGui::GetContentRegionAvail().y;
//
//    // Set the viewport size in the renderer
//    m_glRenderer->SetViewportSize(viewport_width, viewport_height);
//
//    // Calculate the aspect ratio of the viewport
//    float aspect_ratio = viewport_width / viewport_height;
//
//    // Set the projection matrix in the renderer to match the aspect ratio
//    m_glRenderer->SetProjectionMatrix(glm::perspective(glm::radians(45.0f), aspect_ratio, 0.1f, 100.0f));
//
//    // Get the ImGui draw list
//    ImDrawList* draw_list = ImGui::GetWindowDrawList();
//
//    // Set the rendering viewport to the size of the ImGui viewport
//    int fb_width, fb_height;
//    SDL_GL_GetDrawableSize(m_glWindow->GetSDLWindow(), &fb_width, &fb_height);
//    glViewport(0, 0, fb_width, fb_height);
//
//    // Clear the rendering buffer
//    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    // Call the necessary OpenGL functions to render the 3D scene
//    m_glRenderer->RenderScene();
//
//    ImGui::End();
//    DEBUG_MSG("UIElements : Viewport() : Completed.");
//}

//void UIElements::Viewport(ImVec2 window_size)
//{
//    DEBUG_MSG("UIElements : Viewport() : Enters Viewport().");
//
//    ImGui::SetNextWindowPos(ImVec2(window_size.x * 0.2f, 20));
//    ImGui::SetNextWindowSize(ImVec2(window_size.x * 0.6f, (window_size.y - 20) * 0.7f)); // increased height percentage
//    ImGui::Begin("Viewport");
//
//    if (m_viewportID == 0)
//    {
//        m_viewportID = m_uniqueIDGenerator.GenerateUniqueID("");
//    }
//
//    ImGui::End();
//    DEBUG_MSG("UIElements : Viewport() : Completed.");
//}

//void UIElements::Viewport(ImVec2 window_size)
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
    //    DEBUG_MSG("UIElements : Viewport() : Create a new renderer object.");
    //    GLCamera* camera = m_glCamera;
    //    m_glRenderer = new GLRenderer(static_cast<unsigned short int>(window_size.x), static_cast<unsigned short int>(window_size.y), *m_glCamera, m_sdlWindow);

    //    // Initialize the 3D viewport
    //    DEBUG_MSG("UIElements : Viewport() : Initialize the 3D viewport.");
    //    m_glRenderer->InitializeGL3DViewport(static_cast<int>(window_size.x), static_cast<int>(window_size.y));

    //    //// Initialize the framebuffer
    //    DEBUG_MSG("UIElements : Viewport() : Initialize the framebuffer.");
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
    //    DEBUG_MSG("UIElements : Viewport() : GLCamera& camera = glRenderer->GetCamera();.");
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

void UIElements::FolderContent(ImVec2 window_size)
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

void UIElements::Inspector(ImVec2 window_size)
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

void UIElements::MainWindowsInterface()
{
    DEBUG_MSG("UIElements : MainWindowsInterface() : Enters MainWindowsInterface.");
    UIElements::DockSetting();

    // Dockable windows creation should happen in each frame
    DEBUG_MSG("UIElements : MainWindowsInterface() : Dockable windows creation should happen in each frame.");

    DEBUG_MSG("UIElements : MainWindowsInterface() : ImGuiIO& io = ImGui::GetIO();.");
    ImGuiIO& io = ImGui::GetIO();
    DEBUG_MSG("UIElements : MainWindowsInterface() : ImVec2 window_size = io.DisplaySize;.");
    ImVec2 window_size = io.DisplaySize;

    DEBUG_MSG("UIElements : MainWindowsInterface() : UIElements::SceneTree(window_size);.");
    UIElements::SceneTree(window_size);
    DEBUG_MSG("UIElements : MainWindowsInterface() : UIElements::ProjectExplorer(window_size);.");
    UIElements::ProjectExplorer(window_size);
    DEBUG_MSG("UIElements : MainWindowsInterface() : UIElements::Viewport(window_size);.");
    UIElements::Viewport(window_size);
    DEBUG_MSG("UIElements : MainWindowsInterface() : UIElements::FolderContent(window_size);.");
    UIElements::FolderContent(window_size);
    DEBUG_MSG("UIElements : MainWindowsInterface() :UI::Inspector(window_size);.");
    UIElements::Inspector(window_size);

    DEBUG_MSG("UIElements : MainWindowsInterface() : MainWindowsInterface() completed.");
}

void UIElements::DockSetting()
{
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");

    if (!ImGui::DockBuilderGetNode(dockspace_id))
    {
        DEBUG_MSG("UIElements : MainInterface() : Enters MainInterface().");

        // Dockspace layout creation should only happen once
        DEBUG_MSG("UIElements : MainInterface() : Dockspace layout creation should only happen once.");
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoDockingInCentralNode;

        // Render dockspace
        DEBUG_MSG("UIElements : MainInterface() : Render dockspace.");
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), dockspace_flags);

        MutualResizeWindow();

        // Create dockable windows
        DEBUG_MSG("UIElements : MainInterface() :Create dockable windows.");
        ImGui::DockBuilderRemoveNode(dockspace_id);
        ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetIO().DisplaySize);

        ImGui::DockBuilderDockWindow("Scene Tree", ImGui::GetID("Scene Tree"));
        ImGui::DockBuilderDockWindow("Project Explorer", ImGui::GetID("Project Explorer"));
        ImGui::DockBuilderDockWindow("Viewport", ImGui::GetID("Viewport"));
        ImGui::DockBuilderDockWindow("Folder Content", ImGui::GetID("Folder Content"));
        ImGui::DockBuilderDockWindow("Inspector", ImGui::GetID("Inspector"));

        ImGui::DockBuilderFinish(dockspace_id);
        DEBUG_MSG("UIElements : MainInterface() : Dockable windows created.");
    }
    DEBUG_MSG("UIElements : MainInterface() : MainInterface completed.");
}

void UIElements::MutualResizeWindow()
{
    DEBUG_MSG("UIElements : MutualResizeWindow() : Enters MutualResizeWindow().");
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 window_size = io.DisplaySize;

    float window_width = window_size.x / 2;

    // Create left child window
    DEBUG_MSG("UIElements : MutualResizeWindow() : Create left child window.");
    ImGui::BeginChild("Left Panel", ImVec2(window_width, window_size.y), true);
    ImGui::Text("Left Pane");
    ImGui::EndChild();

    ImGui::SameLine();

    // Create right child window
    DEBUG_MSG("UIElements : MutualResizeWindow() : Create right child window.");
    ImGui::BeginChild("Right Panel", ImVec2(window_width, window_size.y), true);
    ImGui::Text("Right Pane");
    ImGui::EndChild();

    // Handle resizing
    DEBUG_MSG("UIElements : MutualResizeWindow() : Handle resizing.");
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
    DEBUG_MSG("UIElements : MutualResizeWindow() : Set child window sizes.");
    ImGui::SetCursorPosX(0);
    ImGui::SetWindowSize("Left Pane", ImVec2(window_width, window_size.y));
    ImGui::SetCursorPosX(window_width);
    ImGui::SetWindowSize("Right Pane", ImVec2(window_size.x - window_width, window_size.y));

    DEBUG_MSG("UIElements : MutualResizeWindow() : MutualResizeWindow has ended.");
}


void UIElements::CursorOverMutualWindows()
{
    //    DEBUG_MSG("UIElements : CursorOverMutualWindows() : Enters CursorOverMutualWindows().");
    //
    //    static ImGuiID last_hovered_window_ID = 0;
    //    static ImGuiID hovered_window_ID = 0;
    //
    //    // Get the ID of the hovered window
    //    ImGuiWindow* hovered_window = ImGui::GetCurrentContext()->HoveredWindow;
    //    DEBUG_MSG("UIElements : CursorOverMutualWindows() : Hovered Window :");
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

