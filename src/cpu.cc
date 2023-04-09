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

        // TODO: dump memory to string then write to file
        for(int i=0; i < MEMSIZE - 8; i += 8){
            mem_dump.append(string_format("0x%06x:\t", i));
            for(int j=i; j < i+8; j++){
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
            //brk = true;
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
  uint16_t addr_lo = load8(++reg_pc);
  uint16_t addr_hi = load8(++reg_pc) << 8;
  uint16_t addr = addr_hi + addr_lo;
  printf("Imm16: 0x%04x -> ", addr);
  op_ld(addr, bc);
  debug_instr.append("BC, imm16");
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
  printf("Imm8: 0x%02x -> ", addr);
  op_ld(addr, &b);
  debug_instr.append("B, Imm8");
}

void CPU::op_07(){
  op_rlca();
  debug_instr.append("A");
}

// TODO: double check this
void CPU::op_08(){
  uint16_t addr_lo = load8(++reg_pc);
  uint16_t addr_hi = load8(++reg_pc) << 8;
  uint16_t addr = addr_hi + addr_lo;
  printf("Imm16: 0x%04x -> ", addr);
  op_ld(&reg_sp, addr);
  debug_instr.append("(Imm16), SP");
}

void CPU::op_09(){
  op_add(hl, bc);
  debug_instr.append("HL, BC");
}

void CPU::op_0A(){
  uint16_t addr = bc->get();
  op_ld(addr, &a);
  debug_instr.append("A, (BC)");
  brk = true;
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
    //op_ld();
}

void CPU::op_0F(){
    op_rrca();
    debug_instr.append("A");
}

void CPU::op_10(){
    op_stop();
}

void CPU::op_11(){
    //op_ld();
}

void CPU::op_12(){
    //op_ld();
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
    //op_ld();
}

void CPU::op_17(){
    op_rla();
    debug_instr.append("A");
}

void CPU::op_18(){
    op_jr();
}

void CPU::op_19(){
    op_add(hl, de);
    debug_instr.append("HL, DE");
}

void CPU::op_1A(){
    //op_ld();
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
    //op_ld();
}

void CPU::op_1F(){
    op_rra();
    debug_instr.append("A");
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
    // TODO
    op_add(&a, &e);
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
    // TODO
    op_adc(&e);
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
    // TODO
    op_sub(&a, &e);
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
    // TODO
    op_sbc(&e);
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
    // TODO
    op_and(&e);
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
    // TODO: pass address
    //op_jp();
    debug_instr.append("NZ, addr");
}

void CPU::op_C3(){
    // TODO: pass address
    //op_jp();
    debug_instr.append("addr");
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
    // TODO: add address
    //op_jp();
    debug_instr.append("Z, addr");

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
    //brk = true;
}

// mov 16bits from src_reg to dest_reg
void CPU::op_ld(Regcomb *src_reg, Regcomb *dest_reg){
    debug_instr = "LD ";
    dest_reg->set(src_reg->get());
    //brk = true;
}

// load 8bits from addr in memory to dest_reg
void CPU::op_ld(uint16_t addr, uint8_t *dest_reg){
    debug_instr = "LD ";
    *dest_reg = load8(addr);
    //brk = true;
}

// load 16bits from addr in memory to dest_reg
void CPU::op_ld(uint16_t addr, Regcomb *dest_reg){
    debug_instr = "LD ";
    dest_reg->set(load16(addr));
}

// store 8bits from src_reg to addr in memory
void CPU::op_ld(uint8_t *src_reg, uint16_t addr){
    debug_instr = "LD ";
    store8(addr, *src_reg);
    //brk = true;
}

// store 16bits from src_reg to addr in memory
void CPU::op_ld(Regcomb *src_reg, uint16_t addr){
    debug_instr = "LD ";
    store16(addr, src_reg->get());
    //brk = true;
}

// store 16bits from src_reg (specifically SP) to addr in memory
void CPU::op_ld(uint16_t *src_reg, uint16_t addr){
    debug_instr = "LD ";
    store16(addr, *src_reg);
    //brk = true;
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

void CPU::op_inc(uint8_t *reg){
    debug_instr = "INC ";
    *reg++;
}

void CPU::op_inc(Regcomb *reg){
    debug_instr = "INC ";
    reg->increment();
}

void CPU::op_dec(uint8_t *reg){
    debug_instr = "DEC ";
    *reg--;
}

void CPU::op_dec(Regcomb *reg){
    debug_instr = "DEC ";
    reg->decrement();
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

void CPU::op_jp(uint8_t addr){
    debug_instr = "JP ";
    reg_pc = addr;
    //brk = true;

    // TODO: handle flags and conditions
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

void CPU::op_stop(){
    debug_instr = "STOP ";
}
