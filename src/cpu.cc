#include "cpu.h"

CPU::CPU(uint8_t *memory_ptr, int m_size){
    a, b, c, d, e, f, h, l = 0x00;
    af = new Regcomb(a, f);
    bc = new Regcomb(b, c);
    de = new Regcomb(d, e);
    hl = new Regcomb(h, l);

    reg_pc = 0x00;
    reg_sp = 0x00;

    flag = 0x00;

    this->memory_ptr = memory_ptr;

    memdump_file.open("mem_dump.log");
}

CPU::~CPU(){

}

void CPU::main_loop(){
    while(1){
        cycle();

        //break;  // TODO: temporary for debugging
    }
}

// TODO: some commands have variable number of cycles (handle timing)
void CPU::cycle(){
    debug_instr = "";
    mem_dump = "";

    printf("0x%04x:\t", reg_pc);
    uint8_t instr = load8(reg_pc);
    printf("0x%02x =>\t", instr);

    execute(instr);
    std::cout << debug_instr << std::endl;

    reg_pc++;
    
    // max PC value
    if(reg_pc >= 0xffff){
        exit(0);
    }

    // TODO: move to a debugger class
    // for debugging
    if(brk == true){
        // TODO: print flags and stack values as well
        printf("\nBREAKPOINT\n");
        printf("Info Registers\n");
        printf("A: 0x%02x\n", a);
        printf("B: 0x%02x\n", b);
        printf("C: 0x%02x\n", c);
        printf("D: 0x%02x\n", d);
        printf("E: 0x%02x\n", e);
        printf("F: 0x%02x\n", f);
        printf("H: 0x%02x\n", h);
        printf("L: 0x%02x\n", l);
        printf("PC: 0x%04x\n", reg_pc);
        printf("SP: 0x%04x\n", reg_sp);

        printf("AF: 0x%04x\n", af->get());
        printf("BC: 0x%04x\n", bc->get());
        printf("DE: 0x%04x\n", de->get());
        printf("HL: 0x%04x\n", hl->get());

        for(int i=0; i <= MEMSIZE - 16; i += 16){
            mem_dump.append(string_format("0x%05x:\t", i));
            for(int j=i; j < i+16; j++){
                mem_dump.append(string_format("0x%02x ", memory_ptr[j]));
            }
            mem_dump.append("\n");
        }
        memdump_file << mem_dump;
        memdump_file.close();
        printf("\nMemory Dumped at mem_dump.log\n");
        exit(0);
    }
}

