#pragma once

#include <stdint.h>

class Instruction{
public:
    Instruction(uint8_t instr);
    void decode();
};
