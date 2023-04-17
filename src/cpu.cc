#include "cpu.h"

/*
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
*/


CPU::CPU(uint8_t *memory_ptr, int m_size){
    a, b, c, d, e, f, h, l = 0x00;
    af = new Regcomb(a, f);
    bc = new Regcomb(b, c);
    de = new Regcomb(d, e);
    hl = new Regcomb(h, l);

    reg_pc = 0x00;
    reg_sp = 0x00;

    flag = new FlagReg();

    this->memory_ptr = memory_ptr;
}

CPU::~CPU(){

}

void CPU::main_loop(){
    while(1){
        cycle();

        //break;  // TODO: temporary for debugging
    }
}

// TODO: some commands have variable number of cycles (handle timing)
void CPU::cycle(){
    debug_instr = "";
    mem_dump = "";

    printf("0x%04x:\t", reg_pc);
    uint8_t instr = load8(reg_pc);
    printf("0x%02x =>\t", instr);

    execute(instr);
    std::cout << debug_instr << std::endl;

    reg_pc++;
    
    // max PC value
    if(reg_pc >= 0xffff){
        exit(0);
    }

    // TODO: move to a debugger class
    // debug
    if(brk == true){
        // TODO: print stack values as well
        printf("\n<====BREAKPOINT====>\n");
        printf("Registers\n");
        printf("A: 0x%02x\n", a);
        printf("B: 0x%02x\n", b);
        printf("C: 0x%02x\n", c);
        printf("D: 0x%02x\n", d);
        printf("E: 0x%02x\n", e);
        printf("F: 0x%02x\n", f);
        printf("H: 0x%02x\n", h);
        printf("L: 0x%02x\n", l);
        printf("PC: 0x%04x\n", reg_pc);
        printf("SP: 0x%04x\n", reg_sp);

        printf("AF: 0x%04x\n", af->get());
        printf("BC: 0x%04x\n", bc->get());
        printf("DE: 0x%04x\n", de->get());
        printf("HL: 0x%04x\n", hl->get());

        printf("\nFlags\n");
        printf("Z: %d\n", flag->flag_zero());
        printf("N: %d\n", flag->flag_subtract());
        printf("H: %d\n", flag->flag_half_carry());
        printf("C: %d\n", flag->flag_carry());

        for(int i=0; i <= MEMSIZE - 16; i += 16){
            mem_dump.append(string_format("0x%05x:\t", i));
            for(int j=i; j < i+16; j++){
                mem_dump.append(string_format("0x%02x ", memory_ptr[j]));
            }
            mem_dump.append("\n");
        }
        memdump_file.open("mem_dump.log");
        memdump_file << mem_dump;
        memdump_file.close();
        printf("\nMemory Dumped at mem_dump.log\n");
        //exit(0);
        system("pause");
    }
}

