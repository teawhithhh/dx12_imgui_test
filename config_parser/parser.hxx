#ifndef PARSER_TOML
#define PARSER_TOML

#include "toml.hpp"
#include <string>
#include <string_view>

using namespace std::string_view_literals;

toml::table& get_parse_result();

class Toml_Parser {
    public:
        Toml_Parser();
        inline static toml::table cfg;
        inline static std::string str_cfg;
    private:
        inline static constexpr std::string_view standart_cfg =
R"([text]
text_color = "0x000000"
text_color_disabled = "0xffffff"

[background]
bg_color = "0xfeefd0"
child_bg = "0xc6b79a"
popup_bg = "0xffffff"
frame_bg = "0x532D22"
framge_bg_hovered = "0xffffff"
frame_bg_active = "0xEAEAEA"
tiitle_bg = "0xE1E1E1"
title_bg_active = "0xEAEAEA"
title_bg_collapsed = "0xCACACA"
menu_bar_bg = "0xF5F5F5"
scroll_bar_bg = "0xD9CEB8"
text_selected_bg = "0x2680EB "
nav_window_dim_bg = "0xffffff"
modal_window_dim_bg = "0xffffff"

[scroll_bar]
scroll_bar_grab_color = "0x692A2A"
scroll_bar_grab_hovered_color = "0x853838"
scroll_bar_grab_active_color = "0x692A2A"

[slider]
slider_grab_color = "0x692A2A"
slider_grab_active = "0x692A2A"

[check_mark]
mark_color = "0x1473E6"

[header]
header_color = "0x2680EB"
header_hovered_color = "0x1473E6"
header_active_color = "0x0D66D0"

[separator]
separator_color = "0xCACACA"
separator_hovered_color = "0x8E8E8E"
separator_active_color = "0x707070"

[resize_grip]
resize_grip_color = "0xCACACA"
resize_grip_hovered_color = "0x8E8E8E"
resize_grip_active_color = "0x095ABA"

[plot_lines]
plot_lines_color = "0x2680E8"
plot_lines_hovered_color = "0x0D6600"
plot_lines_histogram_color = "0x2680EB"
plot_lines_histogram_hovered_color = "0x0D66D0"

[border]
border_color = "0xfeefd0"
border_shadow_color = "0x00000000"

[button]
button_color = "0x692A2A"
button_hovered_color = "0x853838"
button_active_color = "0x692A2A"
button_text_color = "0xDBCFB6"


[drag_drop]
drag_drop_target_color = "0xffffff"

[nav_highlight]
nav_highlight_color = "0xffffff"
nav_window_highlight_color = "0xffffff"

[decorator]
decorator_color = "0xC6B79A"

[logger_window]
logger_window_color = "0xC6B79A"
logger_childbg_color = "0xDBCFB6"
logger_debug_color = "0x692A2A"
logger_info_color = "0x0047FF"
logger_warning_color = "0xFF7A00"
logger_error_color = "0xFF5F5F"
logger_critical_color = "0xFF0000"
logger_window_rounding = "10.0"
logger_child_rounding = "10.0"

[control_buttons]
exit_button_color = "0xF5504E"
exit_button_color_active = "0xF55C5B"
exit_button_color_hovered = "0xF55C5B"
minimize_button_color = "0x9cb148"
minimize_button_color_active = "0x9cb148"
minimize_button_color_hovered = "0xacbf5e"

[login_window]
login_window_rounding = "10.0"

[input_text]
input_text_bg_color = "0xdbcfb6"
input_text_color = "0xfeefd0")"sv;


        void write_cfg();
        void read_cfg();
};
#endif
