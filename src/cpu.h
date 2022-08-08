#pragma once

#include <stdio.h>
#include <stdint.h>
#include <algorithm>
#include <iterator>
#include <iostream>

#include "register.h"
#include "instruction.h"
#include "map.h"

class CPU{
private:
    // for debugging
    std::string debug_instr = "";

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
    void execute(uint8_t instr);
    void store(uint16_t addr, uint8_t data);
    uint8_t load(uint16_t addr);

    // all opcodes
    void op_00();
    void op_01();
    void op_02();
    void op_03();
    void op_04();
    void op_05();
    void op_06();
    void op_07();
    void op_08();
    void op_09();
    void op_0A();
    void op_0B();
    void op_0C();
    void op_0D();
    void op_0E();
    void op_0F();
    void op_10();
    void op_11();
    void op_12();
    void op_13();
    void op_14();
    void op_15();
    void op_16();
    void op_17();
    void op_18();
    void op_19();
    void op_1A();
    void op_1B();
    void op_1C();
    void op_1D();
    void op_1E();
    void op_1F();
    // TODO: add more opcodes
    void op_80();
    void op_81();
    void op_82();
    void op_83();
    void op_84();
    void op_85();
    void op_86();
    void op_87();
    void op_88();
    void op_89();
    void op_8A();
    void op_8B();
    void op_8C();
    void op_8D();
    void op_8E();
    void op_8F();
    // TODO: add more opcodes
    void op_F0();
    void op_F1();
    void op_F2();
    void op_F3();
    void op_F4();
    void op_F5();
    void op_F6();
    void op_F7();
    void op_F8();
    void op_F9();
    void op_FA();
    void op_FB();
    void op_FC();
    void op_FD();
    void op_FE();
    void op_FF();

    // all instructions
    void op_nop();
    void op_ld();
    void op_add(uint8_t *reg, uint8_t *val);
};
