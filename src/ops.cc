#include "cpu.h"

// All instructions
void CPU::op_nop() {
  // do nothing
  debug_instr = "NOP ";
}

// NOTE: LD rr, nn means load to rr the contents of nn
// NOTE: when accessing 16bit addresses, first is LO then HI
// meaning pc->instr => pc+1->lo => pc+2->hi

// mov 8bits from src_reg to dest_reg
void CPU::op_ld(uint8_t *src_reg, uint8_t *dest_reg) {
  debug_instr = "LD ";
  *dest_reg = *src_reg;
}

// mov 16bits from src_reg to dest_reg
void CPU::op_ld(Regcomb *src_reg, Regcomb *dest_reg) {
  debug_instr = "LD ";
  dest_reg->set(src_reg->get());
}

// mov 8bits from src_addr to dest_addr
void CPU::op_ld(uint16_t src_addr, uint16_t dest_addr) {
  debug_instr = "LD ";
  store8(dest_addr, load8(src_addr));
}

// load 8bits from addr in memory to dest_reg
void CPU::op_ld(uint16_t addr, uint8_t *dest_reg) {
  debug_instr = "LD ";
  *dest_reg = load8(addr);
}

// load 16bits from addr in memory to dest_reg
void CPU::op_ld(uint16_t addr, Regcomb *dest_reg) {
  debug_instr = "LD ";
  dest_reg->set(load16(addr));
}

// load 16bits from addr in memory to 16bit dest_reg (specifically SP)
void CPU::op_ld(uint16_t addr, uint16_t *dest_reg) {
  debug_instr = "LD ";
  *dest_reg = load16(addr);
}

// store 8bits from src_reg to addr in memory
void CPU::op_ld(uint8_t *src_reg, uint16_t addr) {
  debug_instr = "LD ";
  store8(addr, *src_reg);
}

// store 16bits from src_reg to addr in memory
void CPU::op_ld(Regcomb *src_reg, uint16_t addr) {
  debug_instr = "LD ";
  store16(addr, src_reg->get());
}

// store 16bits from src_reg (specifically SP) to addr in memory
void CPU::op_ld(uint16_t *src_reg, uint16_t addr) {
  debug_instr = "LD ";
  store16(addr, *src_reg);
}

void CPU::op_add(uint8_t *reg, uint8_t *val) {
  debug_instr = "ADD ";
  uint8_t res = *reg + *val;

  if (*reg == 0)
    flag->set_flag_zero(true);
  else
    flag->set_flag_zero(false);

  flag->set_flag_subtract(false);

  if ((*reg & 0xf) + (*val & 0xf) > 0xf)
    flag->set_flag_zero(true);
  else
    flag->set_flag_zero(false);

  if ((res & 0x100) != 0)
    flag->set_flag_zero(true);
  else
    flag->set_flag_zero(false);

  *reg = res;
}

void CPU::op_add(Regcomb *a, Regcomb *b) {
  debug_instr = "ADD ";
  uint8_t res = a->get() + b->get();

  if (a->get() == 0)
    flag->set_flag_zero(true);
  else
    flag->set_flag_zero(false);

  flag->set_flag_subtract(false);

  if ((a->get() & 0xf) + (b->get() & 0xf) > 0xf)
    flag->set_flag_zero(true);
  else
    flag->set_flag_zero(false);

  if ((res & 0x100) != 0)
    flag->set_flag_zero(true);
  else
    flag->set_flag_zero(false);

  a->set(res);
}

void CPU::op_add(Regcomb *a, uint16_t *b) {
  debug_instr = "ADD ";
  uint8_t res = a->get() + *b;

  if (a->get() == 0)
    flag->set_flag_zero(true);
  else
    flag->set_flag_zero(false);

  flag->set_flag_subtract(false);

  if ((a->get() & 0xf) + (*b & 0xf) > 0xf)
    flag->set_flag_zero(true);
  else
    flag->set_flag_zero(false);

  if ((res & 0x100) != 0)
    flag->set_flag_zero(true);
  else
    flag->set_flag_zero(false);

  a->set(res);
}

// used for adding to SP
void CPU::op_add(uint16_t *a, int8_t *b) {
  debug_instr = "ADD ";
  uint8_t res = *a + (int16_t)(*b);

  if (*a == 0)
    flag->set_flag_zero(true);
  else
    flag->set_flag_zero(false);

  flag->set_flag_subtract(false);

  if ((*a & 0xf) + (*b & 0xf) > 0xf)
    flag->set_flag_zero(true);
  else
    flag->set_flag_zero(false);

  if ((res & 0x100) != 0)
    flag->set_flag_zero(true);
  else
    flag->set_flag_zero(false);

  *a = res;
}

