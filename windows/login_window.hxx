#ifndef LOGIN_WINDOW
#define LOGIN_WINDOW

#include "widget.hxx"
#include "input_text.hxx"
#include "button.hxx"

#include "imgui.h"
#include "imgui_internal.h"

#include "directx_context.hxx"
#include "window.hxx"

#include "logo.cxx"
#include <memory>

class LoginWindow : public Window {
    public:
        bool Render () override;
    private:
        LoginWindow();

        char loginBuffer[64];
        char passwordBuffer[64];

        dx::Image imageDX{logo_png, logo_len};

        void OnClickLogin();
        void OnClickRegister();

        inline static auto& log_ = Logger::GetLogger();

        friend class Window;
};
#endif
