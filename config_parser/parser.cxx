#define TOML_EXCEPTIONS 0

#include "parser.hxx"
#include "logger.hxx"
#include <filesystem>
#include <string_view>
#include <fstream>
#include "exeptions.hxx"

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
    toml::parse_result res = toml::parse_file("config.toml");
    if (res)
        cfg = res.table();
    else
        cfg = toml::parse(standart_cfg).table();
}

static Toml_Parser g_parser = Toml_Parser();

toml::table& get_parse_result()
{
    auto& log_ = Logger::GetLogger();
    static bool firstParse = true;

    if (firstParse == true)
    {
        toml::parse_result res = toml::parse_file("config.toml");
        log_.AddLog(type_log::info, "Reading toml config.\n");
        expect([&res](){ return res ? 1 : 0; }, Error_code::parser_error);
    }

    firstParse = false;
    return g_parser.cfg;
}
