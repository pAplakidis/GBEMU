#pragma once

#include <stdio.h>
#include <stdint.h>
#include <vector>

#include "utils.h"
#include "cartridge.h"
#include "cpu.h"

class Gameboy{
private:
  //static const size_t MEM_SIZE = 8 * 1024;
  static const size_t MEM_SIZE = 1024 * 1024; // TODO: using temporarily 1MB of RAM
  unsigned char memory[MEM_SIZE]; // work RAM (WRAM)

  Cartridge *ctrg;
  CPU *cpu;

public:
  Gameboy(std::string rom_path);
  ~Gameboy();
  void run();
  // TODO: load rom into memory
  auto read_rom(std::string rom_path) -> std::vector<uint8_t>;

};
