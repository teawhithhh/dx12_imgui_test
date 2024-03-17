#define STB_IMAGE_IMPLEMENTATION
#define IM_VEC2_CLASS_EXTRA
#define IMGUI_DEFINE_MATH_OPERATORS

#include "login_window.hxx"
#include "button.hxx"
#include "imgui.h"

#include "center_control_helper/center_control_helper.hxx"
#include "controler_z_order/control_z_order.hxx"

#include "directx_context.hxx"
#include "imgui_context.hxx"

#include "stb_image.h"

#include <iostream>
#include <memory>

void LoginWindow::OnClickRegister()
{
    #ifndef DEBUG_STYLES
        ImGuiContextNs::ImGuiWindowContext::g_currentWindow = ImGuiContextNs::id_wnd::main_window;
    #else
        ImGuiContextNs::ImGuiWindowContext::g_currentWindow = ImGuiContextNs::id_wnd::demo_window;
    #endif
}

void LoginWindow::OnClickLogin()
{
    std::cout << "lol\n";
}

bool LoginWindow::Render()
{
    ImGui::SetNextWindowSize(ImVec2(static_cast<float>(size_.x), static_cast<float>(size_.y)));
    ImGui::SetNextWindowPos(ImVec2(0, 25));

    ImGui::Begin(name_.c_str(), WindowZOrder_MainWindow, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);

    ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX(), ImGui::GetCursorPosY()+30));
    CENTERED_CONTROL(ImGui::Image(reinterpret_cast<ImTextureID>(imageDX.my_texture_srv_gpu_handle.ptr), ImVec2(static_cast<float>(imageDX.my_image_width), static_cast<float>(imageDX.my_image_height))));

    ImGui::SetCursorPos(ImVec2(static_cast<float>(size_.x)/2-200, static_cast<float>(static_cast<int>(size_.y)-(imageDX.my_image_height-30)-200-50)));
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, std::stof(cfg_["login_window"]["login_window_rounding"].value_or("0.0")));
    ImGui::BeginChild("scrolling", ImVec2(400, 200), ImGuiChildFlags_None, ImGuiWindowFlags_HorizontalScrollbar);

    static InputText loginInpt("ofsleep", ImVec2(300, 50), 10.0f, loginBuffer, 64);
    static InputText passwordInpt("******", ImVec2(300, 50), 10.0f, passwordBuffer, 64);

    ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX(), ImGui::GetCursorPosY() + 40));
    loginInpt();
    ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX(), ImGui::GetCursorPosY() + 20));
    passwordInpt();
    ImGui::PopStyleVar();
    ImGui::EndChild();


    ImVec2 pos = ImVec2(static_cast<float>(size_.x)/2 - 200, ImGui::GetCursorPos().y + 25);

    ImGui::SetCursorPos(pos);
    static Button Register("Register", ImVec2(150, 40), 10.0f, [this](){OnClickRegister();});
    Register();

    ImGui::SetCursorPos(ImVec2(pos.x + 250, pos.y));
    static Button Login("Login", ImVec2(150, 40), 10.0f, [this](){OnClickLogin();});
    Login();

    #ifdef DEBUG
    ImGui::SetCursorPos(ImVec2(5, 5));
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    #endif

    ImGui::End();
    return true;
}

LoginWindow::LoginWindow(){
    name_ = "login_window";
    size_ = ImVec2(900,575);
}
