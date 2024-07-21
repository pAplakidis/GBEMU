#include "cpu.h"

// All opcodes
void CPU::op_00() { op_nop(); }

void CPU::op_01() {
  uint16_t addr_lo = (uint16_t)load8(++reg_pc);
  uint16_t addr_hi = (uint16_t)(load8(++reg_pc)) << 8;
  uint16_t addr = addr_hi + addr_lo;
  op_ld(addr, bc);
  debug_instr.append(string_format("BC, Imm16:0x%04x", addr));
}

void CPU::op_02() {
  uint16_t addr = bc->get();
  op_ld(&a, addr);
  debug_instr.append("(BC), A");
}

void CPU::op_03() {
  op_inc(bc);
  debug_instr.append("BC");
}

void CPU::op_04() {
  op_inc(&b);
  debug_instr.append("B");
}

void CPU::op_05() {
  op_dec(&b);
  debug_instr.append("B");
}

void CPU::op_06() {
  uint8_t addr = load8(++reg_pc);
  op_ld(addr, &b);
  debug_instr.append(string_format("B, Imm8:0x%02x", addr));
}

void CPU::op_07() {
  op_rlca();
  debug_instr.append("A");
}

void CPU::op_08() {
  uint16_t addr_lo = (uint16_t)load8(++reg_pc);
  uint16_t addr_hi = (uint16_t)(load8(++reg_pc)) << 8;
  uint16_t addr = addr_hi + addr_lo;
  op_ld(&reg_sp, addr);
  debug_instr.append(string_format("(Imm16:0x%04x), SP", addr));
}

void CPU::op_09() {
  op_add(hl, bc);
  debug_instr.append("HL, BC");
}

void CPU::op_0A() {
  uint16_t addr = bc->get();
  op_ld(addr, &a);
  debug_instr.append("A, (BC)");
}

void CPU::op_0B() {
  op_dec(bc);
  debug_instr.append("BC");
}

void CPU::op_0C() {
  op_inc(&c);
  debug_instr.append("C");
}

void CPU::op_0D() {
  op_dec(&c);
  debug_instr.append("C");
}

void CPU::op_0E() {
  uint8_t addr = load8(++reg_pc);
  op_ld(addr, &c);
  debug_instr.append(string_format("C, Imm8:0x%02x", addr));
}

void CPU::op_0F() {
  op_rrca();
  debug_instr.append("A");
}

void CPU::op_10() { op_stop(); }

void CPU::op_11() {
  uint16_t addr_lo = (uint16_t)load8(++reg_pc);
  uint16_t addr_hi = (uint16_t)(load8(++reg_pc)) << 8;
  uint16_t addr = addr_hi + addr_lo;
  op_ld(addr, de);
  debug_instr.append(string_format("DE, Imm16:0x%04x", addr));
}

void CPU::op_12() {
  uint16_t addr = de->get();
  op_ld(&a, addr);
  debug_instr.append("(DE), A");
}

void CPU::op_13() {
  op_inc(de);
  debug_instr.append("DE");
}

void CPU::op_14() {
  op_inc(&d);
  debug_instr.append("D");
}

void CPU::op_15() {
  op_dec(&d);
  debug_instr.append("D");
}

void CPU::op_16() {
  uint8_t addr = load8(++reg_pc);
  op_ld(addr, &d);
  debug_instr.append(string_format("D, Imm8:0x%02x", addr));
}

void CPU::op_17() {
  op_rla();
  debug_instr.append("A");
}

void CPU::op_18() {
  int16_t addr = load8(++reg_pc);
  op_jr(addr);
  debug_instr.append("Imm8:0x%02x", addr);
}

void CPU::op_19() {
  op_add(hl, de);
  debug_instr.append("HL, DE");
}

void CPU::op_1A() {
  uint16_t addr = de->get();
  op_ld(addr, &a);
  debug_instr.append("A, (DE)");
}

void CPU::op_1B() {
  op_dec(de);
  debug_instr.append("DE");
}

