#include "center_control_helper.hxx"

CenteredControlWrapper::CenteredControlWrapper(bool result) : result_(result) {}

CenteredControlWrapper::operator bool() const {
    return result_;
}

ControlCenter::ControlCenter(ImVec2 windowSize) : windowSize_(windowSize) {}
