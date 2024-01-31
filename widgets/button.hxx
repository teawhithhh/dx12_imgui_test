#ifndef BUTTON
#define BUTTON

#include <iostream>
#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IM_VEC2_CLASS_EXTRA
#define IMGUI_DEFINE_MATH_OPERATORS
#endif

#include "button_id_generator.hxx"
#include "logger.hxx"
#include "style.hxx"
#include "parser.hxx"
#include "imgui.h"
#include "imgui_internal.h"
#include <sstream>
#include <string>

enum class button_pos { left, center, right, STANDART };

template <typename Func>
class Button {
    public:
        Button(std::string label, const ImVec2& sizeArg, const float& rounding, button_pos posButton, const int& margin, const int& topMargin, ImGuiButtonFlags flags, Func onClick) : label_{label}, sizeArg_{sizeArg}, rounding_{rounding}, posButton_{posButton}, margin_{margin}, topMargin_{topMargin}, flags_{flags}, onClick_{onClick}
        {
            using namespace ImGui;

            id_ = ButtonIdGenerator::GenerateId();


            window_ = GetCurrentWindow();
            imguiId_ = window_->GetID(id_);
            labelSize_ = CalcTextSize(label_.c_str(), NULL, true);

            size_ = CalcItemSize(sizeArg_, labelSize_.x + style_.FramePadding.x * 2.0f, labelSize_.y + style_.FramePadding.y * 2.0f);

            log_.AddLog(type_log::debug, "Created button full settings, label: \"%s\", id: %s\n", label_.c_str(), std::to_string(id_).c_str());
        }

        Button(std::string label, const ImVec2& sizeArg, const float& rounding, Func onClick) : label_{label}, sizeArg_{sizeArg}, rounding_{rounding}, posButton_{button_pos::STANDART}, margin_{0}, topMargin_{0}, flags_{ImGuiButtonFlags_None}, onClick_{onClick}
        {
            using namespace ImGui;

            id_ = ButtonIdGenerator::GenerateId();
            log_.AddLog(type_log::debug, "Created button, label: \"%s\", id: %s\n", label_.c_str(), std::to_string(id_).c_str());

            window_ = GetCurrentWindow();
            imguiId_ = window_->GetID(id_);
            labelSize_ = CalcTextSize(label_.c_str(), NULL, true);

            size_ = CalcItemSize(sizeArg_, labelSize_.x + style_.FramePadding.x * 2.0f, labelSize_.y + style_.FramePadding.y * 2.0f);
        }

        bool operator()()
        {
            using namespace ImGui;
            static auto& g = g_;


            if (window_->SkipItems)
                return false;

            pos_ = window_->DC.CursorPos;
            if ((flags_ & ImGuiButtonFlags_AlignTextBaseLine) && style_.FramePadding.y < window_->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
                pos_.y += window_->DC.CurrLineTextBaseOffset - style_.FramePadding.y;

            switch (posButton_)
            {
            case button_pos::STANDART:
                break;
            case button_pos::left:
                pos_.x += margin_;
                break;

            case button_pos::center:
                pos_.x = window_->DC.CursorPos.x + (window_->WorkRect.GetWidth() - size_.x) * 0.5f;
                break;

            case button_pos::right:
                pos_.x = window_->WorkRect.Max.x - size_.x - margin_;
                break;
            }

            pos_.y += topMargin_;

            ImRect bb_ = ImRect(pos_, pos_ + size_);

            ItemSize(size_, style_.FramePadding.y);
            if (!ItemAdd(bb_, imguiId_))
                return false;

            bool hovered, held;
            bool pressed = ButtonBehavior(bb_, imguiId_, &hovered, &held, flags_);

            // Render
            const ImU32 col = GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
            RenderNavHighlight(bb_, imguiId_);
            RenderFrame(bb_.Min, bb_.Max, col, true, ImMax(style_.FrameRounding, rounding_));

            if (g_.LogEnabled)
                LogSetNextTextDecoration("[", "]");
            PushStyleColor(ImGuiCol_Text, CONFIG(["button"]["button_text_color"]));
            RenderTextClipped(bb_.Min + style_.FramePadding, bb_.Max - style_.FramePadding, label_.c_str(), NULL, &labelSize_, style_.ButtonTextAlign, &bb_);
            PopStyleColor();

            // Automatically close popups
            //if (pressed && !(flags & ImGuiButtonFlags_DontClosePopups) && (window->Flags & ImGuiWindowFlags_Popup))
            //    CloseCurrentPopup();

            IMGUI_TEST_ENGINE_ITEM_INFO(imguiId_, label_, g_.LastItemData.StatusFlags);
            if (pressed)
                onClick_();

#ifdef DEBUG_DECORATOR
            if (firstStart == true)
            {
                    center = pos_ + ImVec2(size_.x * 0.5f, size_.y * 0.5f);
                    auto toString = [](auto val){ std::ostringstream oss; oss<< val; return oss.str(); };
                    log_.AddLog(type_log::debug, "Button pos, label: \"%s\", id: %s, pos_x: %s, pos_y %s\n", label_.c_str(), std::to_string(id_).c_str(), toString(center.x).c_str(), toString(center.y).c_str());
                    firstStart = false;
            }
#endif
            return pressed;

        }
    private:
        int id_;
        std::string label_;
        inline static auto& cfg_ = Toml_Parser::cfg;
        inline static auto& log_ = Logger::GetLogger();
        ImVec2 sizeArg_;
        float rounding_;
        button_pos posButton_;
        int margin_;
        int topMargin_;
        ImGuiButtonFlags flags_;
        Func onClick_;

#ifdef DEBUG_DECORATOR
        bool firstStart = true;
        ImVec2 center;
#endif

        ImGuiWindow* window_;
        ImGuiContext& g_ = *GImGui;
        ImGuiID imguiId_;
        ImGuiStyle& style_ = g_.Style;
        ImRect bb_;
        ImVec2 pos_;
        ImVec2 size_;
        ImVec2 labelSize_;
};

#endif // BUTTON
