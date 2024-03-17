#ifndef WINDOW
#define WINDOW

#include "imgui.h"
#include "imgui_internal.h"
#include "parser.hxx"

class Window {
    public:
        template<typename T>
        static T& GetInstance() {
            static T instance;
            return instance;
        }

        virtual bool Render() = 0;
        virtual ~Window() {}

    protected:
        ImVec2 size_;
        std::string name_;

        inline static auto& cfg_ = Toml_Parser::cfg;
};

#endif