void CPU::op_inc(uint8_t *reg) {
  debug_instr = "INC ";
  *reg++;

  if (*reg == 0)
    flag->set_flag_zero(true);
  else
    flag->set_flag_zero(false);

  flag->set_flag_subtract(false);

  if ((*reg & 0x0f) == 0x00)
    flag->set_flag_half_carry(true);
  else
    flag->set_flag_half_carry(true);
}

void CPU::op_inc(uint16_t *reg) {
  debug_instr = "INC ";
  *reg++;

  if (*reg == 0)
    flag->set_flag_zero(true);
  else
    flag->set_flag_zero(false);

  flag->set_flag_subtract(false);

  if ((*reg & 0x0f) == 0x00)
    flag->set_flag_half_carry(true);
  else
    flag->set_flag_half_carry(true);
}

void CPU::op_inc(Regcomb *reg) {
  debug_instr = "INC ";
  reg->increment();

  if (reg->get() == 0)
    flag->set_flag_zero(true);
  else
    flag->set_flag_zero(false);

  flag->set_flag_subtract(false);

  if ((reg->get() & 0x0f) == 0x00)
    flag->set_flag_half_carry(true);
  else
    flag->set_flag_half_carry(true);
}

void CPU::op_inc(uint16_t addr) {
  debug_instr = "INC ";
  uint8_t val = load8(addr);
  val++;
  store8(addr, val);

  if (val == 0)
    flag->set_flag_zero(true);
  else
    flag->set_flag_zero(false);

  flag->set_flag_subtract(false);

  if ((val & 0x0f) == 0x00)
    flag->set_flag_half_carry(true);
  else
    flag->set_flag_half_carry(true);
}

void CPU::op_dec(uint8_t *reg) {
  debug_instr = "DEC ";
  *reg--;

  if (*reg == 0)
    flag->set_flag_zero(true);
  else
    flag->set_flag_zero(false);

  flag->set_flag_subtract(true);

  if ((*reg & 0x0f) == 0x0f) flag->set_flag_half_carry(true);
}

void CPU::op_dec(uint16_t *reg) {
  debug_instr = "DEC ";
  *reg--;

  if (*reg == 0)
    flag->set_flag_zero(true);
  else
    flag->set_flag_zero(false);

  flag->set_flag_subtract(true);

  if ((*reg & 0x0f) == 0x0f) flag->set_flag_half_carry(true);
}

void CPU::op_dec(Regcomb *reg) {
  debug_instr = "DEC ";
  reg->decrement();

  if (reg->get() == 0)
    flag->set_flag_zero(true);
  else
    flag->set_flag_zero(false);

  flag->set_flag_subtract(true);

  if ((reg->get() & 0x0f) == 0x0f) flag->set_flag_half_carry(true);
}

void CPU::op_dec(uint16_t addr) {
  debug_instr = "DEC ";
  uint8_t val = load8(addr);
  val--;
  store8(addr, val);

  if (val == 0)
    flag->set_flag_zero(true);
  else
    flag->set_flag_zero(false);

  flag->set_flag_subtract(true);

  if ((val & 0x0f) == 0x0f) flag->set_flag_half_carry(true);
}

void CPU::op_adc(uint8_t *val) {
  debug_instr = "ADC ";
  uint8_t carry = flag->flag_carry_val();
  uint full_res = a + *val + carry;
  uint8_t res = *val + carry;

  flag->set_flag_zero(res == 0);
  flag->set_flag_subtract(false);
  flag->set_flag_half_carry(((a & 0xf) + (*val & 0xf) + carry) > 0xf);
  flag->set_flag_carry(full_res > 0xff);

  a += res;
}

void CPU::op_sub(uint8_t *reg, uint8_t *val) {
  debug_instr = "SUB ";
  uint8_t res = *reg - *val;

  flag->set_flag_zero(*reg == 0);
  flag->set_flag_subtract(true);
  flag->set_flag_half_carry(((*reg & 0xf) - (*val & 0xf)) < 0);
  flag->set_flag_carry(*reg < *val);

  *reg = res;
}

