#ifndef IMGUI_CONTEXT
#define IMGUI_CONTEXT

#include <d3d12.h> // hwnd
#include <functional> // std::function
#include <unordered_set> // unordered_map

namespace ImGuiContextNs{
    enum class id_wnd { window_decorator, test_window, login_window, demo_window, logger };

    class ImGuiWindowContext {
        public:
            ImGuiWindowContext(HWND hwnd, int width, int height, int& posX, int& posY);
            ~ImGuiWindowContext();
            void Render();
            bool CallWindow(id_wnd index);
            inline static id_wnd currentWindow;
            inline static bool loggerEnabled = true;
            inline static bool decoratorEnabled = true;
        private:
            int width_;
            int height_;

            int& posX_;
            int& posY_;

            HWND hwnd_;
            void InitializeWndMap();
            std::unordered_map<id_wnd, std::function<bool()>> imguiWindows_;
    };
} // ImGuiContextNs

#endif // IMGUI_CONTEXT