void CPU::op_1C() {
  op_inc(&e);
  debug_instr.append("E");
}

void CPU::op_1D() {
  op_dec(&e);
  debug_instr.append("E");
}

void CPU::op_1E() {
  uint8_t addr = load8(++reg_pc);
  op_ld(addr, &e);
  debug_instr.append(string_format("E, Imm8:0x%02x", addr));
}

void CPU::op_1F() {
  op_rra();
  debug_instr.append("A");
}

void CPU::op_20() {
  int16_t addr = load8(++reg_pc);
  op_jr(Condition::NZ, addr);
  debug_instr.append("NZ, Imm8:0x%02x", addr);
}

void CPU::op_21() {
  uint16_t addr_lo = (uint16_t)load8(++reg_pc);
  uint16_t addr_hi = (uint16_t)(load8(++reg_pc)) << 8;
  uint16_t addr = addr_hi + addr_lo;
  op_ld(addr, hl);
  debug_instr.append(string_format("HL, Imm16:0x%04x", addr));
}

void CPU::op_22() {
  uint16_t addr = (hl->get()) + 1;
  op_ld(&a, addr);
  debug_instr.append("(HL+), A");
}

void CPU::op_23() {
  op_inc(hl);
  debug_instr.append("HL");
}

void CPU::op_24() {
  op_inc(&h);
  debug_instr.append("H");
}

void CPU::op_25() {
  op_dec(&h);
  debug_instr.append("H");
}

void CPU::op_26() {
  uint8_t addr = load8(++reg_pc);
  op_ld(addr, &h);
  debug_instr.append(string_format("H, Imm8:0x%02x", addr));
}

void CPU::op_27() { op_daa(); }

void CPU::op_28() {
  int16_t addr = load8(++reg_pc);
  op_jr(Condition::Z, addr);
  debug_instr.append("Z, Imm8:0x%02x", addr);
}

void CPU::op_29() {
  op_add(hl, hl);
  debug_instr.append("HL, HL");
}

void CPU::op_2A() {
  uint16_t addr = (hl->get()) + 1;
  op_ld(addr, &a);
  debug_instr.append("A, (HL+)");
}

void CPU::op_2B() {
  op_dec(hl);
  debug_instr.append("hl");
}

void CPU::op_2C() {
  op_inc(&l);
  debug_instr.append("L");
}

void CPU::op_2D() {
  op_dec(&l);
  debug_instr.append("L");
}

void CPU::op_2E() {
  uint8_t addr = load8(++reg_pc);
  op_ld(addr, &l);
  debug_instr.append(string_format("L, Imm8:0x%02x", addr));
}

void CPU::op_2F() { op_cpl(); }

void CPU::op_30() {
  int16_t addr = load8(++reg_pc);
  op_jr(Condition::NC, addr);
  debug_instr.append("NC, Imm8:0x%02x", addr);
}

void CPU::op_31() {
  uint16_t addr_lo = (uint16_t)load8(++reg_pc);
  uint16_t addr_hi = (uint16_t)(load8(++reg_pc)) << 8;
  uint16_t addr = addr_hi + addr_lo;
  op_ld(addr, &reg_sp);
  debug_instr.append(string_format("SP, Imm16:0x%04x", addr));
}

void CPU::op_32() {
  uint16_t addr = (hl->get()) - 1;
  op_ld(&a, addr);
  debug_instr.append("(HL-), A");
}

void CPU::op_33() {
  op_inc(&reg_sp);
  debug_instr.append("SP");
}

void CPU::op_34() {
  op_inc(hl->get());
  debug_instr.append("(HL)");
}

void CPU::op_35() {
  op_dec(hl->get());
  debug_instr.append("(HL)");
}

void CPU::op_36() {
  uint8_t addr = load8(++reg_pc);
  op_ld(addr, hl->get());
  debug_instr.append(string_format("(HL), Imm8:0x%02x", addr));
}

void CPU::op_37() { op_scf(); }

void CPU::op_38() {
  int16_t addr = load8(++reg_pc);
  op_jr(Condition::C, addr);
  debug_instr.append("C, Imm8:0x%02x", addr);
}

