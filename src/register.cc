#include "register.h"

Regcomb::Regcomb(uint8_t hi, uint8_t lo){
    this->hi = hi;
    this->lo = lo;
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
