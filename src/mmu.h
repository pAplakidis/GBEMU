#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


// TODO: move store and load functions from CPU here (might move main memory here as well)
class MMU{
public:
    MMU();
    ~MMU();

    auto read(const uint16_t addr) const -> uint8_t;
    void write(const uint8_t addr, uint8_t data);
};
