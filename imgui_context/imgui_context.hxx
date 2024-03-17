#ifndef IMGUI_CONTEXT
#define IMGUI_CONTEXT

#include <d3d12.h>
#include <functional>
#include <memory>
#include <unordered_map>
#include "window.hxx"

namespace ImGuiContextNs{
    enum class id_wnd { window_decorator, main_window, login_window, logger };

    class ImGuiWindowContext {
        public:
            ImGuiWindowContext(HWND hwnd, int width, int height, int& posX, int& posY);
            ~ImGuiWindowContext();
            void Render();
            bool CallWindow(id_wnd index);
            inline static id_wnd g_currentWindow;
            inline static bool g_loggerEnabled = true;
            inline static bool g_decoratorEnabled = true;
        private:
            int width_;
            int height_;

            int& posX_;
            int& posY_;

            HWND hwnd_;
            void InitializeWndMap();
            std::unordered_map<id_wnd, Window*> imguiWindows_;
    };
} // ImGuiContextNs

#endif // IMGUI_CONTEXT
