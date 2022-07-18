#pragma once

#include <stdio.h>
#include <fstream>
#include <vector>

class Cartridge{
public:
    Cartridge(std::vector<uint8_t> rom_data);
    ~Cartridge();
};
