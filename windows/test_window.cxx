#include "center_control_helper/center_control_helper.hxx"
#include "button.hxx"
#include "controler_z_order/control_z_order.hxx"
#include "imgui_context.hxx"
#include "imgui.h"

bool test_window(int width, int height)
{
    static int counter = 0;


    ImGui::SetNextWindowSize(ImVec2(static_cast<float>(width), static_cast<float>(height)));
    ImGui::SetNextWindowPos(ImVec2(0, 25));

    ImGui::Begin("Hello, world!", WindowZOrder_MainWindow, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);

    Button button("Button", ImVec2(300, 40), 10.0f, [](){ImGuiContextNs::ImGuiWindowContext::g_currentWindow = ImGuiContextNs::id_wnd::login_window;});
    CENTERED_CONTROL(button());
    CENTERED_CONTROL(ImGui::Text("counter = %d", counter));

    #ifdef DEBUG
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    #endif
    ImGui::End();
    return true;
}
