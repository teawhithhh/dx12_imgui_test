#include "parser.hxx"
#include "logger.hxx"
#include <filesystem>
#include <iostream>
#include <string_view>
#include <fstream>


Toml_Parser::Toml_Parser() {
    if (!std::filesystem::exists("config.toml"))
        write_cfg();
    read_cfg();
}

void Toml_Parser::write_cfg() {
    std::ofstream standart_config("config.toml");
    standart_config << standart_cfg;
}

void Toml_Parser::read_cfg() {
    auto& log_ = Logger::GetLogger();
    std::ifstream inputFile("config.toml");
    std::string str_cfg((std::istreambuf_iterator<char>(inputFile)),
                         std::istreambuf_iterator<char>());
    inputFile.close();
    log_.AddLog(type_log::debug, "Readed toml config \n %s", str_cfg.c_str());

    toml::table res;
    try {
        cfg = toml::parse(str_cfg);
        log_.AddLog(type_log::info, "%s", "Parsing Succesed");
    } catch (const toml::parse_error& err) {
        log_.AddLog(type_log::error, "%s", "Parsing failed");
        cfg = toml::parse(standart_cfg);
    }
}

toml::table& Toml_Parser::get_parse_result()
{
    return cfg;
}
