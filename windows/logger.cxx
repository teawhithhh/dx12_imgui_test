#include "imgui.h"
#include "style.hxx"
#include "parser.hxx"
#include "imgui_custom_widgets.hxx"
#include "controler_z_order/control_z_order.hxx"
#include "logger.hxx"
#include <string>

// Global usage logger
static Logger g_Logger;

Logger::Logger()
{
    AutoScroll = true;
    Clear();
}

void Logger::Clear()
{
    Buf.clear();
    LineOffsets.clear();
    LineOffsets.push_back(0);
}

void Logger::AddLog(type_log type, const char* fmt, ...)
{
    int old_size = Buf.size();
    va_list args;
    va_start(args, fmt);

    std::string type_str;
    switch (type)
    {
        case type_log::debug:
            type_str = "[debug]";
            break;
        case type_log::info:
            type_str = "[info]";
            break;
        case type_log::warning:
            type_str = "[warning]";
            break;
        case type_log::error:
            type_str = "[error]";
            break;
        case type_log::critical_error:
            type_str = "[critical error]";
            break;
    }
    type_str += fmt;

    Buf.appendfv(type_str.c_str(), args);
    va_end(args);
    for (int new_size = Buf.size(); old_size < new_size; old_size++)
        if (Buf[old_size] == '\n')
            LineOffsets.push_back(old_size + 1);
}

void Logger::Draw(const char* title)
{
    auto& cfg = Toml_Parser::cfg;
    ImGui::PushStyleColor(ImGuiCol_WindowBg, CONFIG(["logger_window"]["logger_window_color"]));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, std::stof(cfg["logger_window"]["logger_window_rounding"].value_or("0.0")));
    ImGui::Begin(title, WindowZOrder::WindowZOrder_Logger, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
    ImGui::PopStyleColor();

    // Options menu
    if (ImGui::BeginPopup("Options"))
    {
        ImGui::Checkbox("Auto-scroll", &AutoScroll);
        ImGui::EndPopup();
    }

    // Main window
    if (ImGui_cWidgets::C_ButtonEx("options", ImVec2(0,0), 5, ImGui_cWidgets::button_pos::STANDART, 0, ImGuiButtonFlags_None))
        ImGui::OpenPopup("Options");
    ImGui::SameLine();
    bool clear = ImGui_cWidgets::C_ButtonEx("clear", ImVec2(0,0), 5, ImGui_cWidgets::button_pos::STANDART, 0, ImGuiButtonFlags_None);
    ImGui::SameLine();
    bool copy = ImGui_cWidgets::C_ButtonEx("copy", ImVec2(0,0), 5, ImGui_cWidgets::button_pos::STANDART, 0, ImGuiButtonFlags_None);
    ImGui::SameLine();
    Filter.Draw("Filter", -100.0f);

    ImGui::Separator();

    if (ImGui::BeginChild("scrolling", ImVec2(0, 0), ImGuiChildFlags_None, ImGuiWindowFlags_HorizontalScrollbar))
    {
        if (clear)
            Clear();
        if (copy)
            ImGui::LogToClipboard();

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        const char* buf = Buf.begin();
        const char* buf_end = Buf.end();
        if (Filter.IsActive())
        {
            // In this example we don't use the clipper when Filter is enabled.
            // This is because we don't have random access to the result of our filter.
            // A real application processing logs with ten of thousands of entries may want to store the result of
            // search/filter.. especially if the filtering function is not trivial (e.g. reg-exp).
            for (int line_no = 0; line_no < LineOffsets.Size; line_no++)
            {
                const char* line_start = buf + LineOffsets[line_no];
                const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                if (Filter.PassFilter(line_start, line_end))
                    ImGui::TextUnformatted(line_start, line_end);
            }
        }
        else
        {
            // The simplest and easy way to display the entire buffer:
            //   ImGui::TextUnformatted(buf_begin, buf_end);
            // And it'll just work. TextUnformatted() has specialization for large blob of text and will fast-forward
            // to skip non-visible lines. Here we instead demonstrate using the clipper to only process lines that are
            // within the visible area.
            // If you have tens of thousands of items and their processing cost is non-negligible, coarse clipping them
            // on your side is recommended. Using ImGuiListClipper requires
            // - A) random access into your data
            // - B) items all being the  same height,
            // both of which we can handle since we have an array pointing to the beginning of each line of text.
            // When using the filter (in the block of code above) we don't have random access into the data to display
            // anymore, which is why we don't use the clipper. Storing or skimming through the search result would make
            // it possible (and would be recommended if you want to search through tens of thousands of entries).
            ImGuiListClipper clipper;
            clipper.Begin(LineOffsets.Size);
            while (clipper.Step())
            {
                for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
                {
                    const char* line_start = buf + LineOffsets[line_no];
                    const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                    ImGui::TextUnformatted(line_start, line_end);
                }
            }
            clipper.End();
        }
        ImGui::PopStyleVar();

        // Keep up at the bottom of the scroll region if we were already at the bottom at the beginning of the frame.
        // Using a scrollbar or mouse-wheel will take away from the bottom edge.
        if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);
    }
    ImGui::EndChild();

    ImGui::PopStyleVar();
    ImGui::End();

}

Logger& Logger::GetLogger() {
    return g_Logger;
}
