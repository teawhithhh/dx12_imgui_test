#include "center_control_helper/center_control_helper.hxx"
#include "controler_z_order/control_z_order.hxx"
#include "imgui_context.hxx"
#include "imgui_custom_widgets.hxx"
#include "imgui.h"

bool login_window(int width, int height)
{
    ImGui::SetNextWindowSize(ImVec2(static_cast<float>(width), static_cast<float>(height)));
    ImGui::SetNextWindowPos(ImVec2(0, 25));

    ImGui::Begin("Hello, world!", WindowZOrder_MainWindow, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);

    CENTERED_CONTROL(ImGui::Text("HZ LAUNCHER."));

    if (ImGui_cWidgets::C_Button("Button", ImVec2(500, 40), 10.0f))
    {

    #ifndef DEBUG_STYLES
        ImGui_context_ns::ImGui_context::current_window = ImGui_context_ns::id_wnd::test_window;
    #else
        ImGui_context_ns::ImGui_context::current_window = ImGui_context_ns::id_wnd::demo_window;
    #endif
    }

    #ifdef DEBUG
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    #endif
    ImGui::End();
    return true;
}
