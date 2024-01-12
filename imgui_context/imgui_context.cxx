#ifndef IMGUI_SETUP
#define IMGUI_SETUP

#include "imgui_context.hxx"
#include "spectrum.hxx"
#include "directx_context.hxx"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx12.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include <iostream>
#include <memory>

using namespace ImGui_context_ns;

ImGui_context::ImGui_context(HWND hwnd_, int width_, int height_) : width{width_}, height{height_}, hwnd{hwnd_}
{
    initialize_wnd_vec();
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    auto &io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    // Setup Dear ImGui style
    ImGui::Spectrum::StyleColorsSpectrum();
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

bool ImGui_context::call_window(id_wnd index)
{
    return IMGUI_WINDOWS[index]();
}

#endif
