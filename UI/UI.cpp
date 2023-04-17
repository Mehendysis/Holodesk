// UI.cpp

#include "UI.h"
#include <imgui.h>

// Constructor
UI::UI(Window* windowPtr) :
    m_windowPtr(windowPtr)
{
    // Set up ImGui
    ImGui::CreateContext();
    ImGui::SetCurrentContext(ImGui::CreateContext());
}

// Destructor
UI::~UI()
{
    // Clean up ImGui
    ImGui::DestroyContext();
}