void CPU::execute(uint8_t instr){
    switch(instr){
        case 0x00:
            op_00();
            break;
        case 0x01:
            op_01();
            break;
        case 0x02:
            op_02();
            break;
        case 0x03:
            op_03();
            break;
        case 0x04:
            op_04();
            break;
        case 0x05:
            op_05();
            break;
        case 0x06:
            op_06();
            break;
        case 0x07:
            op_07();
            break;
        case 0x08:
            op_08();
            break;
        case 0x09:
            op_09();
            break;
        case 0x0A:
            op_0A();
            break;
        case 0x0B:
            op_0B();
            break;
        case 0x0C:
            op_0C();
            break;
        case 0x0D:
            op_0D();
            break;
        case 0x0E:
            op_0E();
            break;
        case 0x0F:
            op_0F();
            break;
        case 0x10:
            op_10();
            break;
        case 0x11:
            op_11();
            break;
        case 0x12:
            op_12();
            break;
        case 0x13:
            op_13();
            break;
        case 0x14:
            op_14();
            break;
        case 0x15:
            op_15();
            break;
        case 0x16:
            op_16();
            break;
        case 0x17:
            op_17();
            break;
        case 0x18:
            op_18();
            break;
        case 0x19:
            op_19();
            break;
        case 0x1A:
            op_1A();
            break;
        case 0x1B:
            op_1B();
            break;
        case 0x1C:
            op_1C();
            break;
        case 0x1D:
            op_1D();
            break;
        case 0x1E:
            op_1E();
            break;
        case 0x1F:
            op_1F();
            break;
        case 0x20:
            op_20();
            break;
        case 0x21:
            op_21();
            break;
        case 0x22:
            op_22();
            break;
        case 0x23:
            op_23();
            break;
        case 0x24:
            op_24();
            break;
        case 0x25:
            op_25();
            break;
        case 0x26:
            op_26();
            break;
        case 0x27:
            op_27();
            break;
        case 0x28:
            op_28();
            break;
        case 0x29:
            op_29();
            break;
        case 0x2A:
            op_2A();
            break;
        case 0x2B:
            op_2B();
            break;
        case 0x2C:
            op_1C();
            break;
        case 0x2D:
            op_2D();
            break;
        case 0x2E:
            op_2E();
            break;
        case 0x30:
            op_30();
            break;
        case 0x31:
            op_31();
            break;
        case 0x32:
            op_32();
            break;
        case 0x33:
            op_33();
            break;
        case 0x34:
            op_34();
            break;
        case 0x35:
            op_35();
            break;
        case 0x36:
            op_36();
            break;
        case 0x37:
            op_37();
            break;
        case 0x38:
            op_38();
            break;
        case 0x39:
            op_39();
            break;
        case 0x3A:
            op_3A();
            break;
        case 0x3B:
            op_3B();
            break;
        case 0x3C:
            op_3C();
            break;
        case 0x3D:
            op_3D();
            break;
        case 0x3E:
            op_3E();
            break;
        case 0x3F:
            op_3F();
            break;
        case 0x80:
            op_80();
            break;
        case 0x81:
            op_81();
            break;
        case 0x82:
            op_82();
            break;
        case 0x83:
            op_83();
            break;
        case 0x84:
            op_84();
            break;
        case 0x85:
            op_85();
            break;
        case 0x86:
            op_86();
            break;
        case 0x87:
            op_87();
            break;
        case 0x88:
            op_88();
            break;
        case 0x89:
            op_89();
            break;
        case 0x8A:
            op_8A();
            break;
        case 0x8B:
            op_8B();
            break;
        case 0x8C:
            op_8C();
            break;
        case 0x8D:
            op_8D();
            break;
        case 0x8E:
            op_8E();
            break;
        case 0x8F:
            op_8F();
            break;
        case 0x90:
            op_90();
            break;
        case 0x91:
            op_91();
            break;
        case 0x92:
            op_92();
            break;
        case 0x93:
            op_93();
            break;
        case 0x94:
            op_94();
            break;
        case 0x95:
            op_95();
            break;
        case 0x96:
            op_96();
            break;
        case 0x97:
            op_97();
            break;
        case 0x98:
            op_98();
            break;
        case 0x99:
            op_99();
            break;
        case 0x9A:
            op_9A();
            break;
        case 0x9B:
            op_9B();
            break;
        case 0x9C:
            op_9C();
            break;
        case 0x9D:
            op_9D();
            break;
        case 0x9E:
            op_9E();
            break;
        case 0x9F:
            op_9F();
            break;
        case 0xA0:
            op_A0();
            break;
        case 0xA1:
            op_A1();
            break;
        case 0xA2:
            op_A2();
            break;
        case 0xA3:
            op_A3();
            break;
        case 0xA4:
            op_A4();
            break;
        case 0xA5:
            op_A5();
            break;
        case 0xA6:
            op_A6();
            break;
        case 0xA7:
            op_A7();
            break;
        case 0xA8:
            op_A8();
            break;
        case 0xA9:
            op_A9();
            break;
        case 0xAA:
            op_AA();
            break;
        case 0xAB:
            op_AB();
            break;
        case 0xAC:
            op_AC();
            break;
        case 0xAD:
            op_AD();
            break;
        case 0xAE:
            op_AE();
            break;
        case 0xAF:
            op_AF();
            break;
        case 0xB0:
            op_B0();
            break;
        case 0xB1:
            op_B1();
            break;
        case 0xB2:
            op_B2();
            break;
        case 0xB3:
            op_B3();
            break;
        case 0xB4:
            op_B4();
            break;
        case 0xB5:
            op_B5();
            break;
        case 0xB6:
            op_B6();
            break;
        case 0xB7:
            op_B7();
            break;
        case 0xB8:
            op_B8();
            break;
        case 0xB9:
            op_B9();
            break;
        case 0xBA:
            op_BA();
            break;
        case 0xBB:
            op_BB();
            break;
        case 0xBC:
            op_BC();
            break;
        case 0xBD:
            op_BD();
            break;
        case 0xBE:
            op_BE();
            break;
        case 0xBF:
            op_BF();
            break;
        case 0xC0:
            op_C0();
            break;
        case 0xC1:
            op_C1();
            break;
        case 0xC2:
            op_C2();
            break;
        case 0xC3:
            op_C3();
            break;
        case 0xC4:
            op_C4();
            break;
        case 0xC5:
            op_C5();
            break;
        case 0xC6:
            op_C6();
            break;
        case 0xC7:
            op_C7();
            break;
        case 0xC8:
            op_C8();
            break;
        case 0xC9:
            op_C9();
            break;
        case 0xCA:
            op_CA();
            break;
        case 0xCB:
            op_CB();
            break;
        case 0xCC:
            op_CC();
            break;
        case 0xCD:
            op_CD();
            break;
        case 0xCE:
            op_CE();
            break;
        case 0xCF:
            op_CF();
            break;
        default:
            printf("Opcode not supported\n");
            break;
    }
}