// TODO: this should return the number of cycles
// which will reside in an array of 255 elements
// example: return cycles[instr];
// if opcode not supported return 0 or exit() (inside switch)
void CPU::execute(uint8_t instr){
    switch(instr){
        case 0x00:
            op_00();
            break;
        case 0x01:
            op_01();
            break;
        case 0x02:
            op_02();
            break;
        case 0x03:
            op_03();
            break;
        case 0x04:
            op_04();
            break;
        case 0x05:
            op_05();
            break;
        case 0x06:
            op_06();
            break;
        case 0x07:
            op_07();
            break;
        case 0x08:
            op_08();
            break;
        case 0x09:
            op_09();
            break;
        case 0x0A:
            op_0A();
            break;
        case 0x0B:
            op_0B();
            break;
        case 0x0C:
            op_0C();
            break;
        case 0x0D:
            op_0D();
            break;
        case 0x0E:
            op_0E();
            break;
        case 0x0F:
            op_0F();
            break;
        case 0x10:
            op_10();
            break;
        case 0x11:
            op_11();
            break;
        case 0x12:
            op_12();
            break;
        case 0x13:
            op_13();
            break;
        case 0x14:
            op_14();
            break;
        case 0x15:
            op_15();
            break;
        case 0x16:
            op_16();
            break;
        case 0x17:
            op_17();
            break;
        case 0x18:
            op_18();
            break;
        case 0x19:
            op_19();
            break;
        case 0x1A:
            op_1A();
            break;
        case 0x1B:
            op_1B();
            break;
        case 0x1C:
            op_1C();
            break;
        case 0x1D:
            op_1D();
            break;
        case 0x1E:
            op_1E();
            break;
        case 0x1F:
            op_1F();
            break;
        case 0x20:
            op_20();
            break;
        case 0x21:
            op_21();
            break;
        case 0x22:
            op_22();
            break;
        case 0x23:
            op_23();
            break;
        case 0x24:
            op_24();
            break;
        case 0x25:
            op_25();
            break;
        case 0x26:
            op_26();
            break;
        case 0x27:
            op_27();
            break;
        case 0x28:
            op_28();
            break;
        case 0x29:
            op_29();
            break;
        case 0x2A:
            op_2A();
            break;
        case 0x2B:
            op_2B();
            break;
        case 0x2C:
            op_1C();
            break;
        case 0x2D:
            op_2D();
            break;
        case 0x2E:
            op_2E();
            break;
        case 0x30:
            op_30();
            break;
        case 0x31:
            op_31();
            break;
        case 0x32:
            op_32();
            break;
        case 0x33:
            op_33();
            break;
        case 0x34:
            op_34();
            break;
        case 0x35:
            op_35();
            break;
        case 0x36:
            op_36();
            break;
        case 0x37:
            op_37();
            break;
        case 0x38:
            op_38();
            break;
        case 0x39:
            op_39();
            break;
        case 0x3A:
            op_3A();
            break;
        case 0x3B:
            op_3B();
            break;
        case 0x3C:
            op_3C();
            break;
        case 0x3D:
            op_3D();
            break;
        case 0x3E:
            op_3E();
            break;
        case 0x3F:
            op_3F();
            break;
        case 0x40:
            op_40();
            break;
        case 0x41:
            op_41();
            break;
        case 0x42:
            op_42();
            break;
        case 0x43:
            op_43();
            break;
        case 0x44:
            op_44();
            break;
        case 0x45:
            op_45();
            break;
        case 0x46:
            op_46();
            break;
        case 0x47:
            op_47();
            break;
        case 0x48:
            op_48();
            break;
        case 0x49:
            op_49();
            break;
        case 0x4A:
            op_4A();
            break;
        case 0x4B:
            op_4B();
            break;
        case 0x4C:
            op_4C();
            break;
        case 0x4D:
            op_4D();
            break;
        case 0x4E:
            op_4E();
            break;
        case 0x4F:
            op_4F();
            break;
        case 0x50:
            op_50();
            break;
        case 0x51:
            op_51();
            break;
        case 0x52:
            op_52();
            break;
        case 0x53:
            op_53();
            break;
        case 0x54:
            op_54();
            break;
        case 0x55:
            op_55();
            break;
        case 0x56:
            op_56();
            break;
        case 0x57:
            op_57();
            break;
        case 0x58:
            op_58();
            break;
        case 0x59:
            op_59();
            break;
        case 0x5A:
            op_5A();
            break;
        case 0x5B:
            op_5B();
            break;
        case 0x5C:
            op_5C();
            break;
        case 0x5D:
            op_5D();
            break;
        case 0x5E:
            op_5E();
            break;
        case 0x5F:
            op_5F();
            break;
        case 0x60:
            op_60();
            break;
        case 0x61:
            op_61();
            break;
        case 0x62:
            op_62();
            break;
        case 0x63:
            op_63();
            break;
        case 0x64:
            op_64();
            break;
        case 0x65:
            op_65();
            break;
        case 0x66:
            op_66();
            break;
        case 0x67:
            op_67();
            break;
        case 0x68:
            op_68();
            break;
        case 0x69:
            op_69();
            break;
        case 0x6A:
            op_6A();
            break;
        case 0x6B:
            op_6B();
            break;
        case 0x6C:
            op_6C();
            break;
        case 0x6D:
            op_6D();
            break;
        case 0x6E:
            op_6E();
            break;
        case 0x6F:
            op_6F();
            break;
        case 0x70:
            op_70();
            break;
        case 0x71:
            op_71();
            break;
        case 0x72:
            op_72();
            break;
        case 0x73:
            op_73();
            break;
        case 0x74:
            op_74();
            break;
        case 0x75:
            op_75();
            break;
        case 0x76:
            op_76();
            break;
        case 0x77:
            op_77();
            break;
        case 0x78:
            op_78();
            break;
        case 0x79:
            op_79();
            break;
        case 0x7A:
            op_7A();
            break;
        case 0x7B:
            op_7B();
            break;
        case 0x7C:
            op_7C();
            break;
        case 0x7D:
            op_7D();
            break;
        case 0x7E:
            op_7E();
            break;
        case 0x7F:
            op_7F();
            break;
        case 0x80:
            op_80();
            break;
        case 0x81:
            op_81();
            break;
        case 0x82:
            op_82();
            break;
        case 0x83:
            op_83();
            break;
        case 0x84:
            op_84();
            break;
        case 0x85:
            op_85();
            break;
        case 0x86:
            op_86();
            break;
        case 0x87:
            op_87();
            break;
        case 0x88:
            op_88();
            break;
        case 0x89:
            op_89();
            break;
        case 0x8A:
            op_8A();
            break;
        case 0x8B:
            op_8B();
            break;
        case 0x8C:
            op_8C();
            break;
        case 0x8D:
            op_8D();
            break;
        case 0x8E:
            op_8E();
            break;
        case 0x8F:
            op_8F();
            break;
        case 0x90:
            op_90();
            break;
        case 0x91:
            op_91();
            break;
        case 0x92:
            op_92();
            break;
        case 0x93:
            op_93();
            break;
        case 0x94:
            op_94();
            break;
        case 0x95:
            op_95();
            break;
        case 0x96:
            op_96();
            break;
        case 0x97:
            op_97();
            break;
        case 0x98:
            op_98();
            break;
        case 0x99:
            op_99();
            break;
        case 0x9A:
            op_9A();
            break;
        case 0x9B:
            op_9B();
            break;
        case 0x9C:
            op_9C();
            break;
        case 0x9D:
            op_9D();
            break;
        case 0x9E:
            op_9E();
            break;
        case 0x9F:
            op_9F();
            break;
        case 0xA0:
            op_A0();
            break;
        case 0xA1:
            op_A1();
            break;
        case 0xA2:
            op_A2();
            break;
        case 0xA3:
            op_A3();
            break;
        case 0xA4:
            op_A4();
            break;
        case 0xA5:
            op_A5();
            break;
        case 0xA6:
            op_A6();
            break;
        case 0xA7:
            op_A7();
            break;
        case 0xA8:
            op_A8();
            break;
        case 0xA9:
            op_A9();
            break;
        case 0xAA:
            op_AA();
            break;
        case 0xAB:
            op_AB();
            break;
        case 0xAC:
            op_AC();
            break;
        case 0xAD:
            op_AD();
            break;
        case 0xAE:
            op_AE();
            break;
        case 0xAF:
            op_AF();
            break;
        case 0xB0:
            op_B0();
            break;
        case 0xB1:
            op_B1();
            break;
        case 0xB2:
            op_B2();
            break;
        case 0xB3:
            op_B3();
            break;
        case 0xB4:
            op_B4();
            break;
        case 0xB5:
            op_B5();
            break;
        case 0xB6:
            op_B6();
            break;
        case 0xB7:
            op_B7();
            break;
        case 0xB8:
            op_B8();
            break;
        case 0xB9:
            op_B9();
            break;
        case 0xBA:
            op_BA();
            break;
        case 0xBB:
            op_BB();
            break;
        case 0xBC:
            op_BC();
            break;
        case 0xBD:
            op_BD();
            break;
        case 0xBE:
            op_BE();
            break;
        case 0xBF:
            op_BF();
            break;
        case 0xC0:
            op_C0();
            break;
        case 0xC1:
            op_C1();
            break;
        case 0xC2:
            op_C2();
            break;
        case 0xC3:
            op_C3();
            break;
        case 0xC4:
            op_C4();
            break;
        case 0xC5:
            op_C5();
            break;
        case 0xC6:
            op_C6();
            break;
        case 0xC7:
            op_C7();
            break;
        case 0xC8:
            op_C8();
            break;
        case 0xC9:
            op_C9();
            break;
        case 0xCA:
            op_CA();
            break;
        case 0xCB:
            op_CB();
            break;
        case 0xCC:
            op_CC();
            break;
        case 0xCD:
            op_CD();
            break;
        case 0xCE:
            op_CE();
            break;
        case 0xCF:
            op_CF();
            break;
        case 0xD0:
            op_D0();
            break;
        case 0xD1:
            op_D1();
            break;
        case 0xD2:
            op_D2();
            break;
        case 0xD3:
            op_D3();
            break;
        case 0xD4:
            op_D4();
            break;
        case 0xD5:
            op_D5();
            break;
        case 0xD6:
            op_D6();
            break;
        case 0xD7:
            op_D7();
            break;
        case 0xD8:
            op_D8();
            break;
        case 0xD9:
            op_D9();
            break;
        case 0xDA:
            op_DA();
            break;
        case 0xDB:
            op_DB();
            break;
        case 0xDC:
            op_DC();
            break;
        case 0xDD:
            op_DD();
            break;
        case 0xDE:
            op_DE();
            break;
        case 0xDF:
            op_DF();
            break;
        case 0xE0:
            op_E0();
            break;
        case 0xE1:
            op_E1();
            break;
        case 0xE2:
            op_E2();
            break;
        case 0xE3:
            op_E3();
            break;
        case 0xE4:
            op_E4();
            break;
        case 0xE5:
            op_E5();
            break;
        case 0xE6:
            op_E6();
            break;
        case 0xE7:
            op_E7();
            break;
        case 0xE8:
            op_E8();
            break;
        case 0xE9:
            op_E9();
            break;
        case 0xEA:
            op_EA();
            break;
        case 0xEB:
            op_EB();
            break;
        case 0xEC:
            op_EC();
            break;
        case 0xED:
            op_ED();
            break;
        case 0xEE:
            op_EE();
            break;
        case 0xEF:
            op_EF();
            break;
        case 0xF0:
            op_F0();
            break;
        case 0xF1:
            op_F1();
            break;
        case 0xF2:
            op_F2();
            break;
        case 0xF3:
            op_F3();
            break;
        case 0xF4:
            op_F4();
            break;
        case 0xF5:
            op_F5();
            break;
        case 0xF6:
            op_F6();
            break;
        case 0xF7:
            op_F7();
            break;
        case 0xF8:
            op_F8();
            break;
        case 0xF9:
            op_F9();
            break;
        case 0xFA:
            op_FA();
            break;
        case 0xFB:
            op_FB();
            break;
        case 0xFC:
            op_FC();
            break;
        case 0xFD:
            op_FD();
            break;
        case 0xFE:
            op_FE();
            break;
        case 0xFF:
            op_FF();
            break;
        default:
            printf("Opcode not supported\n");
            break;
    }
}

uint8_t CPU::mem_load8(uint16_t offset){
    size_t off = (size_t)offset;
    if(offset < 8*1024)
        return memory_ptr[off];

    return 0x00;
}

