#include "test_window.cxx"
#include "login_window.cxx"
#include "logger.hxx"
#include "imgui.h"
#include "imgui_context.hxx"
#include <functional>

#define LAMBDA_WINDOW(lambda) std::function([height_, width_](){ return lambda(width_, height_); })
#define wnd_arr ImGui_context_ns::ImGui_context::IMGUI_WINDOWS

void ImGui_context_ns::ImGui_context::initialize_wnd_vec()
{
    auto& log_ = Logger::GetLogger();
    int height_ = height;
    int width_ = width;
    wnd_arr[id_wnd::test_window] = LAMBDA_WINDOW(test_window);
    wnd_arr[id_wnd::login_window] = LAMBDA_WINDOW(login_window);
    wnd_arr[id_wnd::demo_window] = std::function([](){bool result = false; ImGui::ShowDemoWindow(&result); return result;});
    wnd_arr[id_wnd::logger] = std::function([&log_](){bool result = false; log_.Draw("Logger", &result); return result; });
}
