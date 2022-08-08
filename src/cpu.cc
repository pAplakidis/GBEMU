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
    printf("0x%02x\t", instr);

    execute(instr);
    std::cout << debug_instr << std::endl;

    reg_pc++;
    // TODO: remove when done debugging
    //if(reg_pc == 2){
    //if(reg_pc > 0x0110){
    //    exit(0);
    //}
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
}