uint8_t CPU::mem_load8(uint16_t offset){
    size_t off = (size_t)offset;
    if(offset < 8*1024)
        return memory_ptr[off];

    return 0x00;
}

uint16_t CPU::mem_load16(uint16_t offset){
    size_t off = (size_t)offset;
    if(offset < 8*1024)
        return memory_ptr[off] + (memory_ptr[off+1] << 8);

    return 0x0000;
}

void CPU::mem_store8(uint16_t offset, uint8_t data){
    size_t off = (size_t)offset;
    if(offset < 8*1024)
        memory_ptr[off] = data;
}

void CPU::mem_store16(uint16_t offset, uint16_t data){
    size_t off = (size_t)offset;
    if(offset < 8*1024){
        memory_ptr[off] = (uint8_t) (data & 0xf0);
        memory_ptr[off+1] = (uint8_t) (data >> 8);
    }
}

void CPU::store8(uint16_t addr, uint8_t data){
    // TODO: check if addr is aligned

    // TODO: we are currently using just one big junk of memory, but later it needs to utilize the memory map
    //if(uint16_t *offset = map::ROM_bank0->contains(addr)){
    //
    //}
    // TODO: this is temporary since memory map is not finished

    mem_store8(addr, data);
}

void CPU::store16(uint16_t addr, uint16_t data){
    // TODO: check if addr is aligned

    // TODO: we are currently using just one big junk of memory, but later it needs to utilize the memory map
    //if(uint16_t *offset = map::ROM_bank0->contains(addr)){
    //
    //}
    // TODO: this is temporary since memory map is not finished

    mem_store16(addr, data);
}

uint8_t CPU::load8(uint16_t addr){

    // TODO: check if addr is aligned

    // TODO: we are currently using just one big junk of memory, but later it needs to utilize the memory map
    //if(uint16_t *offset = map::ROM_bank0->contains(addr)){
    //
    //}

    return mem_load8(addr);
}

uint16_t CPU::load16(uint16_t addr){

    // TODO: check if addr is aligned

    // TODO: we are currently using just one big junk of memory, but later it needs to utilize the memory map
    //if(uint16_t *offset = map::ROM_bank0->contains(addr)){
    //
    //}

    return mem_load16(addr);
}

// All opcodes
void CPU::op_00(){
    op_nop();
}

void CPU::op_01(){
  uint16_t addr_lo = (uint16_t)load8(++reg_pc);
  uint16_t addr_hi = (uint16_t)(load8(++reg_pc)) << 8;
  uint16_t addr = addr_hi + addr_lo;
  op_ld(addr, bc);
  debug_instr.append(string_format("BC, Imm16:0x%04x", addr));
}

void CPU::op_02(){
  uint16_t addr = bc->get();
  op_ld(&a, addr);
  debug_instr.append("(BC), A");
}

void CPU::op_03(){
  op_inc(bc);
  debug_instr.append("BC");
}

void CPU::op_04(){
  op_inc(&b);
  debug_instr.append("B");
}

void CPU::op_05(){
  op_dec(&b);
  debug_instr.append("B");
}

void CPU::op_06(){
  uint8_t addr = load8(++reg_pc);
  op_ld(addr, &b);
  debug_instr.append(string_format("B, Imm8:0x%02x", addr));
}

void CPU::op_07(){
  op_rlca();
  debug_instr.append("A");
}

// TODO: double check this
void CPU::op_08(){
  uint16_t addr_lo = (uint16_t)load8(++reg_pc);
  uint16_t addr_hi = (uint16_t)(load8(++reg_pc)) << 8;
  uint16_t addr = addr_hi + addr_lo;
  op_ld(&reg_sp, addr);
  debug_instr.append(string_format("(Imm16:0x%04x), SP", addr));
  //brk = true;
}

void CPU::op_09(){
  op_add(hl, bc);
  debug_instr.append("HL, BC");
}

void CPU::op_0A(){
  uint16_t addr = bc->get();
  op_ld(addr, &a);
  debug_instr.append("A, (BC)");
}

