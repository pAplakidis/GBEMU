#pragma once

#include <string>
#include <memory>
#include <stdexcept>

template<typename ... Args> std::string string_format( const std::string& format, Args ... args );
uint8_t set_bit(uint8_t val, uint8_t bit_loc);
uint8_t clear_bit(uint8_t val, uint8_t bit_loc);
uint8_t set_bit_at(uint8_t val, uint8_t bit_loc, bool set);