void CPU::op_39() {
  op_add(hl, &reg_sp);
  debug_instr.append("HL, SP");
}

void CPU::op_3A() {
  uint16_t addr = (hl->get()) - 1;
  op_ld(addr, &a);
  debug_instr.append("A, (HL-)");
}

void CPU::op_3B() {
  op_dec(&reg_sp);
  debug_instr.append("SP");
}

void CPU::op_3C() {
  op_inc(&a);
  debug_instr.append("A");
}

void CPU::op_3D() {
  op_dec(&a);
  debug_instr.append("A");
}

void CPU::op_3E() {
  uint8_t addr = load8(++reg_pc);
  op_ld(addr, &a);
  debug_instr.append(string_format("A, Imm8:0x%02x", addr));
}

void CPU::op_3F() { op_ccf(); }

void CPU::op_40() {
  op_ld(&b, &b);
  debug_instr.append("B, B");
}

void CPU::op_41() {
  op_ld(&c, &b);
  debug_instr.append("B, C");
}

void CPU::op_42() {
  op_ld(&d, &b);
  debug_instr.append("B, D");
}

void CPU::op_43() {
  op_ld(&e, &b);
  debug_instr.append("B, E");
}

void CPU::op_44() {
  op_ld(&h, &b);
  debug_instr.append("B, H");
}

void CPU::op_45() {
  op_ld(&l, &b);
  debug_instr.append("B, L");
}

void CPU::op_46() {
  op_ld(hl->get(), &b);
  debug_instr.append("B, (HL)");
}

void CPU::op_47() {
  op_ld(&a, &b);
  debug_instr.append("B, A");
}

void CPU::op_48() {
  op_ld(&b, &c);
  debug_instr.append("C, B");
}

void CPU::op_49() {
  op_ld(&c, &c);
  debug_instr.append("C, C");
}

void CPU::op_4A() {
  op_ld(&d, &c);
  debug_instr.append("C, D");
}

void CPU::op_4B() {
  op_ld(&e, &c);
  debug_instr.append("C, E");
}

void CPU::op_4C() {
  op_ld(&h, &c);
  debug_instr.append("C, H");
}

void CPU::op_4D() {
  op_ld(&l, &c);
  debug_instr.append("C, L");
}

void CPU::op_4E() {
  op_ld(hl->get(), &c);
  debug_instr.append("C, (HL)");
}

void CPU::op_4F() {
  op_ld(&a, &c);
  debug_instr.append("C, A");
}

void CPU::op_50() {
  op_ld(&b, &d);
  debug_instr.append("D, B");
}

void CPU::op_51() {
  op_ld(&c, &d);
  debug_instr.append("D, C");
}

void CPU::op_52() {
  op_ld(&d, &d);
  debug_instr.append("D, D");
}

void CPU::op_53() {
  op_ld(&e, &d);
  debug_instr.append("D, E");
}

void CPU::op_54() {
  op_ld(&h, &d);
  debug_instr.append("D, H");
}

void CPU::op_55() {
  op_ld(&l, &d);
  debug_instr.append("D, L");
}

void CPU::op_56() {
  op_ld(hl->get(), &d);
  debug_instr.append("D, (HL)");
}

void CPU::op_57() {
  op_ld(&a, &d);
  debug_instr.append("D, A");
}

void CPU::op_58() {
  op_ld(&b, &e);
  debug_instr.append("E, B");
}

void CPU::op_59() {
  op_ld(&c, &e);
  debug_instr.append("E, C");
}

void CPU::op_5A() {
  op_ld(&d, &e);
  debug_instr.append("E, D");
}

void CPU::op_5B() {
  op_ld(&e, &e);
  debug_instr.append("E, E");
}

void CPU::op_5C() {
  op_ld(&h, &e);
  debug_instr.append("E, H");
}

void CPU::op_5D() {
  op_ld(&l, &e);
  debug_instr.append("E, L");
}

