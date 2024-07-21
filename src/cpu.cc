#include "cpu.h"

/*
template<typename ... Args>
std::string string_format( const std::string& format, Args ... args )
{
  int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; //
Extra space for '\0' if( size_s <= 0 ){ throw std::runtime_error( "Error during
formatting." ); } auto size = static_cast<size_t>( size_s );
  std::unique_ptr<char[]> buf( new char[ size ] );
  std::snprintf( buf.get(), size, format.c_str(), args ... );
  return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the
'\0' inside
}
*/

CPU::CPU(uint8_t *memory_ptr, int m_size, MMU *mmu) {
  a, b, c, d, e, f, h, l = 0x00;
  af = new Regcomb(a, f);
  bc = new Regcomb(b, c);
  de = new Regcomb(d, e);
  hl = new Regcomb(h, l);

  reg_pc = 0x0100;
  reg_sp = 0x00;

  flag = new FlagReg();

  this->memory_ptr = memory_ptr;
  this->mmu = mmu;
}

CPU::~CPU() {}

void CPU::main_loop() {
  while (1) {
    cycle();
  }
}

// TODO: some commands have variable number of cycles (handle timing)
void CPU::cycle() {
  debug_instr = "";
  mem_dump = "";

  printf("0x%04x:\t", reg_pc);
  uint8_t instr = load8(reg_pc);
  printf("0x%02x =>\t", instr);

  execute(instr);
  std::cout << debug_instr << std::endl;

  reg_pc++;

  // max PC value
  if (reg_pc >= 0xffff) {
    exit(0);
  }

  // TODO: move to a debugger class
  // debug
  if (brk == true) {
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

    for (int i = 0; i <= MEMSIZE - 16; i += 16) {
      mem_dump.append(string_format("0x%05x:\t", i));
      for (int j = i; j < i + 16; j++) {
        mem_dump.append(string_format("0x%02x ", memory_ptr[j]));
      }
      mem_dump.append("\n");
    }
    memdump_file.open("mem_dump.log");
    memdump_file << mem_dump;
    memdump_file.close();
    printf("\nMemory Dumped at mem_dump.log\n");
    exit(0);
    // printf("\n$>");
    // std::cin.get();
  }
}

uint CPU::execute(uint8_t instr) {
  uint cycles = 0;
  branch_taken = false;
  prefixed_op = false;

  switch (instr) {
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

  if (!branch_taken) {
    if (prefixed_op) {
      cycles = opcode_cycles_cb[instr];
    } else {
      cycles = opcode_cycles[instr];
    }
  } else {
    cycles = opcode_cycles_branched[instr];
  }

  debug_instr.append(string_format("\t\tcycles: %d", cycles));
  return cycles;
}

uint8_t CPU::mem_load8(uint16_t offset) {
  size_t off = (size_t)offset;
  if (offset < 8 * 1024) return memory_ptr[off];

  return 0x00;
}

uint16_t CPU::mem_load16(uint16_t offset) {
  size_t off = (size_t)offset;
  if (offset < 8 * 1024) return memory_ptr[off] + (memory_ptr[off + 1] << 8);

  return 0x0000;
}

void CPU::mem_store8(uint16_t offset, uint8_t data) {
  size_t off = (size_t)offset;
  if (offset < 8 * 1024) memory_ptr[off] = data;
}

void CPU::mem_store16(uint16_t offset, uint16_t data) {
  size_t off = (size_t)offset;
  if (offset < 8 * 1024) {
    memory_ptr[off] = (uint8_t)(data & 0xf0);
    memory_ptr[off + 1] = (uint8_t)(data >> 8);
  }
}

void CPU::store8(uint16_t addr, uint8_t data) {
  // TODO: check if addr is aligned

  if (!mmu->check_range(addr)) {
    printf("Attempting to write to invalid memory 0x%x. EXITING ...\n", addr);
    exit(0);
  }
  mem_store8(addr, data);
}

void CPU::store16(uint16_t addr, uint16_t data) {
  // TODO: check if addr is aligned

  if (!mmu->check_range(addr)) {
    printf("Attempting to write to invalid memory 0x%x. EXITING ...\n", addr);
    exit(0);
  }
  mem_store16(addr, data);
}

uint8_t CPU::load8(uint16_t addr) {
  // TODO: check if addr is aligned

  if (!mmu->check_range(addr)) {
    printf("Attempting to read from invalid memory 0x%x. EXITING ...\n", addr);
    exit(0);
  }
  return mem_load8(addr);
}

uint16_t CPU::load16(uint16_t addr) {
  // TODO: check if addr is aligned

  if (!mmu->check_range(addr)) {
    printf("Attempting to read from invalid memory 0x%x. EXITING ...\n", addr);
    exit(0);
  }
  return mem_load16(addr);
}

uint8_t CPU::rst_addr(uint8_t opcode) {
  uint8_t ret;

  switch (opcode) {
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

bool CPU::check_condition(Condition cond) {
  bool ret;

  switch (cond) {
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

  branch_taken = ret;
  return ret;
}