void CPU::op_0B(){
    op_dec(bc);
    debug_instr.append("BC");
}

void CPU::op_0C(){
    op_inc(&c);
    debug_instr.append("C");
}

void CPU::op_0D(){
    op_dec(&c);
    debug_instr.append("C");
}

void CPU::op_0E(){
  uint8_t addr = load8(++reg_pc);
  op_ld(addr, &c);
  debug_instr.append(string_format("C, Imm8:0x%02x", addr));
}

void CPU::op_0F(){
    op_rrca();
    debug_instr.append("A");
}

void CPU::op_10(){
    op_stop();
}

void CPU::op_11(){
  uint16_t addr_lo = (uint16_t)load8(++reg_pc);
  uint16_t addr_hi = (uint16_t)(load8(++reg_pc)) << 8;
  uint16_t addr = addr_hi + addr_lo;
  op_ld(addr, de);
  debug_instr.append(string_format("DE, Imm16:0x%04x", addr));
}

void CPU::op_12(){
  uint16_t addr = de->get();
  op_ld(&a, addr);
  debug_instr.append("(DE), A");
}

void CPU::op_13(){
    op_inc(de);
    debug_instr.append("DE");
}

void CPU::op_14(){
    op_inc(&d);
    debug_instr.append("D");
}

void CPU::op_15(){
    op_dec(&d);
    debug_instr.append("D");
}

void CPU::op_16(){
  uint8_t addr = load8(++reg_pc);
  op_ld(addr, &d);
  debug_instr.append(string_format("D, Imm8:0x%02x", addr));
}

void CPU::op_17(){
    op_rla();
    debug_instr.append("A");
}

void CPU::op_18(){
    //op_jr();
}

void CPU::op_19(){
    op_add(hl, de);
    debug_instr.append("HL, DE");
}

void CPU::op_1A(){
  uint16_t addr = de->get();
  op_ld(addr, &a);
  debug_instr.append("A, (DE)");
}

void CPU::op_1B(){
    op_dec(de);
    debug_instr.append("DE");
}

void CPU::op_1C(){
    op_inc(&e);
    debug_instr.append("E");
}

void CPU::op_1D(){
    op_dec(&e);
    debug_instr.append("E");
}

void CPU::op_1E(){
  uint8_t addr = load8(++reg_pc);
  op_ld(addr, &e);
  debug_instr.append(string_format("E, Imm8:0x%02x", addr));
}

void CPU::op_1F(){
    op_rra();
    debug_instr.append("A");
}

void CPU::op_20(){
  //op_jr();
}

void CPU::op_21(){
  uint16_t addr_lo = (uint16_t)load8(++reg_pc);
  uint16_t addr_hi = (uint16_t)(load8(++reg_pc)) << 8;
  uint16_t addr = addr_hi + addr_lo;
  op_ld(addr, hl);
  debug_instr.append(string_format("HL, Imm16:0x%04x", addr));
}

void CPU::op_22(){
  uint16_t addr = (hl->get()) + 1;
  op_ld(&a, addr);
  debug_instr.append("(HL+), A");
}

void CPU::op_23(){
    op_inc(hl);
    debug_instr.append("HL");
}

void CPU::op_24(){
    op_inc(&h);
    debug_instr.append("H");
}

void CPU::op_25(){
    op_dec(&h);
    debug_instr.append("H");
}

void CPU::op_26(){
  uint8_t addr = load8(++reg_pc);
  op_ld(addr, &h);
  debug_instr.append(string_format("H, Imm8:0x%02x", addr));
}

void CPU::op_27(){
    op_daa();
}

void CPU::op_28(){
    //op_jr();
}

void CPU::op_29(){
    op_add(hl, hl);
    debug_instr.append("HL, HL");
}

void CPU::op_2A(){
  uint16_t addr = (hl->get()) + 1;
  op_ld(addr, &a);
  debug_instr.append("A, (HL+)");
}

void CPU::op_2B(){
    op_dec(hl);
    debug_instr.append("hl");
}

void CPU::op_2C(){
    op_inc(&l);
    debug_instr.append("L");
}

void CPU::op_2D(){
    op_dec(&l);
    debug_instr.append("L");
}

void CPU::op_2E(){
  uint8_t addr = load8(++reg_pc);
  op_ld(addr, &l);
  debug_instr.append(string_format("L, Imm8:0x%02x", addr));
}

void CPU::op_2F(){
    op_cpl();
}

void CPU::op_30(){
  //op_jr();
}

