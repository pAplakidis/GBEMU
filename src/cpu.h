#pragma once

#include <stdio.h>
#include <stdint.h>

#include "register.h"
#include "instruction.h"

class CPU{
private:
    // registers (real)
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t f;
    uint8_t e;
    uint8_t h;
    uint8_t l;

    uint16_t reg_pc;
    uint16_t reg_sp;

    // combinations (virtual registers)
    Regcomb *af;
    Regcomb *bc;
    Regcomb *de;
    Regcomb *hl;

public:
    CPU();
    ~CPU();

    void main_loop();
    void cycle();
};