void CPU::op_5E() {
  op_ld(hl->get(), &e);
  debug_instr.append("E, (HL)");
}

void CPU::op_5F() {
  op_ld(&a, &e);
  debug_instr.append("E, A");
}

void CPU::op_60() {
  op_ld(&b, &h);
  debug_instr.append("H, B");
}

void CPU::op_61() {
  op_ld(&c, &h);
  debug_instr.append("H, C");
}

void CPU::op_62() {
  op_ld(&d, &h);
  debug_instr.append("H, D");
}

void CPU::op_63() {
  op_ld(&e, &h);
  debug_instr.append("H, E");
}

void CPU::op_64() {
  op_ld(&h, &h);
  debug_instr.append("H, H");
}

void CPU::op_65() {
  op_ld(&l, &h);
  debug_instr.append("H, L");
}

void CPU::op_66() {
  op_ld(hl->get(), &h);
  debug_instr.append("H, (HL)");
}

void CPU::op_67() {
  op_ld(&a, &h);
  debug_instr.append("H, A");
}

void CPU::op_68() {
  op_ld(&b, &l);
  debug_instr.append("L, B");
}

void CPU::op_69() {
  op_ld(&c, &l);
  debug_instr.append("L, C");
}

void CPU::op_6A() {
  op_ld(&d, &l);
  debug_instr.append("L, D");
}

void CPU::op_6B() {
  op_ld(&e, &l);
  debug_instr.append("L, E");
}

void CPU::op_6C() {
  op_ld(&h, &l);
  debug_instr.append("L, H");
}

void CPU::op_6D() {
  op_ld(&l, &l);
  debug_instr.append("L, L");
}

void CPU::op_6E() {
  op_ld(hl->get(), &l);
  debug_instr.append("L, (HL)");
}

void CPU::op_6F() {
  op_ld(&a, &l);
  debug_instr.append("L, A");
}

void CPU::op_70() {
  op_ld(&b, hl->get());
  debug_instr.append("(HL), B");
}

void CPU::op_71() {
  op_ld(&c, hl->get());
  debug_instr.append("(HL), C");
}

void CPU::op_72() {
  op_ld(&d, hl->get());
  debug_instr.append("(HL), D");
}

void CPU::op_73() {
  op_ld(&e, hl->get());
  debug_instr.append("(HL), E");
}

void CPU::op_74() {
  op_ld(&h, hl->get());
  debug_instr.append("(HL), H");
}

void CPU::op_75() {
  op_ld(&l, hl->get());
  debug_instr.append("(HL), L");
}

void CPU::op_76() { op_halt(); }

void CPU::op_77() {
  op_ld(&a, hl->get());
  debug_instr.append("(HL), A");
}

void CPU::op_78() {
  op_ld(&b, &a);
  debug_instr.append("A, B");
}

void CPU::op_79() {
  op_ld(&c, &a);
  debug_instr.append("A, C");
}

void CPU::op_7A() {
  op_ld(&d, &a);
  debug_instr.append("A, D");
}

void CPU::op_7B() {
  op_ld(&e, &a);
  debug_instr.append("A, E");
}

void CPU::op_7C() {
  op_ld(&h, &a);
  debug_instr.append("A, H");
}

void CPU::op_7D() {
  op_ld(&l, &a);
  debug_instr.append("A, L");
}

void CPU::op_7E() {
  op_ld(hl->get(), &a);
  debug_instr.append("A, (HL)");
}

void CPU::op_7F() {
  op_ld(&a, &a);
  debug_instr.append("A, A");
}

void CPU::op_80() {
  op_add(&a, &b);
  debug_instr.append("A, B");
}

void CPU::op_81() {
  op_add(&a, &c);
  debug_instr.append("A, C");
}

void CPU::op_82() {
  op_add(&a, &d);
  debug_instr.append("A, D");
}

void CPU::op_83() {
  op_add(&a, &e);
  debug_instr.append("A, E");
}

void CPU::op_84() {
  op_add(&a, &h);
  debug_instr.append("A, H");
}

