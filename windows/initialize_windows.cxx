#define IM_VEC2_CLASS_EXTRA
#define IMGUI_DEFINE_MATH_OPERATORS

// Includes realization of windows
#include "login_window.hxx"
#include "window_decorator.hxx"
#include "logger.hxx"
#include "main_window.hxx"

// Includes Imgui
#include "imgui.h"
#include "imgui_context.hxx"

// Includes std::function
#include <functional>

#define WND_ARR ImGuiContextNs::ImGuiWindowContext::imguiWindows_

// Initialize windows hashmap
void ImGuiContextNs::ImGuiWindowContext::InitializeWndMap()
{
    WND_ARR[id_wnd::main_window] = &(Window::GetInstance<MainWindow>());
    WND_ARR[id_wnd::login_window] = &(Window::GetInstance<LoginWindow>());
    WND_ARR[id_wnd::logger] = &(Window::GetInstance<Logger>());
    WND_ARR[id_wnd::window_decorator] = &(Window::GetInstance<DecoratorWindow>());
}
