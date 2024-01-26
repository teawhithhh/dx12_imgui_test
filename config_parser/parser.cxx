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
    std::ifstream inputFile("config.toml");
    str_cfg.assign(std::istreambuf_iterator<char>(inputFile), std::istreambuf_iterator<char>());
    inputFile.close();
    try {
        cfg = toml::parse(str_cfg);
    } catch (const toml::parse_error& err) {
        cfg = toml::parse(standart_cfg);
    }
}

static Toml_Parser g_parser = Toml_Parser();

toml::table& get_parse_result()
{
    auto& log_ = Logger::GetLogger();
    static bool firstParse = true;
    if (firstParse == true)
        log_.AddLog(type_log::debug, "Readed toml config \n %s", g_parser.str_cfg.c_str());
    firstParse = false;
    return g_parser.cfg;
}
