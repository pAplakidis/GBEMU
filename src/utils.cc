#include "utils.h"

uint8_t set_bit(uint8_t val, uint8_t bit_loc){
  return (uint8_t)(val | (1 << bit_loc));
}

uint8_t clear_bit(uint8_t val, uint8_t bit_loc){
  return (uint8_t)(val & ~(1 << bit_loc));
}

uint8_t set_bit_at(uint8_t val, uint8_t bit_loc, bool set){
  if(set)
    return set_bit(val, bit_loc);
  else
    return clear_bit(val, bit_loc);
}
