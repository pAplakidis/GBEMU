#pragma once

#include <stdio.h>
#include <stdint.h>
#include <vector>

#include<SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>

#include "cartridge.h"
#include "cpu.h"
#include "renderer.h"
#include "utils.h"

class Gameboy{
private:
  //static const size_t MEM_SIZE = 8 * 1024;
  static const size_t MEM_SIZE = 1024 * 1024; // TODO: using temporarily 1MB of RAM
  unsigned char memory[MEM_SIZE]; // work RAM (WRAM)

  Cartridge *ctrg;
  CPU *cpu;
  MMU *mmu;
  Renderer *renderer;

public:
  Gameboy(std::string rom_path);
  ~Gameboy();
  void run();
  auto read_rom(std::string rom_path) -> std::vector<uint8_t>;
};
