#include "utils.h"

template<typename ... Args>
std::string string_format( const std::string& format, Args ... args )
{
    int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
    auto size = static_cast<size_t>( size_s );
    std::unique_ptr<char[]> buf( new char[ size ] );
    std::snprintf( buf.get(), size, format.c_str(), args ... );
    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}

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
