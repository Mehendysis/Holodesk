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
    void SetDisplay(Window* window);

private:
    Window* m_window;
    Renderer* m_renderer;
    bool m_backendInitialized = false;
};