uint16_t CPU::mem_load16(uint16_t offset){
    size_t off = (size_t)offset;
    if(offset < 8*1024)
        return memory_ptr[off] + (memory_ptr[off+1] << 8);

    return 0x0000;
}

void CPU::mem_store8(uint16_t offset, uint8_t data){
    size_t off = (size_t)offset;
    if(offset < 8*1024)
        memory_ptr[off] = data;
}

void CPU::mem_store16(uint16_t offset, uint16_t data){
    size_t off = (size_t)offset;
    if(offset < 8*1024){
        memory_ptr[off] = (uint8_t) (data & 0xf0);
        memory_ptr[off+1] = (uint8_t) (data >> 8);
    }
}

void CPU::store8(uint16_t addr, uint8_t data){
    // TODO: check if addr is aligned

    // TODO: we are currently using just one big junk of memory, but later it needs to utilize the memory map
    //if(uint16_t *offset = map::ROM_bank0->contains(addr)){
    //
    //}
    // TODO: this is temporary since memory map is not finished

    mem_store8(addr, data);
}

void CPU::store16(uint16_t addr, uint16_t data){
    // TODO: check if addr is aligned

    // TODO: we are currently using just one big junk of memory, but later it needs to utilize the memory map
    //if(uint16_t *offset = map::ROM_bank0->contains(addr)){
    //
    //}
    // TODO: this is temporary since memory map is not finished

    mem_store16(addr, data);
}

uint8_t CPU::load8(uint16_t addr){

    // TODO: check if addr is aligned

    // TODO: we are currently using just one big junk of memory, but later it needs to utilize the memory map
    //if(uint16_t *offset = map::ROM_bank0->contains(addr)){
    //
    //}

    return mem_load8(addr);
}

uint16_t CPU::load16(uint16_t addr){

    // TODO: check if addr is aligned

    // TODO: we are currently using just one big junk of memory, but later it needs to utilize the memory map
    //if(uint16_t *offset = map::ROM_bank0->contains(addr)){
    //
    //}

    return mem_load16(addr);
}

uint8_t CPU::rst_addr(uint8_t opcode){
  uint8_t ret;

  switch(opcode){
    case 0xc7:
      ret = 0x00;
    case 0xcf:
      ret = 0x08;
      break;
    case 0xd7:
      ret = 0x10;
      break;
    case 0xdf:
      ret = 0x18;
      break;
    case 0xe7:
      ret = 0x20;
      break;
    case 0xef:
      ret = 0x28;
      break;
    case 0xf7:
      ret = 0x30;
      break;
    case 0xff:
      ret = 0x38;
      break;
    default:
      ret = 0x00;
      break;
  }

  return ret;
}

// All opcodes
void CPU::op_00(){
    op_nop();
}

void CPU::op_01(){
  uint16_t addr_lo = (uint16_t)load8(++reg_pc);
  uint16_t addr_hi = (uint16_t)(load8(++reg_pc)) << 8;
  uint16_t addr = addr_hi + addr_lo;
  op_ld(addr, bc);
  debug_instr.append(string_format("BC, Imm16:0x%04x", addr));
}

void CPU::op_02(){
  uint16_t addr = bc->get();
  op_ld(&a, addr);
  debug_instr.append("(BC), A");
}

void CPU::op_03(){
  op_inc(bc);
  debug_instr.append("BC");
}

void CPU::op_04(){
  op_inc(&b);
  debug_instr.append("B");
}

void CPU::op_05(){
  op_dec(&b);
  debug_instr.append("B");
}

void CPU::op_06(){
  uint8_t addr = load8(++reg_pc);
  op_ld(addr, &b);
  debug_instr.append(string_format("B, Imm8:0x%02x", addr));
}

void CPU::op_07(){
  op_rlca();
  debug_instr.append("A");
}

void CPU::op_08(){
  uint16_t addr_lo = (uint16_t)load8(++reg_pc);
  uint16_t addr_hi = (uint16_t)(load8(++reg_pc)) << 8;
  uint16_t addr = addr_hi + addr_lo;
  op_ld(&reg_sp, addr);
  debug_instr.append(string_format("(Imm16:0x%04x), SP", addr));
}

void CPU::op_09(){
  op_add(hl, bc);
  debug_instr.append("HL, BC");
}

void CPU::op_0A(){
  uint16_t addr = bc->get();
  op_ld(addr, &a);
  debug_instr.append("A, (BC)");
}

void CPU::op_0B(){
    op_dec(bc);
    debug_instr.append("BC");
}

void CPU::op_0C(){
    op_inc(&c);
    debug_instr.append("C");
}

void CPU::op_0D(){
    op_dec(&c);
    debug_instr.append("C");
}

void CPU::op_0E(){
  uint8_t addr = load8(++reg_pc);
  op_ld(addr, &c);
  debug_instr.append(string_format("C, Imm8:0x%02x", addr));
}

void CPU::op_0F(){
    op_rrca();
    debug_instr.append("A");
}

void CPU::op_10(){
    op_stop();
}

void CPU::op_11(){
  uint16_t addr_lo = (uint16_t)load8(++reg_pc);
  uint16_t addr_hi = (uint16_t)(load8(++reg_pc)) << 8;
  uint16_t addr = addr_hi + addr_lo;
  op_ld(addr, de);
  debug_instr.append(string_format("DE, Imm16:0x%04x", addr));
}

void CPU::op_12(){
  uint16_t addr = de->get();
  op_ld(&a, addr);
  debug_instr.append("(DE), A");
}

void CPU::op_13(){
    op_inc(de);
    debug_instr.append("DE");
}

void CPU::op_14(){
    op_inc(&d);
    debug_instr.append("D");
}

void CPU::op_15(){
    op_dec(&d);
    debug_instr.append("D");
}

void CPU::op_16(){
  uint8_t addr = load8(++reg_pc);
  op_ld(addr, &d);
  debug_instr.append(string_format("D, Imm8:0x%02x", addr));
}

void CPU::op_17(){
    op_rla();
    debug_instr.append("A");
}

void CPU::op_18(){
  int16_t addr = load8(++reg_pc);
  op_jr(addr);
  debug_instr.append("Imm8:0x%02x", addr);
}

void CPU::op_19(){
    op_add(hl, de);
    debug_instr.append("HL, DE");
}

void CPU::op_1A(){
  uint16_t addr = de->get();
  op_ld(addr, &a);
  debug_instr.append("A, (DE)");
}

void CPU::op_1B(){
    op_dec(de);
    debug_instr.append("DE");
}

void CPU::op_1C(){
    op_inc(&e);
    debug_instr.append("E");
}

void CPU::op_1D(){
    op_dec(&e);
    debug_instr.append("E");
}

void CPU::op_1E(){
  uint8_t addr = load8(++reg_pc);
  op_ld(addr, &e);
  debug_instr.append(string_format("E, Imm8:0x%02x", addr));
}

void CPU::op_1F(){
    op_rra();
    debug_instr.append("A");
}

void CPU::op_20(){
  int16_t addr = load8(++reg_pc);
  op_jr(Condition::NZ, addr);
  debug_instr.append("NZ, Imm8:0x%02x", addr);
}

void CPU::op_21(){
  uint16_t addr_lo = (uint16_t)load8(++reg_pc);
  uint16_t addr_hi = (uint16_t)(load8(++reg_pc)) << 8;
  uint16_t addr = addr_hi + addr_lo;
  op_ld(addr, hl);
  debug_instr.append(string_format("HL, Imm16:0x%04x", addr));
}

void CPU::op_22(){
  uint16_t addr = (hl->get()) + 1;
  op_ld(&a, addr);
  debug_instr.append("(HL+), A");
}