void CPU::op_85() {
  op_add(&a, &l);
  debug_instr.append("A, L");
}

void CPU::op_86() {
  uint8_t val = load8(hl->get());
  op_add(&a, &val);
  debug_instr.append("A, (HL)");
}

void CPU::op_87() {
  op_add(&a, &a);
  debug_instr.append("A, A");
}

void CPU::op_88() {
  op_adc(&b);
  debug_instr.append("A, B");
}

void CPU::op_89() {
  op_adc(&c);
  debug_instr.append("A, C");
}

void CPU::op_8A() {
  op_adc(&d);
  debug_instr.append("A, D");
}

void CPU::op_8B() {
  op_adc(&e);
  debug_instr.append("A, E");
}

void CPU::op_8C() {
  op_adc(&h);
  debug_instr.append("A, H");
}

void CPU::op_8D() {
  op_adc(&l);
  debug_instr.append("A, L");
}

void CPU::op_8E() {
  uint8_t val = load8(hl->get());
  op_adc(&val);
  debug_instr.append("A, (HL)");
}

void CPU::op_8F() {
  op_adc(&a);
  debug_instr.append("A, A");
}

void CPU::op_90() {
  op_sub(&a, &b);
  debug_instr.append("A, B");
}

void CPU::op_91() {
  op_sub(&a, &c);
  debug_instr.append("A, C");
}

void CPU::op_92() {
  op_sub(&a, &d);
  debug_instr.append("A, D");
}

void CPU::op_93() {
  op_sub(&a, &e);
  debug_instr.append("A, E");
}

void CPU::op_94() {
  op_sub(&a, &h);
  debug_instr.append("A, H");
}

void CPU::op_95() {
  op_sub(&a, &l);
  debug_instr.append("A, L");
}

void CPU::op_96() {
  uint8_t val = load8(hl->get());
  op_sub(&a, &val);
  debug_instr.append("A, (HL)");
}

void CPU::op_97() {
  op_sub(&a, &a);
  debug_instr.append("A, A");
}

void CPU::op_98() {
  op_sbc(&b);
  debug_instr.append("A, B");
}

void CPU::op_99() {
  op_sbc(&c);
  debug_instr.append("A, C");
}

void CPU::op_9A() {
  op_sbc(&d);
  debug_instr.append("A, D");
}

void CPU::op_9B() {
  op_sbc(&e);
  debug_instr.append("A, E");
}

void CPU::op_9C() {
  op_sbc(&h);
  debug_instr.append("A, H");
}

void CPU::op_9D() {
  op_sbc(&l);
  debug_instr.append("A, L");
}

void CPU::op_9E() {
  uint8_t val = load8(hl->get());
  op_sbc(&val);
  debug_instr.append("A, (HL)");
}

void CPU::op_9F() {
  op_sbc(&a);
  debug_instr.append("A, A");
}

void CPU::op_A0() {
  op_and(&b);
  debug_instr.append("A, B");
}

void CPU::op_A1() {
  op_and(&c);
  debug_instr.append("A, C");
}

void CPU::op_A2() {
  op_and(&d);
  debug_instr.append("A, D");
}

void CPU::op_A3() {
  op_and(&e);
  debug_instr.append("A, E");
}

void CPU::op_A4() {
  op_and(&h);
  debug_instr.append("A, H");
}

void CPU::op_A5() {
  op_and(&l);
  debug_instr.append("A, L");
}

void CPU::op_A6() {
  uint8_t val = load8(hl->get());
  op_and(&val);
  debug_instr.append("A, (HL)");
}

void CPU::op_A7() {
  op_and(&a);
  debug_instr.append("A, A");
}

void CPU::op_A8() {
  op_xor(&b);
  debug_instr.append("A, B");
}

void CPU::op_A9() {
  op_xor(&c);
  debug_instr.append("A, C");
}

void CPU::op_AA() {
  op_xor(&d);
  debug_instr.append("A, D");
}

void CPU::op_AB() {
  op_xor(&e);
  debug_instr.append("A, E");
}

