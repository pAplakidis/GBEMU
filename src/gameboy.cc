#include "gameboy.h"

Gameboy::Gameboy(std::string rom_path) {
  int32_t sdl_context = SDL_Init(SDL_INIT_VIDEO);
  auto rom_data = read_rom(rom_path);

  // map print ROM contents and copy them to main memory
  int idx = 0;
  printf("ROM data:\n");
  while (idx < rom_data.size()) {
    printf("0x%04x: 0x%02x 0x%02x 0x%02x 0x%02x\n", idx, rom_data[idx],
           rom_data[idx + 1], rom_data[idx + 2], rom_data[idx + 3]);
    for (int i = 0; i < 4 && idx < rom_data.size(); i++) {
      memory[idx] = rom_data[idx];
      idx++;
    }
  }
  printf("\nROM data size: %d bytes\n\n", rom_data.size());

  // init components
  ctrg = new Cartridge(rom_data);
  cpu = new CPU(memory, MEM_SIZE, mmu);
  renderer = new Renderer(sdl_context);
}

Gameboy::~Gameboy() {}

void Gameboy::run() { cpu->main_loop(); }

auto Gameboy::read_rom(std::string rom_path) -> std::vector<uint8_t> {
  std::ifstream stream(rom_path.c_str(), std::ios::binary | std::ios::ate);
  if (!stream.good()) {
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
