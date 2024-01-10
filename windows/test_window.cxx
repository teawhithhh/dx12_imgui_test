#include "center_control_helper/center_control_helper.hxx"
#include "imgui_context.hxx"
#include "imgui_custom_widgets.hxx"
#include "imgui.h"

bool test_window(int width, int height)
{
    static bool Window_Opened = false;
    static int counter = 0;

    ImGui::SetNextWindowSize(ImVec2(static_cast<float>(width), static_cast<float>(height)));
    ImGui::SetNextWindowPos(ImVec2(0, 0));

    ImGui::Begin("Hello, world!", &Window_Opened, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);                          // Create a window called "Hello, world!" and append into it.

    if (ImGui_cWidgets::C_Button("Button", ImVec2(500, 40)))                           // Buttons return true when clicked (most widgets return true when edited/activated)
        ImGui_context_ns::ImGui_context::current_window = ImGui_context_ns::id_wnd::login_window;
    CENTERED_CONTROL(ImGui::Text("counter = %d", counter));

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
    return true;
}
