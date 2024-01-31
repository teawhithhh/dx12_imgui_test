#ifndef EXEPTIONS
#define EXEPTIONS

#include <exception>
#include <filesystem>
#include <iostream>
#include <string>
#include "logger.hxx"
#include <source_location>

enum class Error_action { throwing, terminating, logging };
constexpr Error_action default_Error_action = Error_action::logging;
enum class Error_code { parser_error, call_window_error, directx_creation_window_error };

template<Error_action action = default_Error_action, class C>
void expect(C cond, Error_code x, const std::source_location loc = std::source_location::current())
{
    std::string error_code_name[] { "parser_error", "call_window_error", "directx_creation_window_error" };
    auto relative_path = std::filesystem::relative(loc.file_name());

    auto& log = Logger::GetLogger();
    if (action == Error_action::logging)
    {
        if (!cond())
            log.AddLog(type_log::warning, "except( \"%s\", %s:%s) %s failure: %s\n", relative_path.string().c_str(), std::to_string(loc.line()).c_str(), std::to_string(loc.column()).c_str(), loc.function_name(), error_code_name[static_cast<int>(x)].c_str());
    }
    if (action == Error_action::throwing)
    {
        if (!cond()){
            log.AddLog(type_log::error, "except( \"%s\", %s:%s) %s failure: %s\n", relative_path.string().c_str(), std::to_string(loc.line()).c_str(), std::to_string(loc.column()).c_str(), loc.function_name(), error_code_name[static_cast<int>(x)].c_str());
            throw x;
        }
    }
    if (action == Error_action::terminating)
    {
        if (!cond()) {
            log.AddLog(type_log::critical_error, "except( \"%s\", %s:%s) %s failure: %s\n", relative_path.string().c_str(), std::to_string(loc.line()).c_str(), std::to_string(loc.column()).c_str(), loc.function_name(), error_code_name[static_cast<int>(x)].c_str());
            Logger::EndLogger();
            std::terminate();
        }
    }
}

#endif
