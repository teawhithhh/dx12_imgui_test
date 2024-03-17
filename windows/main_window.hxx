#ifndef MAIN_WINDOW
#define MAIN_WINDOW

#include "input_text.hxx"
#include "button.hxx"

#include "imgui.h"
#include "imgui_internal.h"

#include "directx_context.hxx"
#include "window.hxx"

#include <memory>

class MainWindow : public Window {
    public:
        bool Render () override;
    private:
        MainWindow();

        ImVec2 childSize_;
        ImVec2 childNewsSize_;

        char loginBuffer_[64];

        int currentItem = 0;

        inline static auto& cfg_ = Toml_Parser::cfg;
        inline static auto& log_ = Logger::GetLogger();

        friend class Window;
};
#endif