void CPU::op_AC() {
  op_xor(&h);
  debug_instr.append("A, H");
}

void CPU::op_AD() {
  op_xor(&l);
  debug_instr.append("A, L");
}

void CPU::op_AE() {
  op_xor(&e);
  debug_instr.append("A, (HL)");
}

void CPU::op_AF() {
  op_xor(&a);
  debug_instr.append("A, A");
}

void CPU::op_B0() {
  op_or(&b);
  debug_instr.append("A, B");
}

void CPU::op_B1() {
  op_or(&c);
  debug_instr.append("A, C");
}

void CPU::op_B2() {
  op_or(&d);
  debug_instr.append("A, D");
}

void CPU::op_B3() {
  op_or(&e);
  debug_instr.append("A, E");
}

void CPU::op_B4() {
  op_or(&h);
  debug_instr.append("A, H");
}

void CPU::op_B5() {
  op_or(&l);
  debug_instr.append("A, L");
}

void CPU::op_B6() {
  op_or(&e);
  debug_instr.append("A, (HL)");
}

void CPU::op_B7() {
  op_or(&l);
  debug_instr.append("A, A");
}

void CPU::op_B8() {
  op_cp(&b);
  debug_instr.append("A, B");
}

void CPU::op_B9() {
  op_cp(&c);
  debug_instr.append("A, C");
}

void CPU::op_BA() {
  op_cp(&d);
  debug_instr.append("A, D");
}

void CPU::op_BB() {
  op_cp(&e);
  debug_instr.append("A, E");
}

void CPU::op_BC() {
  op_cp(&h);
  debug_instr.append("A, H");
}

void CPU::op_BD() {
  op_cp(&l);
  debug_instr.append("A, L");
}

void CPU::op_BE() {
  op_cp(&e);
  debug_instr.append("A, (HL)");
}

void CPU::op_BF() {
  op_cp(&a);
  debug_instr.append("A, A");
}

void CPU::op_C0() {
  op_ret(Condition::NZ);
  debug_instr.append("NZ");
}

void CPU::op_C1() {
  op_pop(bc);
  debug_instr.append("BC");
}

void CPU::op_C2() {
  uint8_t addr_lo = load8(++reg_pc);
  uint8_t addr_hi = load8(++reg_pc);
  uint16_t addr = (uint16_t)(addr_hi << 8) + (uint16_t)addr_lo;
  op_jp(Condition::NZ, addr);
  debug_instr.append(string_format("NZ, Imm16:0x%04x", addr));
}

void CPU::op_C3() {
  uint8_t addr_lo = load8(++reg_pc);
  uint8_t addr_hi = load8(++reg_pc);
  uint16_t addr = (uint16_t)(addr_hi << 8) + (uint16_t)addr_lo;
  op_jp(addr);
  debug_instr.append(string_format("Imm16:0x%04x", addr));
}

void CPU::op_C4() {
  uint8_t addr_lo = load8(++reg_pc);
  uint8_t addr_hi = load8(++reg_pc);
  uint16_t addr = (uint16_t)(addr_hi << 8) + (uint16_t)addr_lo;
  op_jp(Condition::NZ, addr);
  debug_instr.append(string_format("NZ, Imm16:0x%04x", addr));
}

void CPU::op_C5() {
  op_push(bc);
  debug_instr.append("BC");
}

void CPU::op_C6() {
  uint8_t imm = load8(++reg_pc);
  op_add(&a, &imm);
  debug_instr.append(string_format("A, Imm8:0x%02x", imm));
}

void CPU::op_C7() {
  op_rst(0xc7);
  debug_instr.append("00h");
}

void CPU::op_C8() {
  op_ret(Condition::Z);
  debug_instr.append("Z");
}

void CPU::op_C9() { op_ret(); }

void CPU::op_CA() {
  uint8_t addr_lo = load8(++reg_pc);
  uint8_t addr_hi = load8(++reg_pc);
  uint16_t addr = (uint16_t)(addr_hi << 8) + (uint16_t)addr_lo;
  op_jp(Condition::Z, addr);
  debug_instr.append(string_format("Z, Imm16:0x%04x", addr));
}

