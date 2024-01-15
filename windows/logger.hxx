#ifndef LOGGER
#define LOGGER
#include "imgui.h"

enum class type_log {debug, info, warning, error, critical_error};

class Logger{
private:
    ImGuiTextBuffer     Buf;
    ImGuiTextFilter     Filter;
    ImVector<int>       LineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
    bool                AutoScroll;  // Keep scrolling if already at the bottom.
public:
    Logger();
    void Clear();
    void AddLog(type_log type, const char* fmt, ...) IM_FMTARGS(3);
    void Draw(const char* title);
    static Logger& GetLogger();
};
#endif
