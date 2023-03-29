//ImGuiWrapper.h
#pragma once
//#include <cstdint>
#include <imgui.h>

namespace ImGuiWrapper
{
    // Define your own ID type (e.g. uint16_t)
    typedef uint8_t IDType;

    // Counter to generate unique IDs
    static IDType s_IDCounter = 0;

    // Wrapper function that calls ImGui::PushID with a custom ID scheme
    inline void SetWindowID(IDType id)
    {
        ImGui::PushID(s_IDCounter++);
        ImGui::PushID(id);
    }

    // Function to get the current value of s_IDCounter
    inline IDType GetCurrentID()
    {
        return s_IDCounter;
    }
}