void CPU::op_CB() { op_prefix(); }

void CPU::op_CC() {
  uint8_t addr_lo = load8(++reg_pc);
  uint8_t addr_hi = load8(++reg_pc);
  uint16_t addr = (uint16_t)(addr_hi << 8) + (uint16_t)addr_lo;
  op_jp(Condition::Z, addr);
  debug_instr.append(string_format("Z, Imm16:0x%04x", addr));
}

void CPU::op_CD() {
  uint8_t addr_lo = load8(++reg_pc);
  uint8_t addr_hi = load8(++reg_pc);
  uint16_t addr = (uint16_t)(addr_hi << 8) + (uint16_t)addr_lo;
  op_call(addr);
  debug_instr.append(string_format("Imm16:0x%04x", addr));
}

void CPU::op_CE() {
  uint8_t imm = load8(++reg_pc);
  op_adc(&imm);
  debug_instr.append(string_format("A, Imm8:0x%02x", imm));
}

void CPU::op_CF() {
  op_rst(0xcf);
  debug_instr.append("08h");
}

void CPU::op_D0() {
  op_ret(Condition::NC);
  debug_instr.append("NC");
}

void CPU::op_D1() {
  op_pop(de);
  debug_instr.append("DE");
}

void CPU::op_D2() {
  uint8_t addr_lo = load8(++reg_pc);
  uint8_t addr_hi = load8(++reg_pc);
  uint16_t addr = (uint16_t)(addr_hi << 8) + (uint16_t)addr_lo;
  op_jp(Condition::NC, addr);
  debug_instr.append(string_format("NC, Imm16:0x%04x", addr));
}

void CPU::op_D3() {}

void CPU::op_D4() {
  uint8_t addr_lo = load8(++reg_pc);
  uint8_t addr_hi = load8(++reg_pc);
  uint16_t addr = (uint16_t)(addr_hi << 8) + (uint16_t)addr_lo;
  op_jp(Condition::NC, addr);
  debug_instr.append(string_format("NC, Imm16:0x%04x", addr));
}

void CPU::op_D5() {
  op_push(de);
  debug_instr.append("DE");
}

void CPU::op_D6() {
  uint8_t imm = load8(++reg_pc);
  op_sub(&a, &imm);
  debug_instr.append(string_format("A, Imm8:0x%02x", imm));
}

void CPU::op_D7() {
  op_rst(0xd7);
  debug_instr.append("10h");
}

void CPU::op_D8() {
  op_ret(Condition::C);
  debug_instr.append("C");
}

void CPU::op_D9() { op_reti(); }

void CPU::op_DA() {
  uint8_t addr_lo = load8(++reg_pc);
  uint8_t addr_hi = load8(++reg_pc);
  uint16_t addr = (uint16_t)(addr_hi << 8) + (uint16_t)addr_lo;
  op_jp(Condition::C, addr);
  debug_instr.append(string_format("C, Imm16:0x%04x", addr));
}

void CPU::op_DB() {}

void CPU::op_DC() {
  uint8_t addr_lo = load8(++reg_pc);
  uint8_t addr_hi = load8(++reg_pc);
  uint16_t addr = (uint16_t)(addr_hi << 8) + (uint16_t)addr_lo;
  op_jp(Condition::C, addr);
  debug_instr.append(string_format("C, Imm16:0x%04x", addr));
}

void CPU::op_DD() {}

void CPU::op_DE() {
  uint8_t imm = load8(++reg_pc);
  op_sbc(&imm);
  debug_instr.append(string_format("A, Imm8:0x%02x", imm));
}

void CPU::op_DF() {
  op_rst(0xdf);
  debug_instr.append("18h");
}

void CPU::op_E0() {
  uint16_t addr = 0xff00 + (uint16_t)load8(++reg_pc);
  op_ld(&a, addr);
  debug_instr.append(string_format("(0xFF00+Imm8:0x%02x), A", addr));
}

