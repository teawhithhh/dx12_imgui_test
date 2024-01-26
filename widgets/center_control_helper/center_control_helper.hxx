#ifndef CENTER_CONTROL
#define CENTER_CONTROL

#include "imgui.h"

class CenteredControlWrapper {
public:
    explicit CenteredControlWrapper(bool result);

    operator bool() const;
private:
    bool result_;
};

class ControlCenter {
public:
    ControlCenter(ImVec2 windowSize);

    template<typename Func>
    CenteredControlWrapper operator()(Func control) const;
private:
    ImVec2 windowSize_;
};

#include "center_control_helper_tp.cxx"

#define CENTERED_CONTROL(control) ControlCenter{ImGui::GetWindowSize()}([&]() { control; })

#endif // CENTER_CONTROL
