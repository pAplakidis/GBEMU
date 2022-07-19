#include "cpu.h"

CPU::CPU(uint8_t *memory_ptr, int m_size){
    a, b, c, d, e, f, h, l = 0x00;
    af = new Regcomb(a, f);
    bc = new Regcomb(b, c);
    de = new Regcomb(d, e);
    hl = new Regcomb(h, l);

    reg_pc = 0x00;
    reg_sp = 0x00;

    this->memory_ptr = memory_ptr;
}

CPU::~CPU(){

}

void CPU::main_loop(){
    while(1){
        cycle();
    }
}

void CPU::cycle(){
    printf("0x04:\t", reg_pc);
}

uint16_t CPU::mem_load16(uint16_t offset){
    size_t off = (size_t)offset;
    uint16_t b0 = memory_ptr[off + 0];
    uint16_t b1 = memory_ptr[off + 1];
    uint16_t l_endian = b0 | (b1 << 8);
    return l_endian;
}

uint8_t CPU::mem_load8(uint8_t offset){
    size_t off = (size_t)offset;
    return memory_ptr[off];
}


void CPU::load16(uint16_t addr){
    // TODO: check if addr is aligned
    if(uint16_t *offset = map::ROM_bank0->contains(addr)){

    }
}

void CPU::load8(uint8_t addr){
    // TODO: check if addr is aligned

}
