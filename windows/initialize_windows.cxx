// Includes realization of windows
#include "window_decorator.cxx"
#include "test_window.cxx"
#include "login_window.cxx"
#include "logger.hxx"

// Includes Imgui
#include "imgui.h"
#include "imgui_context.hxx"

// Includes std::function
#include <functional>

#define LAMBDA_WINDOW(lambda) std::function([height, width](){ return lambda(width, height); })
#define WND_ARR ImGuiContextNs::ImGuiWindowContext::imguiWindows_

// Initialize windows hashmap
void ImGuiContextNs::ImGuiWindowContext::InitializeWndMap()
{
    auto& log_ = Logger::GetLogger();
    int height = height_;
    int width = width_;
    WND_ARR[id_wnd::test_window] = LAMBDA_WINDOW(test_window);
    WND_ARR[id_wnd::login_window] = LAMBDA_WINDOW(login_window);
    WND_ARR[id_wnd::demo_window] = std::function([](){bool result = false; ImGui::ShowDemoWindow(&result); return result;});
    WND_ARR[id_wnd::logger] = std::function([&log_](){bool result = true; log_.Draw("Logger"); return result; });
    WND_ARR[id_wnd::window_decorator] = std::function([&](){ ImVec2 size(900, 25); Decorator("hz", size); return true; });
}
