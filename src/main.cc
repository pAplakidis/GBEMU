#include <stdio.h>
#include <stdlib.h>

#include "gameboy.h"

int main(int argc, char **argv){

  if(argc < 2){
    printf("Usage %s <ROM file>\n", argv[0]);
    exit(1);
  }
  
  std::string rom_path = argv[1];

  Gameboy *gb = new Gameboy(rom_path);

  return 0;
}