void CPU::op_31(){
  uint16_t addr_lo = (uint16_t)load8(++reg_pc);
  uint16_t addr_hi = (uint16_t)(load8(++reg_pc)) << 8;
  uint16_t addr = addr_hi + addr_lo;
  op_ld(addr, &reg_sp);
  debug_instr.append(string_format("SP, Imm16:0x%04x", addr));
}

void CPU::op_32(){
  uint16_t addr = (hl->get()) - 1;
  op_ld(&a, addr);
  debug_instr.append("(HL-), A");
}

void CPU::op_33(){
    op_inc(&reg_sp);
    debug_instr.append("SP");
}

void CPU::op_34(){
    op_inc(hl->get());
    debug_instr.append("(HL)");
}

void CPU::op_35(){
    op_dec(hl->get());
    debug_instr.append("(HL)");
}

void CPU::op_36(){
  uint8_t addr = load8(++reg_pc);
  op_ld(addr, hl->get());
  debug_instr.append(string_format("(HL), Imm8:0x%02x", addr));
}

void CPU::op_37(){
  op_scf();
}

void CPU::op_38(){
    //op_jr();
}

void CPU::op_39(){
    op_add(hl, &reg_sp);
    debug_instr.append("HL, SP");
}

void CPU::op_3A(){
  uint16_t addr = (hl->get()) - 1;
  op_ld(addr, &a);
  debug_instr.append("A, (HL-)");
}

void CPU::op_3B(){
    op_dec(&reg_sp);
    debug_instr.append("SP");
}

void CPU::op_3C(){
    op_inc(&a);
    debug_instr.append("A");
}

void CPU::op_3D(){
    op_dec(&a);
    debug_instr.append("A");
}

void CPU::op_3E(){
  uint8_t addr = load8(++reg_pc);
  op_ld(addr, &a);
  debug_instr.append(string_format("A, Imm8:0x%02x", addr));
}

void CPU::op_3F(){
    op_ccf();
}

void CPU::op_80(){
    op_add(&a, &b);
    debug_instr.append("A, B");
}

void CPU::op_81(){
    op_add(&a, &c);
    debug_instr.append("A, C");
}

void CPU::op_82(){
    op_add(&a, &d);
    debug_instr.append("A, D");
}

void CPU::op_83(){
    op_add(&a, &e);
    debug_instr.append("A, E");
}

void CPU::op_84(){
    op_add(&a, &h);
    debug_instr.append("A, H");
}

void CPU::op_85(){
    op_add(&a, &l);
    debug_instr.append("A, L");
}

void CPU::op_86(){
  uint8_t val = load8(hl->get());
  op_add(&a, &val);
  debug_instr.append("A, (HL)");
}

void CPU::op_87(){
    op_add(&a, &a);
    debug_instr.append("A, A");
}

void CPU::op_88(){
    op_adc(&b);
    debug_instr.append("A, B");
}

void CPU::op_89(){
    op_adc(&c);
    debug_instr.append("A, C");
}

void CPU::op_8A(){
    op_adc(&d);
    debug_instr.append("A, D");
}

void CPU::op_8B(){
    op_adc(&e);
    debug_instr.append("A, E");
}

void CPU::op_8C(){
    op_adc(&h);
    debug_instr.append("A, H");
}

void CPU::op_8D(){
    op_adc(&l);
    debug_instr.append("A, L");
}

void CPU::op_8E(){
  uint8_t val = load8(hl->get());
  op_adc(&val);
  debug_instr.append("A, (HL)");
}

void CPU::op_8F(){
    op_adc(&a);
    debug_instr.append("A, A");
}

void CPU::op_90(){
    op_sub(&a, &b);
    debug_instr.append("A, B");
}

void CPU::op_91(){
    op_sub(&a, &c);
    debug_instr.append("A, C");
}

void CPU::op_92(){
    op_sub(&a, &d);
    debug_instr.append("A, D");
}

void CPU::op_93(){
    op_sub(&a, &e);
    debug_instr.append("A, E");
}

void CPU::op_94(){
    op_sub(&a, &h);
    debug_instr.append("A, H");
}

void CPU::op_95(){
    op_sub(&a, &l);
    debug_instr.append("A, L");
}

void CPU::op_96(){
  uint8_t val = load8(hl->get());
  op_sub(&a, &val);
  debug_instr.append("A, (HL)");
}

void CPU::op_97(){
    op_sub(&a, &a);
    debug_instr.append("A, A");
}

void CPU::op_98(){
    op_sbc(&b);
    debug_instr.append("A, B");
}

