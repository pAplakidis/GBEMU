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
    printf("0x%04x:\t", reg_pc);
    uint8_t instr = load(reg_pc);
    printf("0x%02x\n", instr);

    execute(instr);

    reg_pc++;
}

void CPU::execute(uint8_t instr){
    switch(instr){
        case 0x00:
            op_nop();
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

// All instructions
void CPU::op_nop(){
    // do nothing
}

void CPU::op_ld(){

}
