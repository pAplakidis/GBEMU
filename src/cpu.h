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

    uint8_t flag;

    uint8_t *memory_ptr;

public:
    CPU(uint8_t *memory_ptr, int m_size);
    ~CPU();

    uint8_t mem_load(uint16_t offset);
    void mem_store(uint16_t offset, uint8_t data);

    void main_loop();
    void cycle();
    void store(uint16_t addr, uint8_t data);
    uint8_t load(uint16_t addr);
};
