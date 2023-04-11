#include "register.h"

// Regcomb methods
Regcomb::Regcomb(uint8_t hi, uint8_t lo){
  this->hi = hi;
  this->lo = lo;
  val = (uint16_t) (hi << 8) + (uint16_t)lo;
}

uint8_t Regcomb::get_hi(){

}

uint8_t Regcomb::get_lo(){

}

void Regcomb::set(uint16_t new_val){
    val = new_val;
}

uint16_t Regcomb::get(){
    return val;
}

void Regcomb::increment(){
    set(get() + 1);
}

void Regcomb::decrement(){
    set(get() - 1);
}

// FlagReg methods
FlagReg::FlagReg(){
  val = 0x00;
}

uint8_t FlagReg::get(){
  return val;
}

void FlagReg::set(uint8_t new_val){
  val = new_val & 0xF0;
}


void FlagReg::set_flag_zero(bool set){
  val = set_bit_at(val, 7, set);
}

void FlagReg::set_flag_subtract(bool set){
  val = set_bit_at(val, 6, set);
}

void FlagReg::set_flag_half_carry(bool set){
  val = set_bit_at(val, 5, set);
}

void FlagReg::set_flag_carry(bool set){
  val = set_bit_at(val, 4, set);
}

bool FlagReg::flag_zero(){
  return (bool)((val & (1 << 7)) >> 7);
}

bool FlagReg::flag_subtract(){
  return (bool)((val & (1 << 6)) >> 6);
}

bool FlagReg::flag_half_carry(){
  return (bool)((val & (1 << 5)) >> 5);
}

bool FlagReg::flag_carry(){
  return (bool)((val & (1 << 4)) >> 4);
}

uint8_t FlagReg::flag_zero_val(){

}

uint8_t FlagReg::flag_subtract_val(){

}

uint8_t FlagReg::flag_half_carry_val(){

}

uint8_t FlagReg::flag_carry_val(){

}
