#ifndef WIDGET
#define WIDGET

#include "imgui.h"
#include "imgui_internal.h"

#include "parser.hxx"
#include "logger.hxx"

class Widget {
    public:
        virtual bool operator()() = 0;
        virtual int getID() {return id_;}
        virtual ~Widget() {}

    protected:
        int id_;

        inline static auto& cfg_ = Toml_Parser::cfg;
        inline static auto& log_ = Logger::GetLogger();

        ImGuiWindow* window_;
        ImGuiContext& g_ = *GImGui;
        ImGuiID imguiId_;
        ImGuiStyle& style_ = g_.Style;
        ImRect bb_;
        ImVec2 pos_;
        ImVec2 size_;
};

#endif
