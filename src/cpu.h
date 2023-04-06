#pragma once

#include <stdio.h>
#include <stdint.h>
#include <algorithm>
#include <iterator>
#include <iostream>

#include "register.h"
#include "instruction.h"
#include "map.h"

#define MEMSIZE 1024*1024

class CPU{
private:
    // for debugging
    std::string debug_instr = "";
    bool brk = false;

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
    void store8(uint16_t addr, uint8_t data);
    void store16(uint16_t addr, uint16_t data);
    uint8_t load8(uint16_t addr);
    uint8_t load16(uint16_t addr);

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
    void op_90();
    void op_91();
    void op_92();
    void op_93();
    void op_94();
    void op_95();
    void op_96();
    void op_97();
    void op_98();
    void op_99();
    void op_9A();
    void op_9B();
    void op_9C();
    void op_9D();
    void op_9E();
    void op_9F();
    void op_A0();
    void op_A1();
    void op_A2();
    void op_A3();
    void op_A4();
    void op_A5();
    void op_A6();
    void op_A7();
    void op_A8();
    void op_A9();
    void op_AA();
    void op_AB();
    void op_AC();
    void op_AD();
    void op_AE();
    void op_AF();
    void op_B0();
    void op_B1();
    void op_B2();
    void op_B3();
    void op_B4();
    void op_B5();
    void op_B6();
    void op_B7();
    void op_B8();
    void op_B9();
    void op_BA();
    void op_BB();
    void op_BC();
    void op_BD();
    void op_BE();
    void op_BF();
    void op_C0();
    void op_C1();
    void op_C2();
    void op_C3();
    void op_C4();
    void op_C5();
    void op_C6();
    void op_C7();
    void op_C8();
    void op_C9();
    void op_CA();
    void op_CB();
    void op_CC();
    void op_CD();
    void op_CE();
    void op_CF();
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
    // TODO: LD A, (B) is READ, LD (A), B is WRITE
    void op_ld(uint8_t *src_reg, uint8_t *dest_reg);    // like mov
    void op_ld(Regcomb *src_reg, Regcomb *dest_reg);    // like mov
    void op_ld(uint16_t addr, uint8_t *dest_reg);      // load from addr
    void op_ld(uint16_t addr, Regcomb *dest_reg);      // load from addr
    void op_ld(uint8_t *src_reg, uint16_t addr);       // write to addr
    void op_ld(Regcomb *src_reg, uint16_t addr);       // write to addr
    void op_add(uint8_t *reg, uint8_t *val);
    void op_add(Regcomb *a, Regcomb *b);
    void op_inc(uint8_t *reg);
    void op_inc(Regcomb *reg);
    void op_dec(uint8_t *reg);
    void op_dec(Regcomb *reg);
    void op_adc(uint8_t *val);
    void op_sub(uint8_t *reg, uint8_t *val);
    void op_sbc(uint8_t *val);
    void op_and(uint8_t *val);
    void op_xor(uint8_t *val);
    void op_or(uint8_t *val);
    void op_cp(uint8_t *val);
    void op_jp(uint8_t addr);
    void op_jr();
    void op_rlc(uint8_t *reg);
    void op_rlca();
    void op_rl(uint8_t *reg);
    void op_rla();
    void op_rrc(uint8_t *reg);
    void op_rrca();
    void op_rr(uint8_t *reg);
    void op_rra();
    void op_stop();
};
