#pragma once

#include <stdint.h>

// combination of registers
class Regcomb{
private:
    uint8_t hi, lo;

public:
    Regcomb(uint8_t hi, uint8_t lo);

    uint8_t get_hi();
    uint8_t get_lo();
    void set();
};
