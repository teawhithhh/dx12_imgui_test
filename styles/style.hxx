#ifndef STYLES
#define STYLES
#include "imgui.h"

#define CONFIG(args) ImGui::ColorConvertU32ToFloat4(ImGui::Style::Color(static_cast<unsigned int>(std::stoi(cfg_ args.value_or("0xffffff"), nullptr, 16))))

namespace ImGui {
    namespace Style {

        // Load font from compressed ttf
        void LoadFont(float size = 16.0f);

        // Sets the ImGui style
        void SetupStyle();

        namespace { // Unnamed namespace, since we only use this here.
            unsigned int Color(unsigned int c) {
                // add alpha.
                // also swap red and blue channel for some reason.
                // todo: figure out why, and fix it.
                const short a = 0xFF;
                const short r = (c >> 16) & 0xFF;
                const short g = (c >> 8) & 0xFF;
                const short b = (c >> 0) & 0xFF;
                return(a << 24)
                    | (r << 0)
                    | (g << 8)
                    | (b << 16);
            }
        }
        // all colors are from http://spectrum.corp.adobe.com/color.html

        inline unsigned int color_alpha(unsigned int alpha, unsigned int c) {
            return ((alpha & 0xFF) << 24) | (c & 0x00FFFFFF);
        }
    }
}
#endif