void CPU::op_23(){
    op_inc(hl);
    debug_instr.append("HL");
}

void CPU::op_24(){
    op_inc(&h);
    debug_instr.append("H");
}

void CPU::op_25(){
    op_dec(&h);
    debug_instr.append("H");
}

void CPU::op_26(){
  uint8_t addr = load8(++reg_pc);
  op_ld(addr, &h);
  debug_instr.append(string_format("H, Imm8:0x%02x", addr));
}

void CPU::op_27(){
    op_daa();
}

void CPU::op_28(){
  int16_t addr = load8(++reg_pc);
  op_jr(Condition::Z, addr);
  debug_instr.append("Z, Imm8:0x%02x", addr);
}

void CPU::op_29(){
    op_add(hl, hl);
    debug_instr.append("HL, HL");
}

void CPU::op_2A(){
  uint16_t addr = (hl->get()) + 1;
  op_ld(addr, &a);
  debug_instr.append("A, (HL+)");
}

void CPU::op_2B(){
    op_dec(hl);
    debug_instr.append("hl");
}

void CPU::op_2C(){
    op_inc(&l);
    debug_instr.append("L");
}

void CPU::op_2D(){
    op_dec(&l);
    debug_instr.append("L");
}

void CPU::op_2E(){
  uint8_t addr = load8(++reg_pc);
  op_ld(addr, &l);
  debug_instr.append(string_format("L, Imm8:0x%02x", addr));
}

void CPU::op_2F(){
    op_cpl();
}

void CPU::op_30(){
  int16_t addr = load8(++reg_pc);
  op_jr(Condition::NC, addr);
  debug_instr.append("NC, Imm8:0x%02x", addr);
}

void CPU::op_31(){
  uint16_t addr_lo = (uint16_t)load8(++reg_pc);
  uint16_t addr_hi = (uint16_t)(load8(++reg_pc)) << 8;
  uint16_t addr = addr_hi + addr_lo;
  op_ld(addr, &reg_sp);
  debug_instr.append(string_format("SP, Imm16:0x%04x", addr));
}

void CPU::op_32(){
  uint16_t addr = (hl->get()) - 1;
  op_ld(&a, addr);
  debug_instr.append("(HL-), A");
}

void CPU::op_33(){
    op_inc(&reg_sp);
    debug_instr.append("SP");
}

void CPU::op_34(){
    op_inc(hl->get());
    debug_instr.append("(HL)");
}

void CPU::op_35(){
    op_dec(hl->get());
    debug_instr.append("(HL)");
}

void CPU::op_36(){
  uint8_t addr = load8(++reg_pc);
  op_ld(addr, hl->get());
  debug_instr.append(string_format("(HL), Imm8:0x%02x", addr));
}

void CPU::op_37(){
  op_scf();
}

void CPU::op_38(){
  int16_t addr = load8(++reg_pc);
  op_jr(Condition::C, addr);
  debug_instr.append("C, Imm8:0x%02x", addr);
}

void CPU::op_39(){
    op_add(hl, &reg_sp);
    debug_instr.append("HL, SP");
}

void CPU::op_3A(){
  uint16_t addr = (hl->get()) - 1;
  op_ld(addr, &a);
  debug_instr.append("A, (HL-)");
}

void CPU::op_3B(){
    op_dec(&reg_sp);
    debug_instr.append("SP");
}

void CPU::op_3C(){
    op_inc(&a);
    debug_instr.append("A");
}

void CPU::op_3D(){
    op_dec(&a);
    debug_instr.append("A");
}

void CPU::op_3E(){
  uint8_t addr = load8(++reg_pc);
  op_ld(addr, &a);
  debug_instr.append(string_format("A, Imm8:0x%02x", addr));
}

void CPU::op_3F(){
    op_ccf();
}

void CPU::op_40(){
  op_ld(&b, &b);
  debug_instr.append("B, B");
}

void CPU::op_41(){
  op_ld(&c, &b);
  debug_instr.append("B, C");
}

void CPU::op_42(){
  op_ld(&d, &b);
  debug_instr.append("B, D");
}

void CPU::op_43(){
  op_ld(&e, &b);
  debug_instr.append("B, E");
}

void CPU::op_44(){
  op_ld(&h, &b);
  debug_instr.append("B, H");
}

void CPU::op_45(){
  op_ld(&l, &b);
  debug_instr.append("B, L");
}

void CPU::op_46(){
  op_ld(hl->get(), &b);
  debug_instr.append("B, (HL)");
}

void CPU::op_47(){
  op_ld(&a, &b);
  debug_instr.append("B, A");
}

void CPU::op_48(){
  op_ld(&b, &c);
  debug_instr.append("C, B");
}

void CPU::op_49(){
  op_ld(&c, &c);
  debug_instr.append("C, C");
}

void CPU::op_4A(){
  op_ld(&d, &c);
  debug_instr.append("C, D");
}

void CPU::op_4B(){
  op_ld(&e, &c);
  debug_instr.append("C, E");
}

void CPU::op_4C(){
  op_ld(&h, &c);
  debug_instr.append("C, H");
}

void CPU::op_4D(){
  op_ld(&l, &c);
  debug_instr.append("C, L");
}

void CPU::op_4E(){
  op_ld(hl->get(), &c);
  debug_instr.append("C, (HL)");
}

void CPU::op_4F(){
  op_ld(&a, &c);
  debug_instr.append("C, A");
}

void CPU::op_50(){
  op_ld(&b, &d);
  debug_instr.append("D, B");
}

void CPU::op_51(){
  op_ld(&c, &d);
  debug_instr.append("D, C");
}

void CPU::op_52(){
  op_ld(&d, &d);
  debug_instr.append("D, D");
}

void CPU::op_53(){
  op_ld(&e, &d);
  debug_instr.append("D, E");
}

void CPU::op_54(){
  op_ld(&h, &d);
  debug_instr.append("D, H");
}

void CPU::op_55(){
  op_ld(&l, &d);
  debug_instr.append("D, L");
}

void CPU::op_56(){
  op_ld(hl->get(), &d);
  debug_instr.append("D, (HL)");
}

void CPU::op_57(){
  op_ld(&a, &d);
  debug_instr.append("D, A");
}

void CPU::op_58(){
  op_ld(&b, &e);
  debug_instr.append("E, B");
}

void CPU::op_59(){
  op_ld(&c, &e);
  debug_instr.append("E, C");
}

void CPU::op_5A(){
  op_ld(&d, &e);
  debug_instr.append("E, D");
}

void CPU::op_5B(){
  op_ld(&e, &e);
  debug_instr.append("E, E");
}

void CPU::op_5C(){
  op_ld(&h, &e);
  debug_instr.append("E, H");
}

void CPU::op_5D(){
  op_ld(&l, &e);
  debug_instr.append("E, L");
}

void CPU::op_5E(){
  op_ld(hl->get(), &e);
  debug_instr.append("E, (HL)");
}

void CPU::op_5F(){
  op_ld(&a, &e);
  debug_instr.append("E, A");
}

void CPU::op_60(){
  op_ld(&b, &h);
  debug_instr.append("H, B");
}

void CPU::op_61(){
  op_ld(&c, &h);
  debug_instr.append("H, C");
}

void CPU::op_62(){
  op_ld(&d, &h);
  debug_instr.append("H, D");
}

void CPU::op_63(){
  op_ld(&e, &h);
  debug_instr.append("H, E");
}

void CPU::op_64(){
  op_ld(&h, &h);
  debug_instr.append("H, H");
}

void CPU::op_65(){
  op_ld(&l, &h);
  debug_instr.append("H, L");
}

