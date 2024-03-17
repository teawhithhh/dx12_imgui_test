#define IM_VEC2_CLASS_EXTRA
#define IMGUI_DEFINE_MATH_OPERATORS

#include <exception>
#include <iostream>

#include "window_decorator.hxx"

#include "button.hxx"
#include "imgui.h"
#include "style.hxx"
#include "controler_z_order/control_z_order.hxx"

bool DecoratorWindow::Render()
{
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(size_);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, CONFIG(["decorator"]["decorator_color"]));
    ImGui::PushStyleColor(ImGuiCol_Border, CONFIG(["decorator"]["decorator_color"]));
    ImGui::Begin(name_.c_str(), WindowZOrder_Decorator, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    ImGui::PopStyleColor(2);

    /*
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
    */

    static Button exit_button(" ", ImVec2(20,20), 10.0f, button_pos::right, 3, -2, ImGuiButtonFlags_None, [](){return;});
    static Button minimize_button(" ", ImVec2(20,20), 10.0f, button_pos::right, 30, -2, ImGuiButtonFlags_None, [](){return;});

    ImGui::PushStyleColor(ImGuiCol_Button, CONFIG(["control_buttons"]["exit_button_color"]));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, CONFIG(["control_buttons"]["exit_button_color_hovered"]));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, CONFIG(["control_buttons"]["exit_button_color_active"]));
    exit_button();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, CONFIG(["control_buttons"]["minimize_button_color"]));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, CONFIG(["control_buttons"]["minimize_button_color_hovered"]));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, CONFIG(["control_buttons"]["minimize_button_color_active"]));
    minimize_button();
    ImGui::PopStyleColor(3);

    ImGui::End();
    return true;
}

DecoratorWindow::DecoratorWindow(){
    name_ = "decorator window";
    size_ = ImVec2(900, 25);
}
