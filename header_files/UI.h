// UI.h

#pragma once
#include "UniqueIDGenerator.h"
#include "GLRenderer.h"
#include "Renderer.h"
#include "Window.h"

#include <imgui.h>

class UI {
public:
    UI() {};
    virtual ~UI() = 0;
    virtual void Render() = 0;


private:
    Window* m_window;
    Renderer* m_renderer;
    Camera* m_camera;

    mutable bool m_backendInitialized = false;
    ImGuiID m_leftPanelID;
    ImGuiID m_sceneTreeID;
    ImGuiID m_projectExplorerID;
    ImGuiID m_viewportID;
    ImGuiID m_folderContentID;
    ImGuiID m_inspectorID;

protected:
    bool IsBackendInitialized() const;
    void SetBackendInitialized(bool initialized) { m_backendInitialized = initialized; }

};

