#include <iostream>
#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IM_VEC2_CLASS_EXTRA
#define IMGUI_DEFINE_MATH_OPERATORS
#endif


#include "input_text.hxx"
#include "id_generator.hxx"
#include "logger.hxx"
#include "style.hxx"
#include "parser.hxx"
#include "imgui.h"
#include "imgui_internal.h"
#include <string>

#include "directx_context.hxx"

InputText::InputText(std::string label, const ImVec2& sizeArg, const float& rounding, char* buffer, size_t bufferLen) : label_{label}, sizeArg_{sizeArg}, rounding_{rounding}, buffer_{buffer}, bufferEnd_{buffer}, bufferLen_{bufferLen}
{
    using namespace ImGui;

    id_ = IdGenerator::GenerateId();


    window_ = GetCurrentWindow();
    imguiId_ = window_->GetID(id_);
    labelSize_ = CalcTextSize(label_.c_str(), NULL, true);

    size_ = CalcItemSize(sizeArg_, labelSize_.x + style_.FramePadding.x * 2.0f, labelSize_.y + style_.FramePadding.y * 2.0f);

    log_.AddLog(type_log::info, "Created test input text, label: \"%s\", id: %s\n", label_.c_str(), ToString(id_).get());
}

bool InputText::operator()()
{
    using namespace ImGui;

    static auto& g = g_;

    if (window_->SkipItems)
        return false;

    pos_ = window_->DC.CursorPos;
    pos_.x = window_->DC.CursorPos.x + (window_->WorkRect.GetWidth() - size_.x) * 0.5f;

    ImRect bb_ = ImRect(pos_, pos_ + size_);

    ItemSize(size_, style_.FramePadding.y);
    if (!ItemAdd(bb_, imguiId_))
        return false;

    textSize_ = ImGui::CalcTextSize(buffer_);
    const ImU32 col_ = ImGui::ColorConvertFloat4ToU32(CONFIG(["input_text"]["input_text_bg_color"]));
    const ImU32 col = ImGui::ColorConvertFloat4ToU32(CONFIG(["input_text"]["input_text_color"]));

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb_, imguiId_, &hovered, &held);

    RenderNavHighlight(bb_, imguiId_);
    RenderFrame(bb_.Min, bb_.Max, col_, true, ImMax(style_.FrameRounding, rounding_));

    if (IsMouseClicked(0) && !bb_.Contains(ImGui::GetMousePos()))
        isEditing_ = false;

    ImVec2 textPos(pos_.x + (sizeArg_.x / 2) - (textSize_.x/2), pos_.y + (sizeArg_.y/2) - (textSize_.y/2));
    ImVec2 labelPos(pos_.x + (sizeArg_.x / 2) - (labelSize_.x/2), pos_.y + (sizeArg_.y/2) - (labelSize_.y/2));


    if ((pressed && !held) || isEditing_) {


        if (dx::DX_WINDOW::keyPressed!=' ' && bufferEnd_ - buffer_ <= static_cast<int>(bufferLen_) - 1) {
            *bufferEnd_ = dx::DX_WINDOW::keyPressed;
            *(bufferEnd_ + 1) = '\0';
            bufferEnd_++;
            dx::DX_WINDOW::keyPressed = ' ';
        } else if (dx::DX_WINDOW::backSpacePressed == true) {
            dx::DX_WINDOW::backSpacePressed = false;
            *(bufferEnd_-1) = '\0';
            if (bufferEnd_ - buffer_ != 0)
                bufferEnd_--;
        }
        std::string backspace = dx::DX_WINDOW::backSpacePressed ? "true" : "false";

#ifdef DEBUG_INPUT_TEXT
        log_.AddLog(type_log::debug, "x: %s, y: %s, buffer: %s, pos: %s\n", ToString(textPos.x).get(), ToString(textPos.y).get(), buffer_, ToString(static_cast<int>(bufferEnd_ - buffer_)).get());
#endif

        if (textSize_.x <= sizeArg_.x - 20 && textSize_.y <= sizeArg_.y) {

            ImVec2 cursorScreenPos = ImVec2(textPos.x + textSize_.x, textPos.y);
            cursorScreenPos.y += 10.0f;
            cursorScreenPos.x += 2.0f;

            ImVec2 lineStart(cursorScreenPos.x, cursorScreenPos.y - 10.0f);
            ImVec2 lineEnd(cursorScreenPos.x, cursorScreenPos.y + 10.0f);

            window_->DrawList->AddText(g.Font, g.FontSize, textPos, col, buffer_);
            window_->DrawList->AddLine(lineStart, lineEnd, col);
        } else {
            std::string clippedText;
            float availableWidth = sizeArg_.x - 20;
            float widthOfTextThatFits = 0;

            for (char* c = buffer_; c<bufferEnd_; ++c)
            {
                float charEnd = CalcTextSize(c, c+1).x;
                if (widthOfTextThatFits + charEnd <= availableWidth){
                    clippedText += *c;
                    widthOfTextThatFits += charEnd;
                } else {
                    clippedText += *c;
                    widthOfTextThatFits += charEnd;
                    widthOfTextThatFits -= CalcTextSize(clippedText.c_str(), clippedText.c_str()+1).x;
                    clippedText = shiftAndDelete(clippedText);
                }
            }
            log_.AddLog(type_log::debug, "widthOfTextThatFits: %s, availableWidth: %s, clippedText: %s\n", ToString(widthOfTextThatFits).get(), ToString(availableWidth).get(), clippedText.c_str());

            ImVec2 clipTextSize = ImGui::CalcTextSize(clippedText.c_str());
            ImVec2 clipTextPos(pos_.x + (sizeArg_.x / 2) - (clipTextSize.x/2), pos_.y + (sizeArg_.y/2) - (clipTextSize.y/2));

            ImVec2 cursorScreenPos = ImVec2(clipTextPos.x + clipTextSize.x, clipTextPos.y);
            cursorScreenPos.y += 10.0f;
            cursorScreenPos.x += 2.0f;

            ImVec2 lineStart(cursorScreenPos.x, cursorScreenPos.y - 10.0f);
            ImVec2 lineEnd(cursorScreenPos.x, cursorScreenPos.y + 10.0f);

            window_->DrawList->AddText(g.Font, g.FontSize, clipTextPos, col, clippedText.c_str());
            window_->DrawList->AddLine(lineStart, lineEnd, col);
        }
        isEditing_ = true;
    } else if (buffer_ != bufferEnd_){
        if (textSize_.x <= sizeArg_.x && textSize_.y <= sizeArg_.y) {
            window_->DrawList->AddText(g.Font, g.FontSize, textPos, col, buffer_);
        } else {
            std::string clippedText;
            float availableWidth = sizeArg_.x - 20;
            float widthOfTextThatFits = 0;

            for (char* c = buffer_; c<bufferEnd_; ++c)
            {
                float charEnd = CalcTextSize(c, c+1).x;
                if (widthOfTextThatFits + charEnd <= availableWidth){
                    clippedText += *c;
                    widthOfTextThatFits += charEnd;
                } else {
                    clippedText += *c;
                    widthOfTextThatFits += charEnd;
                    widthOfTextThatFits -= CalcTextSize(clippedText.c_str(), clippedText.c_str()+1).x;
                    clippedText = shiftAndDelete(clippedText);
                }
            }
            log_.AddLog(type_log::debug, "widthOfTextThatFits: %s, availableWidth: %s, clippedText: %s\n", ToString(widthOfTextThatFits).get(), ToString(availableWidth).get(), clippedText.c_str());

            ImVec2 clipTextSize = ImGui::CalcTextSize(clippedText.c_str());
            ImVec2 clipTextPos(pos_.x + (sizeArg_.x / 2) - (clipTextSize.x/2), pos_.y + (sizeArg_.y/2) - (clipTextSize.y/2));

            window_->DrawList->AddText(g.Font, g.FontSize, clipTextPos, col, clippedText.c_str());
        }
    } else {
        window_->DrawList->AddText(g.Font, g.FontSize, labelPos, col, label_.c_str());
    }
//            IMGUI_TEST_ENGINE_ITEM_INFO(imguiId_, label_, g_.LastItemData.StatusFlags);

    return pressed;
}

std::string InputText::shiftAndDelete(const std::string& str) {
    if (str.length() <= 1) {
        return "";
    } else {
        return str.substr(1);
    }
}

InputText::~InputText(){}
