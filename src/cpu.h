#pragma once

#include <stdio.h>
#include <stdint.h>
#include <algorithm>
#include <iterator>

#include "register.h"
#include "instruction.h"
#include "map.h"

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

    uint8_t *memory_ptr;

public:
    CPU(uint8_t *memory_ptr, int m_size);
    ~CPU();

    uint16_t mem_load16(uint16_t offset);
    uint8_t mem_load8(uint8_t offset);


    void main_loop();
    void cycle();
    void load16(uint16_t addr);
    void load8(uint8_t addr);
};
