#include "id_generator.hxx"

int IdGenerator::GenerateId() {
        return ++g_idCounter_;
}

int IdGenerator::g_idCounter_ = 0;
