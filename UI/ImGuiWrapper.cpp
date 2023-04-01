#include <cstdint>
#include <imgui.h>

namespace ImGuiWrapper
{
    // Define your own ID type (e.g. uint16_t)
    typedef uint16_t IDType;

    // Counter to generate unique IDs
    static IDType s_IDCounter = 0;

    // Wrapper function that calls ImGui::PushID with a custom ID scheme
    inline void SetWindowID(IDType id)
    {
        ImGui::PushID(s_IDCounter++);
        ImGui::PushID(id);
    }
}