void CPU::op_66(){
  op_ld(hl->get(), &h);
  debug_instr.append("H, (HL)");
}

void CPU::op_67(){
  op_ld(&a, &h);
  debug_instr.append("H, A");
}

void CPU::op_68(){
  op_ld(&b, &l);
  debug_instr.append("L, B");
}

void CPU::op_69(){
  op_ld(&c, &l);
  debug_instr.append("L, C");
}

void CPU::op_6A(){
  op_ld(&d, &l);
  debug_instr.append("L, D");
}

void CPU::op_6B(){
  op_ld(&e, &l);
  debug_instr.append("L, E");
}

void CPU::op_6C(){
  op_ld(&h, &l);
  debug_instr.append("L, H");
}

void CPU::op_6D(){
  op_ld(&l, &l);
  debug_instr.append("L, L");
}

void CPU::op_6E(){
  op_ld(hl->get(), &l);
  debug_instr.append("L, (HL)");
}

void CPU::op_6F(){
  op_ld(&a, &l);
  debug_instr.append("L, A");
}

void CPU::op_70(){
  op_ld(&b, hl->get());
  debug_instr.append("(HL), B");
}

void CPU::op_71(){
  op_ld(&c, hl->get());
  debug_instr.append("(HL), C");
}

void CPU::op_72(){
  op_ld(&d, hl->get());
  debug_instr.append("(HL), D");
}

void CPU::op_73(){
  op_ld(&e, hl->get());
  debug_instr.append("(HL), E");
}

void CPU::op_74(){
  op_ld(&h, hl->get());
  debug_instr.append("(HL), H");
}

void CPU::op_75(){
  op_ld(&l, hl->get());
  debug_instr.append("(HL), L");
}

void CPU::op_76(){
  op_halt();
}

void CPU::op_77(){
  op_ld(&a, hl->get());
  debug_instr.append("(HL), A");
}

void CPU::op_78(){
  op_ld(&b, &a);
  debug_instr.append("A, B");
}

void CPU::op_79(){
  op_ld(&c, &a);
  debug_instr.append("A, C");
}

void CPU::op_7A(){
  op_ld(&d, &a);
  debug_instr.append("A, D");
}

void CPU::op_7B(){
  op_ld(&e, &a);
  debug_instr.append("A, E");
}

void CPU::op_7C(){
  op_ld(&h, &a);
  debug_instr.append("A, H");
}

void CPU::op_7D(){
  op_ld(&l, &a);
  debug_instr.append("A, L");
}

void CPU::op_7E(){
  op_ld(hl->get(), &a);
  debug_instr.append("A, (HL)");
}

void CPU::op_7F(){
  op_ld(&a, &a);
  debug_instr.append("A, A");
}

void CPU::op_80(){
    op_add(&a, &b);
    debug_instr.append("A, B");
}

void CPU::op_81(){
    op_add(&a, &c);
    debug_instr.append("A, C");
}

void CPU::op_82(){
    op_add(&a, &d);
    debug_instr.append("A, D");
}

void CPU::op_83(){
    op_add(&a, &e);
    debug_instr.append("A, E");
}

void CPU::op_84(){
    op_add(&a, &h);
    debug_instr.append("A, H");
}

void CPU::op_85(){
    op_add(&a, &l);
    debug_instr.append("A, L");
}

void CPU::op_86(){
  uint8_t val = load8(hl->get());
  op_add(&a, &val);
  debug_instr.append("A, (HL)");
}

void CPU::op_87(){
    op_add(&a, &a);
    debug_instr.append("A, A");
}

void CPU::op_88(){
    op_adc(&b);
    debug_instr.append("A, B");
}

void CPU::op_89(){
    op_adc(&c);
    debug_instr.append("A, C");
}

void CPU::op_8A(){
    op_adc(&d);
    debug_instr.append("A, D");
}

void CPU::op_8B(){
    op_adc(&e);
    debug_instr.append("A, E");
}

void CPU::op_8C(){
    op_adc(&h);
    debug_instr.append("A, H");
}

void CPU::op_8D(){
    op_adc(&l);
    debug_instr.append("A, L");
}

void CPU::op_8E(){
  uint8_t val = load8(hl->get());
  op_adc(&val);
  debug_instr.append("A, (HL)");
}

void CPU::op_8F(){
    op_adc(&a);
    debug_instr.append("A, A");
}

void CPU::op_90(){
    op_sub(&a, &b);
    debug_instr.append("A, B");
}

void CPU::op_91(){
    op_sub(&a, &c);
    debug_instr.append("A, C");
}

void CPU::op_92(){
    op_sub(&a, &d);
    debug_instr.append("A, D");
}

void CPU::op_93(){
    op_sub(&a, &e);
    debug_instr.append("A, E");
}

void CPU::op_94(){
    op_sub(&a, &h);
    debug_instr.append("A, H");
}

void CPU::op_95(){
    op_sub(&a, &l);
    debug_instr.append("A, L");
}

void CPU::op_96(){
  uint8_t val = load8(hl->get());
  op_sub(&a, &val);
  debug_instr.append("A, (HL)");
}

void CPU::op_97(){
    op_sub(&a, &a);
    debug_instr.append("A, A");
}

void CPU::op_98(){
    op_sbc(&b);
    debug_instr.append("A, B");
}

void CPU::op_99(){
    op_sbc(&c);
    debug_instr.append("A, C");
}

void CPU::op_9A(){
    op_sbc(&d);
    debug_instr.append("A, D");
}

void CPU::op_9B(){
    op_sbc(&e);
    debug_instr.append("A, E");
}

void CPU::op_9C(){
    op_sbc(&h);
    debug_instr.append("A, H");
}

void CPU::op_9D(){
    op_sbc(&l);
    debug_instr.append("A, L");
}

void CPU::op_9E(){
  uint8_t val = load8(hl->get());
  op_sbc(&val);
  debug_instr.append("A, (HL)");
}

void CPU::op_9F(){
    op_sbc(&a);
    debug_instr.append("A, A");
}

void CPU::op_A0(){
    op_and(&b);
    debug_instr.append("A, B");
}

void CPU::op_A1(){
    op_and(&c);
    debug_instr.append("A, C");
}

void CPU::op_A2(){
    op_and(&d);
    debug_instr.append("A, D");
}

void CPU::op_A3(){
    op_and(&e);
    debug_instr.append("A, E");
}

void CPU::op_A4(){
    op_and(&h);
    debug_instr.append("A, H");
}

void CPU::op_A5(){
    op_and(&l);
    debug_instr.append("A, L");
}

void CPU::op_A6(){
  uint8_t val = load8(hl->get());
  op_and(&val);
  debug_instr.append("A, (HL)");
}

void CPU::op_A7(){
    op_and(&a);
    debug_instr.append("A, A");
}

void CPU::op_A8(){
    op_xor(&b);
    debug_instr.append("A, B");
}

void CPU::op_A9(){
    op_xor(&c);
    debug_instr.append("A, C");
}

void CPU::op_AA(){
    op_xor(&d);
    debug_instr.append("A, D");
}

void CPU::op_AB(){
    op_xor(&e);
    debug_instr.append("A, E");
}

void CPU::op_AC(){
    op_xor(&h);
    debug_instr.append("A, H");
}

void CPU::op_AD(){
    op_xor(&l);
    debug_instr.append("A, L");
}

void CPU::op_AE(){
    op_xor(&e);
    debug_instr.append("A, (HL)");
}

void CPU::op_AF(){
    op_xor(&a);
    debug_instr.append("A, A");
}

void CPU::op_B0(){
    op_or(&b);
    debug_instr.append("A, B");
}

void CPU::op_B1(){
    op_or(&c);
    debug_instr.append("A, C");
}

