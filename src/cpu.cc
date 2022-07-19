#include "cpu.h"

CPU::CPU(){
    a, b, c, d, e, f, h, l = 0x00;
    af = new Regcomb(a, f);
    bc = new Regcomb(b, c);
    de = new Regcomb(d, e);
    hl = new Regcomb(h, l);

    reg_pc = 0x00;
    reg_sp = 0x00;
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
