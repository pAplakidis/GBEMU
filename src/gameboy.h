#pragma once

#include <stdio.h>
#include <stdint.h>

class Gameboy{
private:
  static const size_t MEM_SIZE = 8 * 1024;
  unsigned char memory[MEM_SIZE];

public:
  Gameboy();
  ~Gameboy();
};
