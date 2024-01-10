#ifndef IMGUI_CONTEXT
#define IMGUI_CONTEXT

#include "imgui.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include <functional>
#include <vector>
#include <memory>

namespace ImGui_context_ns{
    class ImGui_context;
    enum class id_wnd { test_window, login_window };
}

class ImGui_context_ns::ImGui_context {
    public:
        ImGui_context(HWND hwnd_, int width_, int height_);
        ~ImGui_context();
        void initialize_wnd_vec();
        bool call_window(id_wnd index);
        inline static id_wnd current_window;
    private:
        int width;
        int height;

        HWND hwnd;
        std::unique_ptr<ImGuiIO> io_ptr {nullptr};
        std::vector<std::function<bool()>> IMGUI_WINDOWS {100, [](){return false;}};
};

#endif
