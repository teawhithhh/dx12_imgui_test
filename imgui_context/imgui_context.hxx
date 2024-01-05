#ifndef IMGUI_CONTEXT
#define IMGUI_CONTEXT

#include "imgui.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include <memory>

namespace ImGui_context_ns{
    class ImGui_context;
}

class ImGui_context_ns::ImGui_context {
    public:
        ImGui_context(HWND hwnd_);
        ~ImGui_context();
        void test_window(ImVec4& clear_color, int width, int height);
    private:
        HWND hwnd;
        std::unique_ptr<ImGuiIO> io_ptr {nullptr};
};

#endif
