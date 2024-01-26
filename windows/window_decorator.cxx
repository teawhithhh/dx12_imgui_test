#include <exception>
#define IM_VEC2_CLASS_EXTRA
#define IMGUI_DEFINE_MATH_OPERATORS

#include "imgui.h"
#include "style.hxx"
#include "parser.hxx"
#include "logger.hxx"
#include "imgui_custom_widgets.hxx"
#include "controler_z_order/control_z_order.hxx"

void Decorator(const char* title, int& posX, int& posY, ImVec2& windowSize)
{
    auto& cfg = Toml_Parser::cfg;
    ImGui::SetNextWindowPos(ImVec2(-1,-1));
    ImGui::SetNextWindowSize(windowSize);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, CONFIG(["decorator"]["decorator_color"]));
    ImGui::Begin(title, WindowZOrder_Decorator, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    ImGui::PopStyleColor();

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
        posX += static_cast<int>(0.95f * (cursorPos.x - oldPos.x));
        posY += static_cast<int>(0.95f * (cursorPos.y - oldPos.y));
    } else if (!isMouseDown) {
        is_holding = false;
    }

    ImGui::PushStyleColor(ImGuiCol_Button, CONFIG(["control_buttons"]["exit_button_color"]));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, CONFIG(["control_buttons"]["exit_button_color_hovered"]));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, CONFIG(["control_buttons"]["exit_button_color_active"]));
    if (ImGui_cWidgets::C_ButtonEx(" ", ImVec2(20,20), 10.0f, ImGui_cWidgets::button_pos::right, 3, -2, ImGuiButtonFlags_None))
        exit(0);
    ImGui::PopStyleColor(3);
    ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_Button, CONFIG(["control_buttons"]["minimize_button_color"]));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, CONFIG(["control_buttons"]["minimize_button_color_hovered"]));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, CONFIG(["control_buttons"]["minimize_button_color_active"]));
    if (ImGui_cWidgets::C_ButtonEx(" ", ImVec2(20,20), 10.0f, ImGui_cWidgets::button_pos::right, 30, -2, ImGuiButtonFlags_None))
        exit(0);
    ImGui::PopStyleColor(3);

    ImGui::End();
}
