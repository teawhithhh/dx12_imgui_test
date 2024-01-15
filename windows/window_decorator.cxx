#include <exception>
#define IM_VEC2_CLASS_EXTRA
#define IMGUI_DEFINE_MATH_OPERATORS

#include "imgui.h"
#include "logger.hxx"
#include "imgui_custom_widgets.hxx"
#include "controler_z_order/control_z_order.hxx"

void Decorator(const char* title, int& posX, int& posY, ImVec2& windowSize)
{
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(windowSize);
    ImGui::Begin(title, WindowZOrder_Decorator, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse);

    static bool is_holding;

    const auto cursorPos = ImGui::GetMousePos();
    static auto oldPos = cursorPos;

    bool isMouseHovering = ImGui::IsWindowHovered();
    bool isMouseDown = ImGui::IsMouseDragging(ImGuiMouseButton_Left);

    if (isMouseHovering && isMouseDown && !is_holding)
    {
        oldPos = cursorPos;
        is_holding = true;
    }

    if (is_holding && isMouseDown)
    {
        posX += static_cast<int>(cursorPos.x - oldPos.x);
        posY += static_cast<int>(cursorPos.y - oldPos.y);
    } else if (!isMouseDown) {
        is_holding = false;
    }

    if (ImGui_cWidgets::C_Button("-", ImVec2(100,10), 10.0f))
        exit(0);
    ImGui::End();
}
