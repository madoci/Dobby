#include "elf_load_reloc.h"
#include "elf_symbol.h"
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
      read_32bits(place, &i32);
      return (Elf32_Word) i32;
    case R_ARM_ABS16:
      read_16bits(place, &i16);
      return (Elf32_Word) signExtend(i16, 16);
    case R_ARM_ABS8:
      read_8bits(place, &i8);
      return (Elf32_Word) signExtend(i8, 8);
  }
}

void do_reloc(Elf32_Rel reloc, unsigned char* addr, Elf32_Sym symbol,
              Elf32_Word addend, Elf32_Word type){

  Elf32_Word value = 0;
  switch(ELF32_R_TYPE(reloc.r_info)){
    case R_ARM_ABS32:
      value = (symbol.st_value + addend) | type
      write_32bits(addr,)
  }
}

//Bit immediate : bit 25 == 0 ==> valeur immediate (bits 0-11)
//Bit UP : ??
void execute_relocation(Elf32_File * ef, Elf32_Shdr shdr, Elf32_Rel rel){
  //Compute relocation adress
  unsigned char *to_reloc = ef->elf_section_content[shdr.sh_info]
                            + rel.r_offset;

  //Compute symbol table associated with relocation
  Elf32_Sym sym_table[ef->section_table[shdr.sh_link].sh_size];
  read_elf_symbol_table(ef->section_content[shdr.sh_link],
                        &ef->section_table[shdr.sh_link],
                        sym_table);

  //Compute symbol to be relocated
  const Elf32_Sym symbol = sym_table[ELF32_R_SYM(rel.r_info)];

  //Compute addend
  const Elf32_Word addend = compute_addend(rel, to_reloc);

  //Type is always 0 (no thumb instructions)
  const Elf32_Word type = 0;

  do_reloc(rel,to_reloc,symbol,addend,type);
}
