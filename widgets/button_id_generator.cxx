#include "button_id_generator.hxx"

int ButtonIdGenerator::GenerateId() {
        return ++g_buttonCounter_;
}

int ButtonIdGenerator::g_buttonCounter_ = 1;
