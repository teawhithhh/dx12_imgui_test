#ifndef CONTROLER_Z_ORDER
#define CONTROLER_Z_ORDER
#include "imgui.h"

enum WindowZOrder {
        WindowZOrder_MainWindow,
        WindowZOrder_Logger,
        WindowZOrder_Decorator
};

namespace ImGui {
        void Begin( const char * name, WindowZOrder z_order, ImGuiWindowFlags flags );
}

#endif // CONTROLER_Z_ORDER