void CPU::op_99(){
    op_sbc(&c);
    debug_instr.append("A, C");
}

void CPU::op_9A(){
    op_sbc(&d);
    debug_instr.append("A, D");
}

void CPU::op_9B(){
    op_sbc(&e);
    debug_instr.append("A, E");
}

void CPU::op_9C(){
    op_sbc(&h);
    debug_instr.append("A, H");
}

void CPU::op_9D(){
    op_sbc(&l);
    debug_instr.append("A, L");
}

void CPU::op_9E(){
  uint8_t val = load8(hl->get());
  op_sbc(&val);
  debug_instr.append("A, (HL)");
}

void CPU::op_9F(){
    op_sbc(&a);
    debug_instr.append("A, A");
}

void CPU::op_A0(){
    op_and(&b);
    debug_instr.append("A, B");
}

void CPU::op_A1(){
    op_and(&c);
    debug_instr.append("A, C");
}

void CPU::op_A2(){
    op_and(&d);
    debug_instr.append("A, D");
}

void CPU::op_A3(){
    op_and(&e);
    debug_instr.append("A, E");
}

void CPU::op_A4(){
    op_and(&h);
    debug_instr.append("A, H");
}

void CPU::op_A5(){
    op_and(&l);
    debug_instr.append("A, L");
}

void CPU::op_A6(){
  uint8_t val = load8(hl->get());
  op_and(&val);
  debug_instr.append("A, (HL)");
}

void CPU::op_A7(){
    op_and(&a);
    debug_instr.append("A, A");
}

void CPU::op_A8(){
    op_xor(&b);
    debug_instr.append("A, B");
}

void CPU::op_A9(){
    op_xor(&c);
    debug_instr.append("A, C");
}

void CPU::op_AA(){
    op_xor(&d);
    debug_instr.append("A, D");
}

void CPU::op_AB(){
    op_xor(&e);
    debug_instr.append("A, E");
}

void CPU::op_AC(){
    op_xor(&h);
    debug_instr.append("A, H");
}

void CPU::op_AD(){
    op_xor(&l);
    debug_instr.append("A, L");
}

void CPU::op_AE(){
    op_xor(&e);
    debug_instr.append("A, (HL)");
}

void CPU::op_AF(){
    op_xor(&a);
    debug_instr.append("A, A");
}

void CPU::op_B0(){
    op_or(&b);
    debug_instr.append("A, B");
}

void CPU::op_B1(){
    op_or(&c);
    debug_instr.append("A, C");
}

void CPU::op_B2(){
    op_or(&d);
    debug_instr.append("A, D");
}

void CPU::op_B3(){
    op_or(&e);
    debug_instr.append("A, E");
}

void CPU::op_B4(){
    op_or(&h);
    debug_instr.append("A, H");
}

void CPU::op_B5(){
    op_or(&l);
    debug_instr.append("A, L");
}

void CPU::op_B6(){
    op_or(&e);
    debug_instr.append("A, (HL)");
}

void CPU::op_B7(){
    op_or(&l);
    debug_instr.append("A, A");
}

void CPU::op_B8(){
    op_cp(&b);
    debug_instr.append("A, B");
}

void CPU::op_B9(){
    op_cp(&c);
    debug_instr.append("A, C");
}

void CPU::op_BA(){
    op_cp(&d);
    debug_instr.append("A, D");
}

void CPU::op_BB(){
    op_cp(&e);
    debug_instr.append("A, E");
}

void CPU::op_BC(){
    op_cp(&h);
    debug_instr.append("A, H");
}

void CPU::op_BD(){
    op_cp(&l);
    debug_instr.append("A, L");
}

void CPU::op_BE(){
    op_cp(&e);
    debug_instr.append("A, (HL)");
}

void CPU::op_BF(){
    op_cp(&a);
    debug_instr.append("A, A");
}

void CPU::op_C0(){

}

void CPU::op_C1(){

}

void CPU::op_C2(){
  uint8_t addr_lo = load8(++reg_pc);
  uint8_t addr_hi = load8(++reg_pc);
  uint16_t addr = (uint16_t)(addr_hi << 8) + (uint16_t)addr_lo;
  //op_jp(nz, addr);  // TODO: need to implement flags first
  debug_instr.append(string_format("NZ, Imm16:0x%04x", addr));
}

void CPU::op_C3(){
  uint8_t addr_lo = load8(++reg_pc);
  uint8_t addr_hi = load8(++reg_pc);
  uint16_t addr = (uint16_t)(addr_hi << 8) + (uint16_t)addr_lo;
  op_jp(addr);
  debug_instr.append(string_format("Imm16:0x%04x", addr));
  brk = true;
}

