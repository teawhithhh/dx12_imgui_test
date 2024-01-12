#ifndef PARSER_TOML
#define PARSER_TOML

#include "toml.hpp"
#include <string_view>

using namespace std::string_view_literals;

class Toml_Parser {
    public:
        Toml_Parser();
        toml::table& get_parse_result();

    private:
        inline static constexpr std::string_view standart_cfg =
R"([text]
text_color = "0xDBCFB6"
text_color_disabled = "0xffffff"

[background]
bg_color = "0xfeefd0"
child_bg = "0xffffff"
popup_bg = "0xffffff"
frame_bg = "0x532D22"
framge_bg_hovered = "0xffffff"
frame_bg_active = "0xEAEAEA"
tiitle_bg = "0xE1E1E1"
title_bg_active = "0xEAEAEA"
title_bg_collapsed = "0xCACACA"
menu_bar_bg = "0xF5F5F5"
scroll_bar_bg = "0x33555555"
text_selected_bg = "0x2680EB "
nav_window_dim_bg = "0xffffff"
modal_window_dim_bg = "0xffffff"

[scroll_bar]
scroll_bar_grab_color = "0xCACACA"
scroll_bar_grab_hovered_color = "0x8E8E8E"
scroll_bar_grab_active_color = "0xCACACA"

[slider]
slider_grab_color = "0x707070"
slider_grab_active = "0x4B4B4B"

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
border_color = "0xE1E1E1"
border_shadow_color = "0x00000000"

[button]
button_color = "0x692A2A"
button_hovered_color = "0x853838"
button_active_color = "0x692A2A"

[drag_drop]
drag_drop_target_color = "0xffffff"

[nav_highlight]
nav_highlight_color = 0xffffff
nav_window_highlight_color = 0xffffff
)"sv;
        toml::table cfg;

        void write_cfg();
        void read_cfg();
};

#endif
