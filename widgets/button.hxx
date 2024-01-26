#ifndef BUTTON
#define BUTTON

#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IM_VEC2_CLASS_EXTRA
#define IMGUI_DEFINE_MATH_OPERATORS
#endif

#include "logger.hxx"
#include "style.hxx"
#include "parser.hxx"
#include "imgui.h"
#include "imgui_internal.h"
#include <string>

enum class button_pos { left, center, right, STANDART };

template <typename Func>
class Button {
    public:
        Button(std::string label, const ImVec2& sizeArg, const float& rounding, button_pos posButton, const int& margin, const int& topMargin, ImGuiButtonFlags flags, Func onClick) : label_{label}, sizeArg_{sizeArg}, rounding_{rounding}, posButton_{posButton}, margin_{margin}, topMargin_{topMargin}, flags_{flags}, onClick_{onClick}
        {
            g_buttonCounter_++;
            id_ = g_buttonCounter_;
            log_.AddLog(type_log::debug, "Created button full settings, label: %s\n", label_.c_str());
        }

        Button(std::string label, const ImVec2& sizeArg, const float& rounding, Func onClick) : label_{label}, sizeArg_{sizeArg}, rounding_{rounding}, posButton_{button_pos::STANDART}, margin_{0}, topMargin_{0}, flags_{ImGuiButtonFlags_None}, onClick_{onClick}
        {
            g_buttonCounter_++;
            id_ = g_buttonCounter_;
            log_.AddLog(type_log::debug, "Created button, label: %s\n", label_);
        }

        bool operator()()
        {
            using namespace ImGui;
            ImGuiWindow* window = GetCurrentWindow();
            if (window->SkipItems)
                return false;

            ImGuiContext& g = *GImGui;
            const ImGuiStyle& style = g.Style;
            const ImGuiID id = window->GetID(id_);
            const ImVec2 label_size = CalcTextSize(label_.c_str(), NULL, true);

            ImVec2 pos = window->DC.CursorPos;
            if ((flags_ & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
                pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
            ImVec2 size = CalcItemSize(sizeArg_, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

            switch (posButton_)
            {
            case button_pos::STANDART:
                break;
            case button_pos::left:
                pos.x += margin_;
                break;

            case button_pos::center:
                pos.x = window->DC.CursorPos.x + (window->WorkRect.GetWidth() - size.x) * 0.5f;
                break;

            case button_pos::right:
                pos.x = window->WorkRect.Max.x - size.x - margin_;
                break;
            }

            pos.y += topMargin_;

            const ImRect bb(pos, pos + size);
            ItemSize(size, style.FramePadding.y);
            if (!ItemAdd(bb, id))
                return false;

            bool hovered, held;
            bool pressed = ButtonBehavior(bb, id, &hovered, &held, flags_);

            // Render
            const ImU32 col = GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
            RenderNavHighlight(bb, id);
            RenderFrame(bb.Min, bb.Max, col, true, ImMax(style.FrameRounding, rounding_));

            if (g.LogEnabled)
                LogSetNextTextDecoration("[", "]");
            PushStyleColor(ImGuiCol_Text, CONFIG(["button"]["button_text_color"]));
            RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, label_.c_str(), NULL, &label_size, style.ButtonTextAlign, &bb);
            PopStyleColor();

            // Automatically close popups
            //if (pressed && !(flags & ImGuiButtonFlags_DontClosePopups) && (window->Flags & ImGuiWindowFlags_Popup))
            //    CloseCurrentPopup();

            IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags);
            if (pressed)
                onClick_();
            return pressed;
        }
    private:
        inline static int g_buttonCounter_ = 1;
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
};

#endif // BUTTON
