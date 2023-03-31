// UI.h
#pragma once

#include <Renderer.h>
#include <Window.h>
#include <imgui.h>

class UI
{
public:
    UI(Window* window, Renderer* renderer)
        : m_window(window)
        , m_renderer(renderer)
        , m_leftPanelID(0)
        , m_sceneTreeID(0)
        , m_projectExplorerID(0)
        , m_viewportID(0)
        , m_folderContentID(0)
        , m_inspectorID(0)
    {}

    ~UI();

    void Initialize();
    void Render();
    void MainTopMenu();
    void MutualResizeWindow();
    void MainWindowsInterface();
    void RenderUIElements();
    void CursorOverMutualWindows();
    void DockSetting();
    void SceneTree(ImVec2 window_size);
    void ProjectExplorer(ImVec2 window_size);
    void Viewport(ImVec2 window_size);
    void FolderContent(ImVec2 window_size);
    void Inspector(ImVec2 window_size);

private:
    Window* m_window;
    std::unique_ptr<Renderer> m_renderer;
    bool m_backendInitialized = false;
    ImGuiID m_leftPanelID;
    ImGuiID m_sceneTreeID;
    ImGuiID m_projectExplorerID;
    ImGuiID m_viewportID;
    ImGuiID m_folderContentID;
    ImGuiID m_inspectorID;
};