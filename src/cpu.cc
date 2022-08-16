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

    printf("0x%04x:\t", reg_pc);
    uint8_t instr = load(reg_pc);
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
        // TODO: print registers and stack values
        exit(0);
    }
}

void CPU::execute(uint8_t instr){
    switch(instr){
        case 0x00:
            op_00();
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
        default:
            printf("Opcode not supported\n");
            break;
    }
}

uint8_t CPU::mem_load(uint16_t offset){
    size_t off = (size_t)offset;
    if(offset < 8*1024)
        return memory_ptr[off];

    return 0x00;
}

void CPU::mem_store(uint16_t offset, uint8_t data){
    size_t off = (size_t)offset;
    if(offset < 8*1024)
        memory_ptr[off] = data;

}

void CPU::store(uint16_t addr, uint8_t data){
    // TODO: this is temporary since memory map is not finished

}

uint8_t CPU::load(uint16_t addr){

    // TODO: check if addr is aligned

    // TODO: we are currently using just one big junk of memory, but later it needs to utilize the memory map
    //if(uint16_t *offset = map::ROM_bank0->contains(addr)){
    //
    //}

    return mem_load(addr);
}

// All opcodes
void CPU::op_00(){
    op_nop();
}

void CPU::op_01(){
    op_ld();
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

// All instructions
void CPU::op_nop(){
    // do nothing
    debug_instr = "NOP ";
}

void CPU::op_ld(){
    debug_instr = "LD ";
}

void CPU::op_add(uint8_t *reg, uint8_t *val){
    debug_instr = "ADD ";
    *reg = *reg + *val;

    // TODO: set flags such as carry, etc
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
    brk = true;

    // TODO: update flags
}
