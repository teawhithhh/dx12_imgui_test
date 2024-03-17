#define IM_VEC2_CLASS_EXTRA
#define IMGUI_DEFINE_MATH_OPERATORS

#include "main_window.hxx"

#include "input_text.hxx"
#include "button.hxx"
#include "center_control_helper/center_control_helper.hxx"
#include "controler_z_order/control_z_order.hxx"
#include "imgui_context.hxx"
#include "imgui.h"

bool MainWindow::Render()
{
    static int counter = 0;


    ImGui::SetNextWindowSize(ImVec2(static_cast<float>(size_.x), static_cast<float>(size_.y)));
    ImGui::SetNextWindowPos(ImVec2(0, 25));

    ImGui::Begin(name_.c_str(), WindowZOrder_MainWindow, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);

    ImGui::SetCursorPos(ImVec2(static_cast<float>(size_.x)/2-childSize_.x/2 - 215, static_cast<float>(size_.y/2 - childSize_.y/2)));
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, std::stof(cfg_["login_window"]["login_window_rounding"].value_or("0.0")));
    ImGui::BeginChild("play frame", childSize_, ImGuiChildFlags_None, ImGuiWindowFlags_HorizontalScrollbar);
    static InputText loginInpt("ofsleep", ImVec2(350,40), 10.0f, loginBuffer_, 64);

    ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX(), ImGui::GetCursorPosY() + 32));
    loginInpt();
    const char* items[] = { "1.20.4", "1.20.3", "1.20.2" };
    if (ImGui::BeginCombo("Select an item", items[currentItem]))
    {
        for (int i = 0; i < IM_ARRAYSIZE(items); i++)
        {
            bool isSelected = (currentItem == i);
            if (ImGui::Selectable(items[i], isSelected))
                currentItem = i;

            // Если элемент выбран, установите флаг выбранного элемента так, чтобы он отображался в выпадающем списке
            if (isSelected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    ImGui::PopStyleVar();
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(static_cast<float>(size_.x)/2-childNewsSize_.x/2 + childSize_.x/2 + 25, static_cast<float>(size_.y/2 - childNewsSize_.y/2)));
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, std::stof(cfg_["login_window"]["login_window_rounding"].value_or("0.0")));
    ImGui::BeginChild("news frame", childNewsSize_, ImGuiChildFlags_None, ImGuiWindowFlags_HorizontalScrollbar);
    ImGui::PopStyleVar();
    ImGui::EndChild();


    #ifdef DEBUG
//    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    #endif
    ImGui::End();
    return true;
}

MainWindow::MainWindow(){
    name_ = "main window";
    size_ = ImVec2(900, 575);
    childSize_ = ImVec2(400, 300);
    childNewsSize_ = ImVec2(400, 520);
}
