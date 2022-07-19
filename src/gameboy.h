#pragma once

#include <stdio.h>
#include <stdint.h>
#include <vector>

#include "utils.h"
#include "cartridge.h"
#include "cpu.h"

class Gameboy{
private:
  static const size_t MEM_SIZE = 8 * 1024;
  unsigned char memory[MEM_SIZE]; // work RAM (WRAM)

  Cartridge *ctrg;
  CPU *cpu;

public:
  Gameboy(std::string rom_path);
  ~Gameboy();
  void run();
  auto read_rom(std::string rom_path) -> std::vector<uint8_t>;
};
