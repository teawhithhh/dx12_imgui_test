#ifndef IMGUI_CONTEXT
#define IMGUI_CONTEXT

#include "imgui.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include <functional>
#include <unordered_set>
#include <vector>
#include <memory>

namespace ImGui_context_ns{
    class ImGui_context;
    enum class id_wnd { window_decorator, test_window, login_window, demo_window, logger};
}

class ImGui_context_ns::ImGui_context {
    public:
        ImGui_context(HWND hwnd_, int width_, int height_, int& posX, int& posY);
        ~ImGui_context();
        void Render_();
        bool call_window(id_wnd index);
        inline static id_wnd current_window;
        inline static bool logger_enabled = true;
        inline static bool decorator_enabled = true;
    private:
        int width;
        int height;

        int& posX;
        int& posY;

        HWND hwnd;
        void initialize_wnd_vec();
        std::unordered_map<id_wnd, std::function<bool()>> IMGUI_WINDOWS;
};

#endif