void CPU::op_sbc(uint8_t *val) {
  debug_instr = "SBC ";
  uint8_t carry = flag->flag_carry_val();
  uint8_t res = *val - carry;
  int full_res = a - *val - carry;

  flag->set_flag_zero(res == 0);
  flag->set_flag_subtract(true);
  flag->set_flag_carry(full_res < 0);
  flag->set_flag_half_carry(((a & 0xf) - (*val & 0xf) - carry) < 0);

  a -= res;
}

void CPU::op_and(uint8_t *val) {
  debug_instr = "AND ";
  a &= *val;

  flag->set_flag_zero(a == 0);
  flag->set_flag_half_carry(true);
  flag->set_flag_carry(false);
  flag->set_flag_subtract(false);
}

void CPU::op_xor(uint8_t *val) {
  debug_instr = "XOR ";
  a ^= *val;
}

void CPU::op_or(uint8_t *val) {
  debug_instr = "OR ";
  a |= *val;
}

void CPU::op_cp(uint8_t *val) {
  debug_instr = "CP ";
  uint8_t res = a - *val;

  flag->set_flag_zero(res == 0);
  flag->set_flag_subtract(true);
  flag->set_flag_half_carry(((a & 0xf) - (*val & 0xf)) < 0);
  flag->set_flag_carry(a < *val);
}

void CPU::op_cpl() {
  debug_instr = "CPL";
  a = ~a;

  flag->set_flag_subtract(true);
  flag->set_flag_half_carry(true);
}

void CPU::op_jp(uint16_t addr) {
  debug_instr = "JP ";
  reg_pc = addr - 1;  // we subtract 1 because in cycle reg pc is incremented
                      // before moving to the next one
}

// Uncoditional jump to the absolute address specified by 16bit register
// (specifically HL)
void CPU::op_jp(Regcomb *reg) {
  debug_instr = "JP ";
  reg_pc = reg->get() - 1;  // we subtract 1 because in cycle reg pc is
                            // incremented before moving to the next one
}

// Conditional jump to 16bit addr depending on condition from reg
void CPU::op_jp(Condition cond, uint16_t addr) {
  debug_instr = "JP ";
  if (check_condition(cond)) {
    reg_pc = addr - 1;
  }
}

void CPU::op_jr(int8_t addr) {
  debug_instr = "JR ";
  reg_pc += addr - 1;
}

void CPU::op_jr(Condition cond, int8_t addr) {
  debug_instr = "JR ";
  if (check_condition(cond)) {
    reg_pc += addr - 1;
  }
}

void CPU::op_call(uint16_t addr) {
  debug_instr = "CALL";
  reg_sp--;
  mem_store8(reg_sp--, (uint8_t)(reg_pc & 0xff));
  mem_store8(reg_sp, (uint8_t)(reg_pc >> 8));
  reg_pc = addr - 1;
}

void CPU::op_call(Condition cond, uint16_t addr) {
  debug_instr = "CALL ";
  if (check_condition(cond)) {
    reg_sp--;
    mem_store8(reg_sp--, (uint8_t)(reg_pc & 0xff));
    mem_store8(reg_sp, (uint8_t)(reg_pc >> 8));
    reg_pc = addr - 1;
  }
}

void CPU::op_ret() {
  debug_instr = "RET ";
  uint8_t pc_hi = load8(reg_sp++);
  uint8_t pc_lo = load8(reg_sp++);
  reg_pc = (uint16_t)(pc_hi << 8) + (uint16_t)pc_lo;
  reg_pc--;  // pc-1 since we increment it at the end of cycle(), which we do
             // not want
}

void CPU::op_ret(Condition cond) {
  debug_instr = "RET ";
  if (check_condition(cond)) {
    uint8_t pc_hi = load8(reg_sp++);
    uint8_t pc_lo = load8(reg_sp++);
    reg_pc = (uint16_t)(pc_hi << 8) + (uint16_t)pc_lo;
    reg_pc--;  // pc-1 since we increment it at the end of cycle(), which we do
               // not want
  }
}

void CPU::op_reti() {
  debug_instr = "RETI ";
  uint8_t pc_hi = load8(reg_sp++);
  uint8_t pc_lo = load8(reg_sp++);
  reg_pc = (uint16_t)(pc_hi << 8) + (uint16_t)pc_lo;
  reg_pc--;  // pc-1 since we increment it at the end of cycle(), which we do
             // not want
  // IME = 1
}

