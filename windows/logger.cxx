#include "button.hxx"
#include "imgui.h"
#include "style.hxx"
#include "parser.hxx"
#include "controler_z_order/control_z_order.hxx"
#include "logger.hxx"
#include <string>

// Global usage logger


Logger::Logger()
{
    logFile.open("log.txt", std::ios::app);
    AutoScroll = true;
    Clear();
}

Logger::~Logger()
{
    logFile << Buf.c_str();
    logFile.flush();
    logFile.close();
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
            type_str = "[debug] ";
            break;
        case type_log::info:
            type_str = "[info] ";
            break;
        case type_log::warning:
            type_str = "[warning] ";
            break;
        case type_log::error:
            type_str = "[error] ";
            break;
        case type_log::critical_error:
            type_str = "[critical error] ";
            break;
    }
    type_str += fmt;

    Buf.appendfv(type_str.c_str(), args);
    va_end(args);

    for (int new_size = Buf.size(); old_size < new_size; old_size++)
        if (Buf[old_size] == '\n')
            LineOffsets.push_back(old_size + 1);
}

bool StartsWithBracketed(const char* str, const char* prefix) {
    // Ищем открытую квадратную скобку
    const char* bracket_open = strchr(str, '[');
    if (bracket_open == nullptr)
        return false; // Если нет квадратной скобки, то строка не начинается с указанного префикса

    // Ищем закрывающую квадратную скобку
    const char* bracket_close = strchr(bracket_open, ']');
    if (bracket_close == nullptr || bracket_close - bracket_open < 2)
        return false; // Если нет закрывающей скобки или между скобками нет символов, строка не начинается с указанного префикса

    // Сравниваем содержимое между скобками с указанным префиксом
    return strncmp(bracket_open + 1, prefix, static_cast<size_t>(bracket_close - bracket_open) - 1) == 0;
}

bool SetColor(const char* str)
{
    auto& cfg_ = Toml_Parser::cfg;
    if (StartsWithBracketed(str, "debug"))
    {
        ImGui::PushStyleColor(ImGuiCol_Text, CONFIG(["logger_window"]["logger_debug_color"]));
        return true;
    } else if (StartsWithBracketed(str, "info")) {
        ImGui::PushStyleColor(ImGuiCol_Text, CONFIG(["logger_window"]["logger_info_color"]));
        return true;
    } else if (StartsWithBracketed(str, "warning")) {
        ImGui::PushStyleColor(ImGuiCol_Text, CONFIG(["logger_window"]["logger_warning_color"]));
        return true;
    } else if (StartsWithBracketed(str, "error")) {
        ImGui::PushStyleColor(ImGuiCol_Text, CONFIG(["logger_window"]["logger_error_color"]));
        return true;
    } else if (StartsWithBracketed(str, "critical error")) {
        ImGui::PushStyleColor(ImGuiCol_Text, CONFIG(["logger_window"]["logger_critical_color"]));
        return true;
    }

    return false;
}

bool Logger::Render()
{
    auto& cfg_ = Toml_Parser::cfg;

    ImGui::SetNextWindowSize(ImVec2(500, 350));

    ImGui::PushStyleColor(ImGuiCol_WindowBg, CONFIG(["logger_window"]["logger_window_color"]));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, std::stof(cfg_["logger_window"]["logger_window_rounding"].value_or("0.0")));
    ImGui::Begin("logger", WindowZOrder::WindowZOrder_Logger, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    ImGui::PopStyleColor();

    // Options menu
    if (ImGui::BeginPopup("Options"))
    {
        ImGui::Checkbox("Auto-scroll", &AutoScroll);
        ImGui::EndPopup();
    }

    // Main window
    static Button optionsButton("options", ImVec2(0,0), 5, button_pos::STANDART, 0, 0, ImGuiButtonFlags_None, [](){ ImGui::OpenPopup("Options"); });
    optionsButton();

    ImGui::SameLine();

    static Button clearButton("clear", ImVec2(0,0), 5, button_pos::STANDART, 0, 0, ImGuiButtonFlags_None, [](){});
    bool clear = clearButton();

    ImGui::SameLine();

    static Button copyButton("copy", ImVec2(0,0), 5, button_pos::STANDART, 0, 0, ImGuiButtonFlags_None, [](){});
    bool copy = copyButton();

    ImGui::SameLine();

    Filter.Draw("Filter", -100.0f);

    ImGui::Separator();

    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, std::stof(cfg_["logger_window"]["logger_child_rounding"].value_or("0.0")));
    ImGui::PushStyleColor(ImGuiCol_ChildBg, CONFIG(["logger_window"]["logger_childbg_color"]));
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
                {
                    ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPos().x + 10.0f, ImGui::GetCursorPos().y));
                    bool res = SetColor(line_start);
                    ImGui::TextUnformatted(line_start, line_end);
                    if (res)
                        ImGui::PopStyleColor();
                }
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
                    ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPos().x + 10.0f, ImGui::GetCursorPos().y));
                    bool res = SetColor(line_start);
                    ImGui::TextUnformatted(line_start, line_end);
                    if (res)
                        ImGui::PopStyleColor();
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
    ImGui::PopStyleColor();

    ImGui::PopStyleVar(2);
    ImGui::End();

    return true;
}

Logger& Logger::GetLogger() {
    return Window::GetInstance<Logger>();
}

void Logger::EndLogger() {
    Window::GetInstance<Logger>().~Logger();
}
