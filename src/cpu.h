#pragma once

#include <stdio.h>
#include <stdint.h>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>

#include "register.h"
#include "instruction.h"
#include "map.h"
#include "utils.h"

#define MEMSIZE 1024*1024

class CPU{
private:
  // for debugging
  std::string debug_instr = "";
  std::string mem_dump = "";
  bool brk = false;
  std::ofstream memdump_file;

  // for branching
  enum class Condition {
      NZ,
      Z,
      NC,
      C,
  };

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

  FlagReg *flag;

  uint8_t *memory_ptr;

public:
  CPU(uint8_t *memory_ptr, int m_size);
  ~CPU();

  uint8_t mem_load8(uint16_t offset);
  uint16_t mem_load16(uint16_t offset);
  void mem_store8(uint16_t offset, uint8_t data);
  void mem_store16(uint16_t offset, uint16_t data);

  void main_loop();
  void cycle();
  void execute(uint8_t instr);
  void store8(uint16_t addr, uint8_t data);
  void store16(uint16_t addr, uint16_t data);
  uint8_t load8(uint16_t addr);
  uint16_t load16(uint16_t addr);

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
  void op_20();
  void op_21();
  void op_22();
  void op_23();
  void op_24();
  void op_25();
  void op_26();
  void op_27();
  void op_28();
  void op_29();
  void op_2A();
  void op_2B();
  void op_2C();
  void op_2D();
  void op_2E();
  void op_2F();
  void op_30();
  void op_31();
  void op_32();
  void op_33();
  void op_34();
  void op_35();
  void op_36();
  void op_37();
  void op_38();
  void op_39();
  void op_3A();
  void op_3B();
  void op_3C();
  void op_3D();
  void op_3E();
  void op_3F();
  void op_40();
  void op_41();
  void op_42();
  void op_43();
  void op_44();
  void op_45();
  void op_46();
  void op_47();
  void op_48();
  void op_49();
  void op_4A();
  void op_4B();
  void op_4C();
  void op_4D();
  void op_4E();
  void op_4F();
  void op_50();
  void op_51();
  void op_52();
  void op_53();
  void op_54();
  void op_55();
  void op_56();
  void op_57();
  void op_58();
  void op_59();
  void op_5A();
  void op_5B();
  void op_5C();
  void op_5D();
  void op_5E();
  void op_5F();
  void op_60();
  void op_61();
  void op_62();
  void op_63();
  void op_64();
  void op_65();
  void op_66();
  void op_67();
  void op_68();
  void op_69();
  void op_6A();
  void op_6B();
  void op_6C();
  void op_6D();
  void op_6E();
  void op_6F();
  void op_70();
  void op_71();
  void op_72();
  void op_73();
  void op_74();
  void op_75();
  void op_76();
  void op_77();
  void op_78();
  void op_79();
  void op_7A();
  void op_7B();
  void op_7C();
  void op_7D();
  void op_7E();
  void op_7F();
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
  // TODO: support more opcodes
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
  bool check_condition(Condition cond);
  void op_nop();
  void op_ld(uint8_t *src_reg, uint8_t *dest_reg);  // like mov
  void op_ld(Regcomb *src_reg, Regcomb *dest_reg);  // like mov
  void op_ld(uint16_t src_addr, uint16_t dest_addr);// mov from one addr to another
  void op_ld(uint16_t addr, uint8_t *dest_reg);     // load from addr
  void op_ld(uint16_t addr, Regcomb *dest_reg);     // load from addr
  void op_ld(uint16_t addr, uint16_t *dest_reg);    // load from addr
  void op_ld(uint8_t *src_reg, uint16_t addr);      // write to addr
  void op_ld(Regcomb *src_reg, uint16_t addr);      // write to addr
  void op_ld(uint16_t *src_reg, uint16_t addr);     // write to addr
  void op_add(uint8_t *reg, uint8_t *val);
  void op_add(Regcomb *a, Regcomb *b);
  void op_add(Regcomb *a, uint16_t *b);
  void op_inc(uint8_t *reg);
  void op_inc(uint16_t *reg);
  void op_inc(Regcomb *reg);
  void op_inc(uint16_t addr);
  void op_dec(uint8_t *reg);
  void op_dec(uint16_t *reg);
  void op_dec(Regcomb *reg);
  void op_dec(uint16_t addr);
  void op_adc(uint8_t *val);
  void op_sub(uint8_t *reg, uint8_t *val);
  void op_sbc(uint8_t *val);
  void op_and(uint8_t *val);
  void op_xor(uint8_t *val);
  void op_or(uint8_t *val);
  void op_cp(uint8_t *val);
  void op_cpl();
  void op_jp(uint16_t addr);
  void op_jp(Regcomb *reg);
  void op_jp(Condition cond, uint16_t addr);
  void op_jp(uint16_t *reg, uint16_t addr);
  void op_jr();
  void op_rlc(uint8_t *reg);
  void op_rlca();
  void op_rl(uint8_t *reg);
  void op_rla();
  void op_rrc(uint8_t *reg);
  void op_rrca();
  void op_rr(uint8_t *reg);
  void op_rra();
  void op_daa();
  void op_scf();
  void op_ccf();
  void op_stop();
  void op_halt();
};
