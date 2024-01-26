#ifndef WIDGETS
#define WIDGETS

#include "imgui.h"

namespace ImGui_cWidgets {
    enum class button_pos { left, center, right, STANDART };
    bool C_ButtonEx(const char* label, const ImVec2& size_arg, const float& rounding , button_pos pos_button, const int& margin = 0, const int& top_margin = 0, ImGuiButtonFlags flags = ImGuiButtonFlags_None);
    bool C_Button(const char*, const ImVec2&, const float&);
} // ImGui_cWidgets

#endif // WIDGETS