void CPU::op_C4(){

}

void CPU::op_C5(){

}

void CPU::op_C6(){

}

void CPU::op_C7(){

}

void CPU::op_C8(){

}

void CPU::op_C9(){

}

void CPU::op_CA(){
  uint8_t addr_lo = load8(++reg_pc);
  uint8_t addr_hi = load8(++reg_pc);
  uint16_t addr = (uint16_t)(addr_hi << 8) + (uint16_t)addr_lo;
  //op_jp(z, addr);
  debug_instr.append(string_format("Z, Imm16:0x%04x", addr));
}

void CPU::op_CB(){

}

void CPU::op_CC(){

}

void CPU::op_CD(){

}

void CPU::op_CE(){

}

void CPU::op_CF(){

}


// All instructions
void CPU::op_nop(){
    // do nothing
    debug_instr = "NOP ";
}

// NOTE: LD rr, nn means load to rr the contents of nn
// NOTE: when accessing 16bit addresses, first is LO then HI
// meaning pc->instr => pc+1->lo => pc+2->hi

// mov 8bits from src_reg to dest_reg
void CPU::op_ld(uint8_t *src_reg, uint8_t *dest_reg){
  debug_instr = "LD ";
  *dest_reg = *src_reg;
}

// mov 16bits from src_reg to dest_reg
void CPU::op_ld(Regcomb *src_reg, Regcomb *dest_reg){
  debug_instr = "LD ";
  dest_reg->set(src_reg->get());
}

// mov 8bits from src_addr to dest_addr
void CPU::op_ld(uint16_t src_addr, uint16_t dest_addr){
  debug_instr = "LD ";
  store8(dest_addr, load8(src_addr));
}

// load 8bits from addr in memory to dest_reg
void CPU::op_ld(uint16_t addr, uint8_t *dest_reg){
  debug_instr = "LD ";
  *dest_reg = load8(addr);
}

// load 16bits from addr in memory to dest_reg
void CPU::op_ld(uint16_t addr, Regcomb *dest_reg){
  debug_instr = "LD ";
  dest_reg->set(load16(addr));
}

// load 16bits from addr in memory to 16bit dest_reg (specifically SP)
void CPU::op_ld(uint16_t addr, uint16_t *dest_reg){
  debug_instr = "LD ";
  *dest_reg = load16(addr);
}

// store 8bits from src_reg to addr in memory
void CPU::op_ld(uint8_t *src_reg, uint16_t addr){
  debug_instr = "LD ";
  store8(addr, *src_reg);
}

// store 16bits from src_reg to addr in memory
void CPU::op_ld(Regcomb *src_reg, uint16_t addr){
  debug_instr = "LD ";
  store16(addr, src_reg->get());
}

// store 16bits from src_reg (specifically SP) to addr in memory
void CPU::op_ld(uint16_t *src_reg, uint16_t addr){
  debug_instr = "LD ";
  store16(addr, *src_reg);
}

void CPU::op_add(uint8_t *reg, uint8_t *val){
  debug_instr = "ADD ";
  *reg = *reg + *val;

  // TODO: set flags such as carry, etc
}

void CPU::op_add(Regcomb *a, Regcomb *b){
  debug_instr = "ADD ";
  a->set(a->get() + b->get());

  // TODO: set flags such as carry, etc
}

void CPU::op_add(Regcomb *a, uint16_t *b){
  debug_instr = "ADD ";
  a->set(a->get() + *b);

  // TODO: set flags such as carry, etc
}

void CPU::op_inc(uint8_t *reg){
    debug_instr = "INC ";
    *reg++;
}

void CPU::op_inc(uint16_t *reg){
    debug_instr = "INC ";
    *reg++;
}

void CPU::op_inc(Regcomb *reg){
    debug_instr = "INC ";
    reg->increment();
}

void CPU::op_inc(uint16_t addr){
  debug_instr = "INC ";
  uint8_t val = load8(addr);
  val++;
  store8(addr, val);
}

void CPU::op_dec(uint8_t *reg){
    debug_instr = "DEC ";
    *reg--;
}

void CPU::op_dec(uint16_t *reg){
    debug_instr = "DEC ";
    *reg--;
}

void CPU::op_dec(Regcomb *reg){
    debug_instr = "DEC ";
    reg->decrement();
}

void CPU::op_dec(uint16_t addr){
  debug_instr = "DEC ";
  uint8_t val = load8(addr);
  val--;
  store8(addr, val);
}

