#include "test_window.cxx"
#include "login_window.cxx"
#include "imgui.h"
#include "imgui_context.hxx"
#include <functional>

#define command_len 100
#define _(id_wnd) static_cast<int>(id_wnd)
#define LAMBDA_WINDOW(lambda) std::function([height_, width_](){ return lambda(width_, height_); })
#define wnd_vec ImGui_context_ns::ImGui_context::IMGUI_WINDOWS

void ImGui_context_ns::ImGui_context::initialize_wnd_vec()
{
    int height_ = height;
    int width_ = width;
    wnd_vec[_(id_wnd::test_window)] = LAMBDA_WINDOW(test_window);
    wnd_vec[_(id_wnd::login_window)] = LAMBDA_WINDOW(login_window);
}