void CPU::op_E1() {
  op_pop(hl);
  debug_instr.append("HL");
}

void CPU::op_E2() {
  uint16_t addr = 0xff00 + (uint16_t)c;
  op_ld(&a, addr);
  debug_instr.append(string_format("(0xFF00+C:0x%02x), A", addr));
}

void CPU::op_E3() {}

void CPU::op_E4() {}

void CPU::op_E5() {
  op_push(hl);
  debug_instr.append("HL");
}

void CPU::op_E6() {
  uint8_t addr = load8(++reg_pc);
  op_and(&addr);
  debug_instr.append(string_format("A, Imm8:0x%02x", addr));
}

void CPU::op_E7() {
  op_rst(0xe7);
  debug_instr.append("20h");
}

void CPU::op_E8() {
  int8_t val = (int8_t)load8(++reg_pc);
  op_add(&reg_sp, &val);
  debug_instr.append(string_format("SP, Imm8:0x%02x", val));
}

void CPU::op_E9() {
  op_jp(hl);
  debug_instr.append("HL");
}

void CPU::op_EA() {
  uint8_t addr_lo = load8(++reg_pc);
  uint8_t addr_hi = load8(++reg_pc);
  uint16_t addr = (uint16_t)(addr_hi << 8) + (uint16_t)addr_lo;
  op_ld(&a, addr);
  debug_instr.append(string_format("(Imm16:0x%04x), A", addr));
}

void CPU::op_EB() {}

void CPU::op_EC() {}

void CPU::op_ED() {}

void CPU::op_EE() {
  uint8_t val = load8(++reg_pc);
  op_xor(&val);
  debug_instr.append(string_format("A, Imm8:0x%02x", val));
}

void CPU::op_EF() {
  op_rst(0xef);
  debug_instr.append("28h");
}

void CPU::op_F0() {
  uint16_t addr = 0xff00 + (uint16_t)load8(++reg_pc);
  op_ld(addr, &a);
  debug_instr.append(string_format("A, (0xFF00+Imm8:0x%02x)", addr));
}

void CPU::op_F1() {
  op_pop(af);
  debug_instr.append("AF");
}

void CPU::op_F2() {
  uint16_t addr = 0xff00 + (uint16_t)c;
  op_ld(addr, &a);
  debug_instr.append(string_format("A, (0xFF00+C:0x%02x)", addr));
}

void CPU::op_F3() {
  // op_di();
}

void CPU::op_F4() {}

void CPU::op_F5() {
  op_push(af);
  debug_instr.append("AF");
}

void CPU::op_F6() {
  uint8_t val = load8(++reg_pc);
  op_or(&val);
  debug_instr.append(string_format("A, Imm8:0x%02x", val));
}

void CPU::op_F7() {
  op_rst(0xf7);
  debug_instr.append("30h");
}

void CPU::op_F8() {
  int8_t val = (int8_t)load8(++reg_pc);
  // op_ld(reg_sp+val, hl);
  hl->set(reg_sp + val);
  debug_instr.append(string_format("LD HL, SP+Imm8:0x%02x", val));
}

void CPU::op_F9() {
  reg_sp = hl->get();
  debug_instr.append("LD SP, HL");
}

void CPU::op_FA() {
  uint16_t addr_lo = (uint16_t)load8(++reg_pc);
  uint16_t addr_hi = (uint16_t)(load8(++reg_pc)) << 8;
  uint16_t addr = addr_hi + addr_lo;
  op_ld(addr, &a);
  debug_instr.append(string_format("A, (Imm16):0x%04x", addr));
}

void CPU::op_FB() {
  // op_ei();
}

void CPU::op_FC() {}

void CPU::op_FD() {}

void CPU::op_FE() {
  uint8_t val = load8(++reg_pc);
  op_cp(&val);
  debug_instr.append(string_format("A, Imm8:0x%02x", val));
}

void CPU::op_FF() {
  op_rst(0xff);
  debug_instr.append("38h");
}
