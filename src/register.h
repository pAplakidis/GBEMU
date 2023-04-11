#pragma once

#include <stdint.h>

#include "utils.h"

// combination of registers
class Regcomb{
private:
  uint8_t hi, lo;
  uint16_t val;

public:
  Regcomb(uint8_t hi, uint8_t lo);

  uint8_t get_hi();
  uint8_t get_lo();
  void set(uint16_t new_val);
  uint16_t get();
  void increment();
  void decrement();
};

class FlagReg{
private:
  uint8_t val;

public:
  FlagReg();

  uint8_t get();
  void set(uint8_t new_val);

  void set_flag_zero(bool set);
  void set_flag_subtract(bool set);
  void set_flag_half_carry(bool set);
  void set_flag_carry(bool set);

  bool flag_zero();       // Z
  bool flag_subtract();   // N
  bool flag_half_carry(); // H
  bool flag_carry();      // C

  uint8_t flag_zero_val();
  uint8_t flag_subtract_val();
  uint8_t flag_half_carry_val();
  uint8_t flag_carry_val();
};
