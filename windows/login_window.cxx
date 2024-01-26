#define STB_IMAGE_IMPLEMENTATION

#include "center_control_helper/center_control_helper.hxx"
#include "controler_z_order/control_z_order.hxx"
#include "directx_context.hxx"
#include "imgui_context.hxx"
#include "stb_image.h"
#include "imgui_custom_widgets.hxx"
#include "imgui.h"
#include "parser.hxx"
#include "logger.hxx"

bool login_window(int width, int height)
{
    static auto& log_ = Logger::GetLogger();
    static auto& cfg = get_parse_result();

    static char password[64];
    log_.AddLog(type_log::debug, "%s\n", password);

    ImGui::SetNextWindowSize(ImVec2(static_cast<float>(width), static_cast<float>(height)));
    ImGui::SetNextWindowPos(ImVec2(0, 25));

    ImGui::Begin("Hello, world!", WindowZOrder_MainWindow, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);

    static dx::Image img_dx{"C:\\Users\\240821\\app\\imgui\\examples\\example_win32_directx12\\windows\\logo_500.png"};

    ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX(), ImGui::GetCursorPosY()+30));
    CENTERED_CONTROL(ImGui::Image(reinterpret_cast<ImTextureID>(img_dx.my_texture_srv_gpu_handle.ptr), ImVec2(static_cast<float>(img_dx.my_image_width), static_cast<float>(img_dx.my_image_height))));

    ImGui::SetCursorPos(ImVec2(static_cast<float>(width)/2-200, static_cast<float>(height-(img_dx.my_image_height-30)-200-50)));
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, std::stof(cfg["login_window"]["login_window_rounding"].value_or("0.0")));
    ImGui::BeginChild("scrolling", ImVec2(400, 200), ImGuiChildFlags_None, ImGuiWindowFlags_HorizontalScrollbar);
    CENTERED_CONTROL(ImGui::InputTextWithHint(" ", "<password>", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password));
    ImGui::PopStyleVar();
    ImGui::EndChild();


    ImVec2 pos = ImVec2(static_cast<float>(width)/2 - 200, ImGui::GetCursorPos().y + 25);
    ImGui::SetCursorPos(pos);
    if (ImGui_cWidgets::C_Button("Register", ImVec2(150, 40), 10.0f))
    {
    #ifndef DEBUG_STYLES
        ImGuiContextNs::ImGuiWindowContext::currentWindow = ImGuiContextNs::id_wnd::test_window;
    #else
        ImGuiContextNs::ImGuiWindowContext::currentWindow = ImGuiContextNs::id_wnd::demo_window;
    #endif
    }

    ImGui::SetCursorPos(ImVec2(pos.x + 250, pos.y));
    if (ImGui_cWidgets::C_Button("Login", ImVec2(150, 40), 10.0f))
    {}

    #ifdef DEBUG
    ImGui::SetCursorPos(ImVec2(5, 5));
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    #endif

    ImGui::End();
    return true;
}
