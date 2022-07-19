#include "map.h"

namespace map{

Range::Range(uint16_t start, uint16_t end){
    this->start = start;
    this->end = end;
}

// Returns an offset if the address is within range
uint16_t* Range::contains(uint16_t addr) const{
    if(addr >= start && addr < end){
        uint16_t *res = (uint16_t*)malloc(sizeof(uint16_t));
        *res = addr - start;
        return res;
    }
    else{
        return NULL;
    }
}

const Range *ROM_bank0 = new Range(0x0000, 0x3fff);
const Range *ROM_bank1 = new Range(0x4000, 0x7fff);
const Range *VRAM = new Range(0x8000, 0x9fff);
const Range *EXT_RAM = new Range(0xa000, 0xbfff);
const Range *WRAM_bank0 = new Range(0xc000, 0xcfff);
const Range *WRAM_bank1 = new Range(0xd000, 0xdfff);
const Range *ECHO_RAM = new Range(0xe000, 0xfdff);
const Range *OAM = new Range(0xf000, 0xfe9f);
const Range *IO_Regs = new Range(0xf000, 0xfeff);
const Range *HRAM = new Range(0xf000, 0xff7f);
const Range *IE = new Range(0xffff, 0xffff);

}