void CPU::op_adc(uint8_t *val){
    debug_instr = "ADC ";
    uint8_t carry = f;
    a += *val + carry;

    // TODO: set flags such as carry, etc
}

void CPU::op_sub(uint8_t *reg, uint8_t *val){
    debug_instr = "SUB ";
    *reg = *reg - *val;
}

void CPU::op_sbc(uint8_t *val){
    debug_instr = "SBC ";
    uint8_t carry = f;
    a -= *val - carry;
}

void CPU::op_and(uint8_t *val){
    debug_instr = "AND ";
    a &= *val;
}

void CPU::op_xor(uint8_t *val){
    debug_instr = "XOR ";
    a ^= *val;
}

void CPU::op_or(uint8_t *val){
    debug_instr = "OR ";
    a |= *val;
}

// TODO: CP is a subtraction from A that doesn't update A, only the flags it would have set/reset if it really was subtracted.
void CPU::op_cp(uint8_t *val){
    debug_instr = "CP ";
    uint8_t res = a - *val;

    // TODO: update flags
}

void CPU::op_cpl(){
  debug_instr = "CPL";
  a = ~a;

  // TODO: update flags (N = 1, H = 1)
}

void CPU::op_jp(uint16_t addr){
    debug_instr = "JP ";
    reg_pc = addr-1;  // we subtract 1 because in cycle reg pc is incremented before moving to the next one
}

// Uncoditional jump to the absolute address specified by 16bit register (specifically HL)
void CPU::op_jp(Regcomb *reg){
    debug_instr = "JP ";
    reg_pc = reg->get() - 1;  // we subtract 1 because in cycle reg pc is incremented before moving to the next one
}

// Conditional jump to 16bit addr depending on condition from reg
void CPU::op_jp(uint8_t *reg, uint16_t addr){
    debug_instr = "JP ";
}

// Conditional jump to 16bit addr depending on condition from reg
void CPU::op_jp(uint16_t *reg, uint16_t addr){
    debug_instr = "JP ";
}

void CPU::op_jr(){
    debug_instr = "JR ";
    // TODO

}

void CPU::op_rlc(uint8_t *reg){
    debug_instr = "RLC ";
    uint8_t carry = *reg >> 7;
    uint8_t res = (*reg << 1) | carry;
    *reg = res;

    // TODO: set flags as well
}

void CPU::op_rlca(){
    debug_instr = "RLCA";
    op_rlc(&a);
}

void CPU::op_rl(uint8_t *reg){
    debug_instr = "RL ";
    uint8_t carry = *reg >> 7;
    uint8_t res = (*reg << 1) | carry;
    *reg = res;

    // TODO: set flags (carry is false)
}

void CPU::op_rla(){
    debug_instr = "RLA";
    op_rl(&a);
}

void CPU::op_rrc(uint8_t *reg){
    debug_instr = "RRC ";
    uint8_t carry = *reg & 0x1;
    uint8_t res = (*reg >> 1) | (carry << 7);
    *reg = res;

    // TODO: handle flags
}

void CPU::op_rrca(){
    debug_instr = "RRCA";
    op_rrc(&a);
}

void CPU::op_rr(uint8_t *reg){
    debug_instr = "RR ";
    uint8_t carry = *reg & 0x1;
    uint8_t res = (*reg >> 1) | (carry << 7);
    *reg = res;

    // TODO: handle flags (carry = false)
}

void CPU::op_rra(){
    debug_instr = "RRA ";
    op_rr(&a);
}

void CPU::op_daa(){
  debug_instr = "DAA ";
  // TODO: handle flags
  /*
  // note: assumes a is a uint8_t and wraps from 0xff to 0
  if (!n_flag) {  // after an addition, adjust if (half-)carry occurred or if result is out of bounds
    if (c_flag || a > 0x99) { a += 0x60; c_flag = 1; }
    if (h_flag || (a & 0x0f) > 0x09) { a += 0x6; }
  } else {  // after a subtraction, only adjust if (half-)carry occurred
    if (c_flag) { a -= 0x60; }
    if (h_flag) { a -= 0x6; }
  }
  // these flags are always updated
  z_flag = (a == 0); // the usual z flag
  h_flag = 0; // h flag is always cleared
  */
}

// TODO: write this
void CPU::op_scf(){
  debug_instr = "SCF ";
}

// TODO: write this
void CPU::op_ccf(){
  debug_instr = "CCF ";
}

void CPU::op_stop(){
    debug_instr = "STOP ";
}
