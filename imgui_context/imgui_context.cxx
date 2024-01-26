#include "imgui_context.hxx"
#include "style.hxx"
#include "directx_context.hxx"
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx12.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include <iostream>
#include <memory>

using namespace ImGuiContextNs;

ImGuiWindowContext::ImGuiWindowContext(HWND hwnd, int width, int height, int& posX, int& posY) : width_{width}, height_{height}, posX_{posX}, posY_{posY}, hwnd_{hwnd}
{
    InitializeWndMap();
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    auto &io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    // Setup Dear ImGui style
    ImGui::Style::SetupStyle();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd_);
    ImGui_ImplDX12_Init(dx::DX_WINDOW::g_pd3dDevice, dx::DX_WINDOW::NUM_FRAMES_IN_FLIGHT,
        DXGI_FORMAT_R8G8B8A8_UNORM, dx::DX_WINDOW::g_pd3dSrvDescHeap,
        dx::DX_WINDOW::g_pd3dSrvDescHeap->GetCPUDescriptorHandleForHeapStart(),
        dx::DX_WINDOW::g_pd3dSrvDescHeap->GetGPUDescriptorHandleForHeapStart());
}

ImGuiWindowContext::~ImGuiWindowContext()
{
    dx::DX_WINDOW::WaitForLastSubmittedFrame();

    ImGui_ImplDX12_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiWindowContext::Render()
{
    ImGuiContext * ctx = ImGui::GetCurrentContext();
    std::stable_sort( ctx->Windows.begin(), ctx->Windows.end(),
            []( const ImGuiWindow * a, const ImGuiWindow * b ) {
                    return a->BeginOrderWithinContext < b->BeginOrderWithinContext;
            }
    );
    ImGui::Render();
}

bool ImGuiWindowContext::CallWindow(id_wnd index)
{
    return imguiWindows_[index]();
}
