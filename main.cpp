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
#include "logger.hxx"

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

    static int posX = (screenWidth/2)-WIDTH/2;
    static int posY = (screenHeight/2)-HEIGHT/2;


    // Инициализация directx
    dx::DX_WINDOW wnd(L"test", WIDTH, HEIGHT, static_cast<int>(posX), static_cast<int>(posY), 10);

    // Инициализация dear imgui
    ImGui_context_ns::ImGui_context imgui_wnd(wnd.get_hwnd(), WIDTH, HEIGHT-25, posX, posY);

    imgui_wnd.current_window = ImGui_context_ns::id_wnd::login_window;
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
        ::ImGui_ImplDX12_NewFrame();
        ::ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        if (imgui_wnd.current_window == ImGui_context_ns::id_wnd::login_window)
            imgui_wnd.call_window(ImGui_context_ns::id_wnd::login_window);
        if (imgui_wnd.current_window == ImGui_context_ns::id_wnd::test_window)
            imgui_wnd.call_window(ImGui_context_ns::id_wnd::test_window);
        if (imgui_wnd.current_window == ImGui_context_ns::id_wnd::demo_window)
            imgui_wnd.call_window(ImGui_context_ns::id_wnd::demo_window);
        if (imgui_wnd.logger_enabled == true)
            imgui_wnd.call_window(ImGui_context_ns::id_wnd::logger);
        if (imgui_wnd.decorator_enabled == true)
            imgui_wnd.call_window(ImGui_context_ns::id_wnd::window_decorator);

        SetWindowPos(wnd.get_hwnd(), NULL, posX, posY, WIDTH, HEIGHT, SWP_NOSIZE | SWP_NOZORDER);

       // Рендер кадра ImGui
        imgui_wnd.Render_();
        wnd.render_loop_dx12();
    }
}
