# GBEMU
A Gameboy Emulator implemented in C++

## USAGE
```
mkdir build
cd build
cmake ..
make
./GBEMU <path to .gb file>
```

## Minor TODOs
- place the ROM at the correct address range according to the memory map (gameboy.cc)
- move store and load ops to MMU (mmu.h)
- (cpu.cc)
- some commands have variable number of cycles, handle timing
- print stack values along with registers
- check if addresses in stores and loads are aligned
- after implementing timing/cycles, implement STOP and HALT
- prefixed opecodes

## Major TODOs
- Implement Full Memory Map
- Implement Load and Store Instructions (DONE)
- Implement Flags (DONE)
- Implement Jump Instructions (DONE)
- Implement Timing/Cycles (DONE)
- Implement Interrupts/Exceptions and handlers  (DONE, dummy exceptions tho)
- Implement Graphics
- Improve Debugging => Separate Debugger
- Test on games