void CPU::op_B2(){
    op_or(&d);
    debug_instr.append("A, D");
}

void CPU::op_B3(){
    op_or(&e);
    debug_instr.append("A, E");
}

void CPU::op_B4(){
    op_or(&h);
    debug_instr.append("A, H");
}

void CPU::op_B5(){
    op_or(&l);
    debug_instr.append("A, L");
}

void CPU::op_B6(){
    op_or(&e);
    debug_instr.append("A, (HL)");
}

void CPU::op_B7(){
    op_or(&l);
    debug_instr.append("A, A");
}

void CPU::op_B8(){
    op_cp(&b);
    debug_instr.append("A, B");
}

void CPU::op_B9(){
    op_cp(&c);
    debug_instr.append("A, C");
}

void CPU::op_BA(){
    op_cp(&d);
    debug_instr.append("A, D");
}

void CPU::op_BB(){
    op_cp(&e);
    debug_instr.append("A, E");
}

void CPU::op_BC(){
    op_cp(&h);
    debug_instr.append("A, H");
}

void CPU::op_BD(){
    op_cp(&l);
    debug_instr.append("A, L");
}

void CPU::op_BE(){
    op_cp(&e);
    debug_instr.append("A, (HL)");
}

void CPU::op_BF(){
    op_cp(&a);
    debug_instr.append("A, A");
}

void CPU::op_C0(){
  op_ret(Condition::NZ);
  debug_instr.append("NZ");
}

void CPU::op_C1(){
  op_pop(bc);
  debug_instr.append("BC");
}

void CPU::op_C2(){
  uint8_t addr_lo = load8(++reg_pc);
  uint8_t addr_hi = load8(++reg_pc);
  uint16_t addr = (uint16_t)(addr_hi << 8) + (uint16_t)addr_lo;
  op_jp(Condition::NZ, addr);
  debug_instr.append(string_format("NZ, Imm16:0x%04x", addr));
}

void CPU::op_C3(){
  uint8_t addr_lo = load8(++reg_pc);
  uint8_t addr_hi = load8(++reg_pc);
  uint16_t addr = (uint16_t)(addr_hi << 8) + (uint16_t)addr_lo;
  op_jp(addr);
  debug_instr.append(string_format("Imm16:0x%04x", addr));
}

void CPU::op_C4(){
  uint8_t addr_lo = load8(++reg_pc);
  uint8_t addr_hi = load8(++reg_pc);
  uint16_t addr = (uint16_t)(addr_hi << 8) + (uint16_t)addr_lo;
  op_jp(Condition::NZ, addr);
  debug_instr.append(string_format("NZ, Imm16:0x%04x", addr));
}

void CPU::op_C5(){
  op_push(bc);
  debug_instr.append("BC");
}

void CPU::op_C6(){
  uint8_t imm = load8(++reg_pc);
  op_add(&a, &imm);
  debug_instr.append(string_format("A, Imm8:0x%02x", imm));
}

void CPU::op_C7(){
  op_rst(0xc7);
  debug_instr.append("00h");
}

void CPU::op_C8(){
  op_ret(Condition::Z);
  debug_instr.append("Z");
}

void CPU::op_C9(){
  op_ret();
}

void CPU::op_CA(){
  uint8_t addr_lo = load8(++reg_pc);
  uint8_t addr_hi = load8(++reg_pc);
  uint16_t addr = (uint16_t)(addr_hi << 8) + (uint16_t)addr_lo;
  op_jp(Condition::Z, addr);
  debug_instr.append(string_format("Z, Imm16:0x%04x", addr));
}

void CPU::op_CB(){
  // op_prefix()
  // TODO
}

void CPU::op_CC(){
  uint8_t addr_lo = load8(++reg_pc);
  uint8_t addr_hi = load8(++reg_pc);
  uint16_t addr = (uint16_t)(addr_hi << 8) + (uint16_t)addr_lo;
  op_jp(Condition::Z, addr);
  debug_instr.append(string_format("Z, Imm16:0x%04x", addr));
}

void CPU::op_CD(){
  uint8_t addr_lo = load8(++reg_pc);
  uint8_t addr_hi = load8(++reg_pc);
  uint16_t addr = (uint16_t)(addr_hi << 8) + (uint16_t)addr_lo;
  op_call(addr);
  debug_instr.append(string_format("Imm16:0x%04x", addr));
}

void CPU::op_CE(){
  uint8_t imm = load8(++reg_pc);
  op_adc(&imm);
  debug_instr.append(string_format("A, Imm8:0x%02x", imm));
}

void CPU::op_CF(){
  op_rst(0xcf);
  debug_instr.append("08h");
}

void CPU::op_D0(){
  op_ret(Condition::NC);
  debug_instr.append("NC");
}

void CPU::op_D1(){
  op_pop(de);
  debug_instr.append("DE");
}

void CPU::op_D2(){
  uint8_t addr_lo = load8(++reg_pc);
  uint8_t addr_hi = load8(++reg_pc);
  uint16_t addr = (uint16_t)(addr_hi << 8) + (uint16_t)addr_lo;
  op_jp(Condition::NC, addr);
  debug_instr.append(string_format("NC, Imm16:0x%04x", addr));
}

void CPU::op_D3(){

}

void CPU::op_D4(){
  uint8_t addr_lo = load8(++reg_pc);
  uint8_t addr_hi = load8(++reg_pc);
  uint16_t addr = (uint16_t)(addr_hi << 8) + (uint16_t)addr_lo;
  op_jp(Condition::NC, addr);
  debug_instr.append(string_format("NC, Imm16:0x%04x", addr));
}

void CPU::op_D5(){
  op_push(de);
  debug_instr.append("DE");
}

void CPU::op_D6(){
  uint8_t imm = load8(++reg_pc);
  op_sub(&a, &imm);
  debug_instr.append(string_format("A, Imm8:0x%02x", imm));
}

void CPU::op_D7(){
  op_rst(0xd7);
  debug_instr.append("10h");
}

void CPU::op_D8(){
  op_ret(Condition::C);
  debug_instr.append("C");
}

void CPU::op_D9(){
  op_reti();
}

void CPU::op_DA(){
  uint8_t addr_lo = load8(++reg_pc);
  uint8_t addr_hi = load8(++reg_pc);
  uint16_t addr = (uint16_t)(addr_hi << 8) + (uint16_t)addr_lo;
  op_jp(Condition::C, addr);
  debug_instr.append(string_format("C, Imm16:0x%04x", addr));
}

void CPU::op_DB(){

}

void CPU::op_DC(){
  uint8_t addr_lo = load8(++reg_pc);
  uint8_t addr_hi = load8(++reg_pc);
  uint16_t addr = (uint16_t)(addr_hi << 8) + (uint16_t)addr_lo;
  op_jp(Condition::C, addr);
  debug_instr.append(string_format("C, Imm16:0x%04x", addr));
}

void CPU::op_DD(){

}

void CPU::op_DE(){
  uint8_t imm = load8(++reg_pc);
  op_sbc(&imm);
  debug_instr.append(string_format("A, Imm8:0x%02x", imm));
}

void CPU::op_DF(){
  op_rst(0xdf);
  debug_instr.append("18h");
}

void CPU::op_E0(){
  uint16_t addr = 0xff00 + (uint16_t)load8(++reg_pc);
  op_ld(&a, addr);
  debug_instr.append(string_format("(0xFF00+Imm8:0x%02x), A", addr));
}

void CPU::op_E1(){
  op_pop(hl);
  debug_instr.append("HL");
}

void CPU::op_E2(){
  uint16_t addr = 0xff00 + (uint16_t)c;
  op_ld(&a, addr);
  debug_instr.append(string_format("(0xFF00+C:0x%02x), A", addr));
}

