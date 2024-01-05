/*
   Nazar Fingerkovskiy test program
*/

#include "imgui_context.hxx"
#include "directx_context.hxx"
#include "windows.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx12.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include <tchar.h>

#define WIDTH 900
#define HEIGHT 600

#ifdef _DEBUG
#define DX12_ENABLE_DEBUG_LAYER
#endif

#ifdef DX12_ENABLE_DEBUG_LAYER
#include <dxgidebug.h>
#pragma comment(lib, "dxguid.lib")
#endif

int main(int, char**)
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Инициализация directx
    dx::DX_WINDOW wnd(L"test", WIDTH, HEIGHT, (screenWidth/2)-WIDTH/2, (screenHeight/2)-HEIGHT/2);

    // Инициализация dear imgui
    ImGui_context_ns::ImGui_context imgui_wnd(wnd.get_hwnd());

    static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 0.00f);

    auto [width, height] = wnd.get_size();


    bool show_test_window = true;
    bool done = false;
    while (!done)
    {
        // Обработчик событий окна виндовc
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        // Начало кадра imgui
        ImGui_ImplDX12_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        if (show_test_window)
            imgui_wnd.test_window(clear_color, width, height);

       // Рендер кадра ImGui
        ImGui::Render();
        wnd.render_loop_dx12(clear_color);
    }
}