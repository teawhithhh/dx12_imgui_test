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
#include <iostream>
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

    static int positionX = (screenWidth/2)-WIDTH/2;
    static int positionY = (screenHeight/2)-HEIGHT/2;

    // Initialization directx context
    dx::DX_WINDOW wnd(L"test", WIDTH, HEIGHT, static_cast<int>(positionX), static_cast<int>(positionY), 5);

    // Initialization imgui context
    ImGuiContextNs::ImGuiWindowContext imguiWnd(wnd.get_hwnd(), WIDTH, HEIGHT-25, positionX, positionY);

    imguiWnd.g_currentWindow = ImGuiContextNs::id_wnd::login_window;
    bool done = false;
    while (!done)
    {
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

        // Start frame imgui
        ::ImGui_ImplDX12_NewFrame();
        ::ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        if (imguiWnd.g_currentWindow == ImGuiContextNs::id_wnd::login_window)
            imguiWnd.CallWindow(ImGuiContextNs::id_wnd::login_window);
        if (imguiWnd.g_currentWindow == ImGuiContextNs::id_wnd::test_window)
            imguiWnd.CallWindow(ImGuiContextNs::id_wnd::test_window);
        if (imguiWnd.g_currentWindow == ImGuiContextNs::id_wnd::demo_window)
            imguiWnd.CallWindow(ImGuiContextNs::id_wnd::demo_window);
        if (imguiWnd.g_loggerEnabled == true)
            imguiWnd.CallWindow(ImGuiContextNs::id_wnd::logger);
        if (imguiWnd.g_decoratorEnabled == true)
            imguiWnd.CallWindow(ImGuiContextNs::id_wnd::window_decorator);

        ::SetWindowPos(wnd.get_hwnd(), NULL, positionX, positionY, WIDTH, HEIGHT, SWP_NOSIZE | SWP_NOZORDER);

       // Render frame imgui
        imguiWnd.Render();
        wnd.RenderLoopDX12();
    }
}