void CPU::op_E3(){

}

void CPU::op_E4(){

}

void CPU::op_E5(){
  op_push(hl);
  debug_instr.append("HL");
}

void CPU::op_E6(){
  uint8_t addr = load8(++reg_pc);
  op_and(&addr);
  debug_instr.append(string_format("A, Imm8:0x%02x", addr));
}

void CPU::op_E7(){
  op_rst(0xe7);
  debug_instr.append("20h");
}

void CPU::op_E8(){
  int8_t val = (int8_t)load8(++reg_pc);
  op_add(&reg_sp, &val);
  debug_instr.append(string_format("SP, Imm8:0x%02x", val));
}

void CPU::op_E9(){
  op_jp(hl);
  debug_instr.append("HL");
}

void CPU::op_EA(){
  uint8_t addr_lo = load8(++reg_pc);
  uint8_t addr_hi = load8(++reg_pc);
  uint16_t addr = (uint16_t)(addr_hi << 8) + (uint16_t)addr_lo;
  op_ld(&a, addr);
  debug_instr.append(string_format("(Imm16:0x%04x), A", addr));
}

void CPU::op_EB(){

}

void CPU::op_EC(){

}

void CPU::op_ED(){

}

void CPU::op_EE(){
  uint8_t val = load8(++reg_pc);
  op_xor(&val);
  debug_instr.append(string_format("A, Imm8:0x%02x", val));
}

void CPU::op_EF(){
  op_rst(0xef);
  debug_instr.append("28h");
}

void CPU::op_F0(){
  uint16_t addr = 0xff00 + (uint16_t)load8(++reg_pc);
  op_ld(addr, &a);
  debug_instr.append(string_format("A, (0xFF00+Imm8:0x%02x)", addr));
}

void CPU::op_F1(){
  op_pop(af);
  debug_instr.append("AF");
}

void CPU::op_F2(){
  uint16_t addr = 0xff00 + (uint16_t)c;
  op_ld(addr, &a);
  debug_instr.append(string_format("A, (0xFF00+C:0x%02x)", addr));
}

void CPU::op_F3(){
  // op_di();
}

void CPU::op_F4(){

}

void CPU::op_F5(){
  op_push(af);
  debug_instr.append("AF");
}

void CPU::op_F6(){
  uint8_t val = load8(++reg_pc);
  op_or(&val);
  debug_instr.append(string_format("A, Imm8:0x%02x", val));
}

void CPU::op_F7(){
  op_rst(0xf7);
  debug_instr.append("30h");
}

void CPU::op_F8(){
  int8_t val = (int8_t)load8(++reg_pc);
  //op_ld(reg_sp+val, hl);
  hl->set(reg_sp+val);
  debug_instr.append(string_format("LD HL, SP+Imm8:0x%02x", val));
}

void CPU::op_F9(){
  reg_sp = hl->get();
  debug_instr.append("LD SP, HL");
}

void CPU::op_FA(){
  uint16_t addr_lo = (uint16_t)load8(++reg_pc);
  uint16_t addr_hi = (uint16_t)(load8(++reg_pc)) << 8;
  uint16_t addr = addr_hi + addr_lo;
  op_ld(addr, &a);
  debug_instr.append(string_format("A, (Imm16):0x%04x", addr));
}

void CPU::op_FB(){
  // op_ei();
}

void CPU::op_FC(){

}

void CPU::op_FD(){

}

void CPU::op_FE(){
  uint8_t val = load8(++reg_pc);
  op_cp(&val);
  debug_instr.append(string_format("A, Imm8:0x%02x", val));
}

void CPU::op_FF(){
  op_rst(0xff);
  debug_instr.append("38h");
}


bool CPU::check_condition(Condition cond){
  bool ret;

  switch(cond){
    case Condition::C:
      ret = flag->flag_carry();
      break;
    case Condition::NC:
      ret = !flag->flag_carry();
      break;
    case Condition::Z:
      ret = flag->flag_zero();
      break;
    case Condition::NZ:
      ret = !flag->flag_zero();
      break;
  }
  
  // TODO: need to notify whether the branch is taken for timing issues
  // branch_taken = ret;
  return ret;
}

// All instructions
void CPU::op_nop(){
    // do nothing
    debug_instr = "NOP ";
}

// NOTE: LD rr, nn means load to rr the contents of nn
// NOTE: when accessing 16bit addresses, first is LO then HI
// meaning pc->instr => pc+1->lo => pc+2->hi

// mov 8bits from src_reg to dest_reg
void CPU::op_ld(uint8_t *src_reg, uint8_t *dest_reg){
  debug_instr = "LD ";
  *dest_reg = *src_reg;
}

// mov 16bits from src_reg to dest_reg
void CPU::op_ld(Regcomb *src_reg, Regcomb *dest_reg){
  debug_instr = "LD ";
  dest_reg->set(src_reg->get());
}

// mov 8bits from src_addr to dest_addr
void CPU::op_ld(uint16_t src_addr, uint16_t dest_addr){
  debug_instr = "LD ";
  store8(dest_addr, load8(src_addr));
}

// load 8bits from addr in memory to dest_reg
void CPU::op_ld(uint16_t addr, uint8_t *dest_reg){
  debug_instr = "LD ";
  *dest_reg = load8(addr);
}

// load 16bits from addr in memory to dest_reg
void CPU::op_ld(uint16_t addr, Regcomb *dest_reg){
  debug_instr = "LD ";
  dest_reg->set(load16(addr));
}

// load 16bits from addr in memory to 16bit dest_reg (specifically SP)
void CPU::op_ld(uint16_t addr, uint16_t *dest_reg){
  debug_instr = "LD ";
  *dest_reg = load16(addr);
}

// store 8bits from src_reg to addr in memory
void CPU::op_ld(uint8_t *src_reg, uint16_t addr){
  debug_instr = "LD ";
  store8(addr, *src_reg);
}

// store 16bits from src_reg to addr in memory
void CPU::op_ld(Regcomb *src_reg, uint16_t addr){
  debug_instr = "LD ";
  store16(addr, src_reg->get());
}

// store 16bits from src_reg (specifically SP) to addr in memory
void CPU::op_ld(uint16_t *src_reg, uint16_t addr){
  debug_instr = "LD ";
  store16(addr, *src_reg);
}

void CPU::op_add(uint8_t *reg, uint8_t *val){
  debug_instr = "ADD ";
  *reg = *reg + *val;

  // TODO: set flags such as carry, etc
}

void CPU::op_add(Regcomb *a, Regcomb *b){
  debug_instr = "ADD ";
  a->set(a->get() + b->get());

  // TODO: set flags such as carry, etc
}

void CPU::op_add(Regcomb *a, uint16_t *b){
  debug_instr = "ADD ";
  a->set(a->get() + *b);

  // TODO: set flags such as carry, etc
}

// used for adding to SP
void CPU::op_add(uint16_t *a, int8_t *b){
  debug_instr = "ADD ";
  *a = *a + (int16_t)(*b);

  // TODO: set flags such as carry, etc
}

void CPU::op_inc(uint8_t *reg){
    debug_instr = "INC ";
    *reg++;
}

void CPU::op_inc(uint16_t *reg){
    debug_instr = "INC ";
    *reg++;
}

void CPU::op_inc(Regcomb *reg){
    debug_instr = "INC ";
    reg->increment();
}

void CPU::op_inc(uint16_t addr){
  debug_instr = "INC ";
  uint8_t val = load8(addr);
  val++;
  store8(addr, val);
}

void CPU::op_dec(uint8_t *reg){
    debug_instr = "DEC ";
    *reg--;
}

void CPU::op_dec(uint16_t *reg){
    debug_instr = "DEC ";
    *reg--;
}

