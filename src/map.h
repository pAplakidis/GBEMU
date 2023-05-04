#pragma once

#include <cstdlib>
#include <stdio.h>
#include <stdint.h>

namespace map{

class Range{
public:
  uint16_t start, end;

  Range(uint16_t start, uint16_t end);
  uint16_t* contains(uint16_t addr) const;
};

extern const Range *ROM_bank0;  // From cartridge, usually a fixed bank
extern const Range *ROM_bank1;  // From cartridge, switchable bank via MBC (if any)
extern const Range *VRAM;       // Only bank 0 in Non-CGB mode. Switchable bank 0/1 in CGB mode
extern const Range *EXT_RAM;    // External RAM. In cartridge, switchable bank if any
extern const Range *WRAM_bank0; // Work RAM
extern const Range *WRAM_bank1; // Only bank 1 in Non-CGB mode. Switchable bank 1~7 in CGB mode   
extern const Range *ECHO_RAM;   // Typically not used
extern const Range *OAM;        // Sprite attribute table
extern const Range *IO_Regs;    // I/O Registers
extern const Range *HRAM;       // High RAM
extern const Range *IE;         // Interrupts Enable Register

}
