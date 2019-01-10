#include "elf_types_atomic.h"
#include "elf_types_relocation.h"
#include "elf_load_reloc.h"
#include "elf_symbol.h"
#include "elf_relocation.h"
#include "elf_io.h"
#include <stdio.h>

int32_t signExtend(uint32_t number, int n){
  int32_t ret;
  uint32_t mask = 0xffffffff << n;

  if (number & (1 << (n - 1))){
    // number is negative
    ret = number | mask;
  }
  else {
    // number is positive
    ret = number & ~mask;
  }
  return ret;
}

Elf32_Word compute_addend(Elf32_Rel reloc, unsigned char * place){
  uint32_t i32 = 0;
  uint16_t i16 = 0;
  uint8_t  i8  = 0;
  switch(ELF32_R_TYPE(reloc.r_info)){
    case R_ARM_ABS32:
      read_32bits(&i32, place);
      return (Elf32_Word) i32;
    case R_ARM_ABS16:
      read_16bits(&i16, place+2);
      return (Elf32_Word) signExtend(i16, 16);
    case R_ARM_ABS8:
      read_8bits(&i8, place+3);
      return (Elf32_Word) signExtend(i8, 8);
    case R_ARM_CALL:
    case R_ARM_JUMP24:
      read_32bits(&i32, place);
      i32 &= 0x00FFFFFF;
      i32 = (i32 & 0x00800000) ? i32 | 0xFF000000 : i32;
      return (Elf32_Word) i32;
    default:
      puts("Unknow");
      return (Elf32_Word) 0;
  }
}

void do_reloc(Elf32_Rel reloc, unsigned char* addr, Elf32_Sym symbol,
              Elf32_Word addend, Elf32_Word type){
  union {Elf32_Word v32; Elf32_Half v16; unsigned char v8; } value;
  int32_t inst;
  int32_t imm24;

  switch(ELF32_R_TYPE(reloc.r_info)){
    case R_ARM_ABS32:
      value.v32 = (symbol.st_value + addend) | type;
      write_32bits(addr, &value.v32);
      break;
    case R_ARM_ABS16:
      value.v16 = symbol.st_value + addend;
      write_16bits(addr+2, &value.v16);
      break;
    case R_ARM_ABS8:
      value.v8 = symbol.st_value + addend;
      write_8bits(addr+3, &value.v8);
      break;
    case R_ARM_CALL:
    case R_ARM_JUMP24:
      imm24 = symbol.st_value + (addend << 2);
      imm24 -= reloc.r_offset;
      imm24 = (imm24 & 0x03FFFFFE) >> 2;
      read_32bits(&inst, addr);
      value.v32 = (inst & 0xFF000000) | (imm24 & 0x00FFFFFF);
      write_32bits(addr, &value.v32);
      break;
    default:
      break;
  }
}

//Bit immediate : bit 25 == 0 ==> valeur immediate (bits 0-11)
//Bit UP : ??
void execute_single_relocation(Elf32_File * ef, Elf32_Shdr shdr, Elf32_Rel rel, Elf32_Half correl_symbol[]){
  //Compute relocation adress
  unsigned char *to_reloc = ef->section_content[shdr.sh_info]
                            + rel.r_offset;

  //Compute symbol table associated with relocation
  const unsigned int nb_sym = ef->section_table[shdr.sh_link].sh_size / sizeof(Elf32_Sym);
  Elf32_Sym sym_table[nb_sym];
  read_elf_symbol_table(ef->section_content[shdr.sh_link],
                        &ef->section_table[shdr.sh_link],
                        sym_table);

  //Compute symbol to be relocated
  const Elf32_Sym symbol = sym_table[correl_symbol[ELF32_R_SYM(rel.r_info)]];

  //Compute addend
  const Elf32_Word addend = compute_addend(rel, to_reloc);

  //Type is always 0 (no thumb instructions)
  const Elf32_Word type = 0;

  do_reloc(rel,to_reloc,symbol,addend,type);
}

void execute_relocation_section(Elf32_File *ef, Elf32_Shdr reloc_shdr,
                                unsigned char * reloc_content, Elf32_Half correl_symbol[]){
  const unsigned int nb_rel = reloc_shdr.sh_size / sizeof(Elf32_Rel);
  Elf32_Rel rel_table[nb_rel];

  read_rel_section(reloc_content, &reloc_shdr, rel_table);

  for (Elf32_Half i = 0; i < nb_rel; i++){
    execute_single_relocation(ef, reloc_shdr, rel_table[i], correl_symbol);
  }
}
