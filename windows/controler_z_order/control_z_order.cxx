#include "imgui.h"
#include "imgui_internal.h"
#include "controler_z_order/control_z_order.hxx"

namespace ImGui {
        void Begin( const char * name, WindowZOrder z_order, ImGuiWindowFlags flags ) {
                ImGui::Begin( name, NULL, flags );
                ImGui::GetCurrentWindow()->BeginOrderWithinContext = z_order;
        }
}