void CPU::op_dec(Regcomb *reg){
    debug_instr = "DEC ";
    reg->decrement();
}

void CPU::op_dec(uint16_t addr){
  debug_instr = "DEC ";
  uint8_t val = load8(addr);
  val--;
  store8(addr, val);
}

void CPU::op_adc(uint8_t *val){
    debug_instr = "ADC ";
    uint8_t carry = flag->flag_carry_val();
    a += *val + carry;

    // TODO: set flags such as carry, etc
}

void CPU::op_sub(uint8_t *reg, uint8_t *val){
    debug_instr = "SUB ";
    *reg = *reg - *val;
}

void CPU::op_sbc(uint8_t *val){
    debug_instr = "SBC ";
    uint8_t carry = flag->flag_carry_val();
    a -= *val - carry;
}

void CPU::op_and(uint8_t *val){
    debug_instr = "AND ";
    a &= *val;
}

void CPU::op_xor(uint8_t *val){
    debug_instr = "XOR ";
    a ^= *val;
}

void CPU::op_or(uint8_t *val){
    debug_instr = "OR ";
    a |= *val;
}

// TODO: CP is a subtraction from A that doesn't update A, only the flags it would have set/reset if it really was subtracted.
void CPU::op_cp(uint8_t *val){
    debug_instr = "CP ";
    uint8_t res = a - *val;

    // TODO: update flags
}

void CPU::op_cpl(){
  debug_instr = "CPL";
  a = ~a;

  // TODO: update flags (N = 1, H = 1)
}

void CPU::op_jp(uint16_t addr){
  debug_instr = "JP ";
  reg_pc = addr-1;  // we subtract 1 because in cycle reg pc is incremented before moving to the next one
}

// Uncoditional jump to the absolute address specified by 16bit register (specifically HL)
void CPU::op_jp(Regcomb *reg){
  debug_instr = "JP ";
  reg_pc = reg->get() - 1;  // we subtract 1 because in cycle reg pc is incremented before moving to the next one
}

// Conditional jump to 16bit addr depending on condition from reg
void CPU::op_jp(Condition cond, uint16_t addr){
  debug_instr = "JP ";
  if(check_condition(cond)){
    reg_pc = addr - 1;
  }
}

void CPU::op_jr(int8_t addr){
  debug_instr = "JR ";
  reg_pc += addr - 1;
}

void CPU::op_jr(Condition cond, int8_t addr){
  debug_instr = "JR ";
  if(check_condition(cond)){
    reg_pc += addr - 1;
  }
}

void CPU::op_call(uint16_t addr){
  debug_instr = "CALL";
  reg_sp--;
  mem_store8(reg_sp--, (uint8_t)(reg_pc & 0xff));
  mem_store8(reg_sp, (uint8_t)(reg_pc >> 8));
  reg_pc = addr - 1;
}

void CPU::op_call(Condition cond, uint16_t addr){
  debug_instr = "CALL ";
  if(check_condition(cond)){
    reg_sp--;
    mem_store8(reg_sp--, (uint8_t)(reg_pc & 0xff));
    mem_store8(reg_sp, (uint8_t)(reg_pc >> 8));
    reg_pc = addr - 1;
  }
}

void CPU::op_ret(){
  debug_instr = "RET ";
  uint8_t pc_hi = load8(reg_sp++);
  uint8_t pc_lo = load8(reg_sp++);
  reg_pc = (uint16_t)(pc_hi << 8) + (uint16_t)pc_lo;
  reg_pc--; // pc-1 since we increment it at the end of cycle(), which we do not want
}

void CPU::op_ret(Condition cond){
  debug_instr = "RET ";
  if(check_condition(cond)){
    uint8_t pc_hi = load8(reg_sp++);
    uint8_t pc_lo = load8(reg_sp++);
    reg_pc = (uint16_t)(pc_hi << 8) + (uint16_t)pc_lo;
    reg_pc--; // pc-1 since we increment it at the end of cycle(), which we do not want
  }
}

void CPU::op_reti(){
  debug_instr = "RETI ";
  uint8_t pc_hi = load8(reg_sp++);
  uint8_t pc_lo = load8(reg_sp++);
  reg_pc = (uint16_t)(pc_hi << 8) + (uint16_t)pc_lo;
  reg_pc--; // pc-1 since we increment it at the end of cycle(), which we do not want
  // IME = 1
}

void CPU::op_rst(uint8_t opcode){
  debug_instr = "RST ";
  reg_sp--;
  mem_store8(reg_sp--, (uint8_t)(reg_pc & 0xff));
  mem_store8(reg_sp, (uint8_t)(reg_pc >> 8));
  reg_pc = rst_addr(opcode) - 1;
}

void CPU::op_rlc(uint8_t *reg){
    debug_instr = "RLC ";
    uint8_t carry = *reg >> 7;
    uint8_t res = (*reg << 1) | carry;
    *reg = res;

    // TODO: set flags as well
}

void CPU::op_rlca(){
    debug_instr = "RLCA";
    op_rlc(&a);
}

void CPU::op_rl(uint8_t *reg){
    debug_instr = "RL ";
    uint8_t carry = *reg >> 7;
    uint8_t res = (*reg << 1) | carry;
    *reg = res;

    // TODO: set flags (carry is false)
}

void CPU::op_rla(){
    debug_instr = "RLA";
    op_rl(&a);
}

void CPU::op_rrc(uint8_t *reg){
    debug_instr = "RRC ";
    uint8_t carry = *reg & 0x1;
    uint8_t res = (*reg >> 1) | (carry << 7);
    *reg = res;

    // TODO: handle flags
}

void CPU::op_rrca(){
    debug_instr = "RRCA";
    op_rrc(&a);
}

void CPU::op_rr(uint8_t *reg){
    debug_instr = "RR ";
    uint8_t carry = *reg & 0x1;
    uint8_t res = (*reg >> 1) | (carry << 7);
    *reg = res;

    // TODO: handle flags (carry = false)
}

void CPU::op_rra(){
    debug_instr = "RRA ";
    op_rr(&a);
}

void CPU::op_daa(){
  debug_instr = "DAA ";
  // TODO: handle flags
  /*
  // note: assumes a is a uint8_t and wraps from 0xff to 0
  if (!n_flag) {  // after an addition, adjust if (half-)carry occurred or if result is out of bounds
    if (c_flag || a > 0x99) { a += 0x60; c_flag = 1; }
    if (h_flag || (a & 0x0f) > 0x09) { a += 0x6; }
  } else {  // after a subtraction, only adjust if (half-)carry occurred
    if (c_flag) { a -= 0x60; }
    if (h_flag) { a -= 0x6; }
  }
  // these flags are always updated
  z_flag = (a == 0); // the usual z flag
  h_flag = 0; // h flag is always cleared
  */
}

// TODO: write this
void CPU::op_scf(){
  debug_instr = "SCF ";
}

// TODO: write this
void CPU::op_ccf(){
  debug_instr = "CCF ";
}

// TODO: implement these after adding timing/cycles
void CPU::op_stop(){
    debug_instr = "STOP ";
}

void CPU::op_halt(){
  debug_instr = "HALT ";
}

void CPU::op_push(Regcomb *reg){
  debug_instr = "PUSH ";
  reg_sp--;
  mem_store8(reg_sp--, reg->get_lo());
  mem_store8(reg_sp--, reg->get_hi());
}

void CPU::op_pop(Regcomb *reg){
  debug_instr = "POP ";
  uint16_t val = (uint16_t)(mem_load8(reg_sp++) << 8) + (uint16_t)(mem_load8(reg_sp++));
  reg->set(val);
}

void CPU::op_prefix(){

}
