#include "gameboy.h"

Gameboy::Gameboy(std::string rom_path){
    auto rom_data = read_rom(rom_path);
    std::string *p_rom_data = std::string(rom_data.begin(), rom_data.end());
    hexdump((void*)(p_rom_data), p_rom_data->length());

    ctrg = new Cartridge(rom_data);
    cpu = new CPU();
}

Gameboy::~Gameboy(){

}

auto Gameboy::read_rom(std::string rom_path) -> std::vector<uint8_t> {
    std::ifstream stream(rom_path.c_str(), std::ios::binary|std::ios::ate);
    if(!stream.good()){
        printf("Error reading from file: %s\n", rom_path.c_str());
        exit(1);
    }

    std::ifstream::pos_type pos = stream.tellg();
    auto file_size = static_cast<size_t>(pos);
    std::vector<char> file_data(file_size);

    stream.seekg(0, std::ios::beg);
    stream.read(&file_data[0], static_cast<std::streamsize>(pos));
    stream.close();

    auto data = std::vector<uint8_t>(file_data.begin(), file_data.end());
    return data;
}
