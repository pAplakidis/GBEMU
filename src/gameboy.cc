#include "gameboy.h"

Gameboy::Gameboy(std::string rom_path){
    int32_t sdl_context = SDL_Init(SDL_INIT_VIDEO);
    auto rom_data = read_rom(rom_path);

    // TODO: place the ROM at the correct address range according to the memory map
    // print ROM contents and copy them to main memory
    int idx = 0;
    for(uint8_t i: rom_data){
        printf("0x%04x: 0x%02x\t", idx, i);
        if(idx % 4 == 0)
            printf("\n");
        idx++;

        memory[idx] = i;
    }
    printf("\nROM data size: %d bytes\n", rom_data.size());

    // init components
    ctrg = new Cartridge(rom_data);
    cpu = new CPU(memory, MEM_SIZE, mmu);
    renderer = new Renderer(sdl_context);
}

Gameboy::~Gameboy(){

}

void Gameboy::run(){
    cpu->main_loop();
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
