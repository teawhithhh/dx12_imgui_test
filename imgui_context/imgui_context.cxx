#ifndef IMGUI_SETUP
#define IMGUI_SETUP

#include "imgui_custom_widgets.cxx"
#include "imgui_context.hxx"
#include "styles.hxx"
#include "directx_context.hxx"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx12.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include <memory>

using namespace ImGui_context_ns;

ImGui_context::ImGui_context(HWND hwnd_) : hwnd{hwnd_}
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io_ptr = std::unique_ptr<ImGuiIO>(new ImGuiIO(ImGui::GetIO())); (void)*io_ptr;
    io_ptr->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    // Setup Dear ImGui style
    Style::embraceTheDarkness();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX12_Init(dx::DX_WINDOW::g_pd3dDevice, dx::DX_WINDOW::NUM_FRAMES_IN_FLIGHT,
        DXGI_FORMAT_R8G8B8A8_UNORM, dx::DX_WINDOW::g_pd3dSrvDescHeap,
        dx::DX_WINDOW::g_pd3dSrvDescHeap->GetCPUDescriptorHandleForHeapStart(),
        dx::DX_WINDOW::g_pd3dSrvDescHeap->GetGPUDescriptorHandleForHeapStart());
}

ImGui_context::~ImGui_context()
{
    dx::DX_WINDOW::WaitForLastSubmittedFrame();

    ImGui_ImplDX12_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void ImGui_context::test_window(ImVec4& clear_color, int width, int height)
{
    static bool Window_Opened = false;
    static float f = 0.0f;
    static int counter = 0;

    ImGui::SetNextWindowSize(ImVec2(static_cast<float>(width), static_cast<float>(height)));
    ImGui::SetNextWindowPos(ImVec2(0, 0));

    ImGui::Begin("Hello, world!", &Window_Opened, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit4("clear color", reinterpret_cast<float*>(&clear_color)); // Edit 3 floats representing a color

    if (ImGui_cWidgets::C_Button("Button", ImVec2(500, 40)))                           // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
    CENTERED_CONTROL(ImGui::Text("counter = %d", counter));

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}
#endif