void CPU::op_rst(uint8_t opcode) {
  debug_instr = "RST ";
  reg_sp--;
  mem_store8(reg_sp--, (uint8_t)(reg_pc & 0xff));
  mem_store8(reg_sp, (uint8_t)(reg_pc >> 8));
  reg_pc = rst_addr(opcode) - 1;
}

void CPU::op_rlc(uint8_t *reg) {
  debug_instr = "RLC ";
  uint8_t carry = *reg >> 7;
  // uint8_t carry = ((*reg & (1 << 7)) != 0);
  uint8_t res = (*reg << 1) | carry;
  *reg = res;

  flag->set_flag_carry(carry);
  flag->set_flag_zero(res == 0);
  flag->set_flag_half_carry(false);
  flag->set_flag_subtract(false);
}

void CPU::op_rlca() {
  debug_instr = "RLCA";
  op_rlc(&a);

  flag->set_flag_zero(false);
}

void CPU::op_rl(uint8_t *reg) {
  debug_instr = "RL ";
  uint8_t carry = *reg >> 7;
  uint8_t res = (*reg << 1) | carry;
  *reg = res;

  flag->set_flag_carry(carry);
  flag->set_flag_zero(res == 0);
  flag->set_flag_subtract(false);
  flag->set_flag_half_carry(false);
}

void CPU::op_rla() {
  debug_instr = "RLA";
  op_rl(&a);

  flag->set_flag_zero(false);
}

void CPU::op_rrc(uint8_t *reg) {
  debug_instr = "RRC ";
  uint8_t carry = *reg & 0x1;
  uint8_t res = (*reg >> 1) | (carry << 7);
  *reg = res;

  flag->set_flag_carry(carry);
  flag->set_flag_zero(res == 0);
  flag->set_flag_half_carry(false);
  flag->set_flag_subtract(false);
}

void CPU::op_rrca() {
  debug_instr = "RRCA";
  op_rrc(&a);

  flag->set_flag_zero(false);
}

void CPU::op_rr(uint8_t *reg) {
  debug_instr = "RR ";
  uint8_t carry = *reg & 0x1;
  uint8_t res = (*reg >> 1) | (carry << 7);
  *reg = res;

  flag->set_flag_carry(carry);
  flag->set_flag_zero(res == 0);
  flag->set_flag_subtract(false);
  flag->set_flag_half_carry(false);
}

void CPU::op_rra() {
  debug_instr = "RRA ";
  op_rr(&a);

  flag->set_flag_zero(false);
}

void CPU::op_daa() {
  debug_instr = "DAA ";
  uint8_t reg = a;
  uint16_t correction = flag->flag_carry() ? 0x60 : 0x00;

  if (flag->flag_half_carry() ||
      (!flag->flag_subtract() && ((reg & 0x0F) > 9))) {
    correction |= 0x06;
  }

  if (flag->flag_carry() || (!flag->flag_subtract() && (reg > 0x99))) {
    correction |= 0x60;
  }

  if (flag->flag_subtract()) {
    reg -= correction;
  } else {
    reg += correction;
  }

  if (((correction << 2) & 0x100) != 0) {
    flag->set_flag_carry(true);
  }

  flag->set_flag_half_carry(false);
  flag->set_flag_zero(reg == 0);

  a = reg;
}

void CPU::op_scf() {
  debug_instr = "SCF ";
  flag->set_flag_subtract(false);
  flag->set_flag_half_carry(false);
  flag->set_flag_carry(true);
}

void CPU::op_ccf() {
  debug_instr = "CCF ";
  flag->set_flag_subtract(false);
  flag->set_flag_half_carry(false);
  flag->set_flag_carry(~flag->flag_carry());
}

// TODO: implement these after adding timing/cycles
void CPU::op_stop() {
  debug_instr = "STOP ";
  // halted = true;
}

void CPU::op_halt() {
  debug_instr = "HALT ";
  halted = true;
}

void CPU::op_push(Regcomb *reg) {
  debug_instr = "PUSH ";
  reg_sp--;
  mem_store8(reg_sp--, reg->get_lo());
  mem_store8(reg_sp--, reg->get_hi());
}

void CPU::op_pop(Regcomb *reg) {
  debug_instr = "POP ";
  uint16_t val =
      (uint16_t)(mem_load8(reg_sp++) << 8) + (uint16_t)(mem_load8(reg_sp++));
  reg->set(val);
}

// TODO: implement prefixed opcodes
void CPU::op_prefix() {
  prefixed_op = true;
  uint8_t prefix_opcode = load8(++reg_pc);

  switch (prefix_opcode) {}
}
