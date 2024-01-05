#include "imgui.h"

template<typename Func>
CenteredControlWrapper ControlCenter::operator()(Func control) const {
    ImVec2 originalPos = ImGui::GetCursorPos();

    // Draw offscreen to calculate size
    ImGui::SetCursorPos(ImVec2(-10000.0f, -10000.0f));
    control();
    ImVec2 controlSize = ImGui::GetItemRectSize();

    // Draw at centered position
    ImGui::SetCursorPos(ImVec2((windowSize_.x - controlSize.x) * 0.5f, originalPos.y));
    control();

    return CenteredControlWrapper(ImGui::IsItemClicked());
}
