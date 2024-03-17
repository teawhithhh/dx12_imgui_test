#ifndef DECORATOR_WINDOW
#define DECORATOR_WINDOW

#include "imgui.h"

#include "window.hxx"
#include "logger.hxx"

#include <memory>

class DecoratorWindow : public Window {
    public:
        bool Render () override;
    private:
        DecoratorWindow();

        inline static auto& cfg_ = Toml_Parser::cfg;
        inline static auto& log_ = Logger::GetLogger();

        friend class Window;
};
#endif
