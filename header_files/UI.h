// UI.h
#pragma once

#include <Renderer.h>
#include <Window.h>
#include <imgui.h>

class UI
{
public:
    UI(Window* window, Renderer* renderer);
    ~UI();

    void Initialize();
    void Render();
    void MainTopMenu();
    void MutualResizeWindow();
    void MainWindowsInterface();
    void RenderUIElements();
    void CursorOverMutualWindows();

private:
    Window* m_window;
    Renderer* m_renderer;
    bool m_backendInitialized = false;
    static const uint8_t SCENE_TREE = 1;
    static const uint8_t PROJECT_EXPLORER = 2;
    static const uint8_t VIEWPORT = 3;
    static const uint8_t FOLDER_CONTENT = 4;
    static const uint8_t INSPECTOR = 5;
};