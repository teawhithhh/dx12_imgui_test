#ifndef LOGGER
#define LOGGER
#include "imgui.h"
#include <memory>
#include <sstream>
#include <fstream>
#include <cstring>

#include "window.hxx"

enum class type_log {debug, info, warning, error, critical_error};

template <typename T>
std::unique_ptr<char[]> ToString(T val) {
    std::ostringstream oss;
    oss << val;
    std::string str = oss.str();

    std::unique_ptr<char[]> cstr = std::make_unique<char[]>(str.size() + 1);
    std::memcpy(cstr.get(), str.c_str(), str.size() + 1);

    return cstr;
}

class Logger : public Window {
private:
    ~Logger();
    Logger();
    ImGuiTextBuffer     Buf;
    ImGuiTextFilter     Filter;
    ImVector<int>       LineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
    bool                AutoScroll;  // Keep scrolling if already at the bottom.
    std::ofstream       logFile;
public:
    void Clear();

    void AddLog(type_log type, const char* fmt, ...) IM_FMTARGS(3);

    bool Render() override;

    static Logger& GetLogger();
    static void EndLogger();

    friend class Window;
};
#endif
