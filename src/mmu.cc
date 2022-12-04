#include "mmu.h"


MMU::MMU(){

}

MMU::~MMU(){

}

auto MMU::read(const uint16_t addr) const -> uint8_t {
    // Cartridge
    if(0x0 <= addr <= 0x7FFF){
        
    }

    // VRAM
    if(0x8000 <= addr <= 0x9FFF){
    
    }

    // External cartridge RAM
    if(0xA000 <= addr <= 0xBFFF){
    
    }

    // WRAM
    if(0xC000 <= addr <= 0xDFFF){
    
    }
    
    // Mirrored work RAM
    if(0xE000 <= addr <= 0xFDFF){
        
    }
    
    // OAM (sprite attribute table)
    if(0xFE00 <= addr <= 0xFE9F){
    
    }
    
    // Not usable
    if(0xFEA0 <= addr <= 0xFEFF){
    
    }
    
    // IO registers
    if(0xFF00 <= addr <= 0xFF7F){
        
    }
    
    // HRAM
    if(0xFF80 <= addr <= 0xFFFE){
    
    }
    
    // IE (Interrupt Enable Register)
    if(addr == 0xFFFF){
    
    }

    printf("Error: unmapped memory address 0x%X\n", addr);
    exit(1);
}

void MMU::write(const uint8_t addr, uint8_t data){

}
