#include "elf_load_symbol.h"
#include "elf_symbol.h"
#include "elf_io.h"
#include <stdio.h>

Elf32_Sym correct_symbol_section(Elf32_Sym sym, Elf32_Half correl_table[]){
  switch(sym.st_shndx){
    case SHN_ABS:
    case SHN_UNDEF:
    case SHN_COMMON:
      break;
    default:
      sym.st_shndx = correl_table[sym.st_shndx];
      break;
  }
  return sym;
}

Elf32_Sym correct_symbol_value(Elf32_Sym sym, Elf32_Shdr section_table[], Elf32_Half sh_count){
  if (sym.st_shndx==SHN_ABS){
    return sym;
  }

  if (sym.st_shndx==SHN_COMMON){
      return (Elf32_Sym) {.st_shndx=sym.st_shndx+1};
  }

  if (sym.st_shndx >= sh_count || sym.st_shndx == SHN_UNDEF){
    return (Elf32_Sym) {.st_shndx=sym.st_shndx+1};
  }

  if (ELF32_ST_TYPE(sym.st_info) == STT_NOTYPE || ELF32_ST_TYPE(sym.st_info) == STT_SECTION)
    sym.st_value += section_table[sym.st_shndx].sh_addr;

  return sym;
}

void write_symbol(unsigned char *addr, Elf32_Sym symbol){
  write_32bits(addr, &symbol.st_name);
  addr += sizeof(symbol.st_name);
  write_32bits(addr, &symbol.st_value);
  addr += sizeof(symbol.st_value);
  write_32bits(addr, &symbol.st_size);
  addr += sizeof(symbol.st_size);
  write_8bits(addr, &symbol.st_info);
  addr += sizeof(symbol.st_info);
  write_8bits(addr, &symbol.st_other);
  addr += sizeof(symbol.st_other);
  write_16bits(addr, &symbol.st_shndx);
}

void correct_all_symbol(Elf32_File* ef, Elf32_Half sh_num, Elf32_Half correl_table[], Elf32_Half correl_symbol[]){
  unsigned char *symbol_addr = ef->section_content[sh_num];
  Elf32_Sym temp;
  const unsigned int num_symbols =
        ef->section_table[sh_num].sh_size / sizeof(Elf32_Sym);

  Elf32_Word nb_symbol = 1;
  Elf32_Sym sym_table[num_symbols];

  read_elf_symbol_table(symbol_addr, &ef->section_table[sh_num], sym_table);

  //Let the undef symbol
  symbol_addr += sizeof(Elf32_Sym);
  correl_symbol[0] = 0;

  //Modify other symbols
  for(Elf32_Half i = 1; i < num_symbols; i++){
    sym_table[i] = correct_symbol_section(sym_table[i],correl_table);
    temp = correct_symbol_value(sym_table[i],ef->section_table,ef->header.e_shnum);
    if (temp.st_shndx != sym_table[i].st_shndx){
      continue;
    }
    else{
      sym_table[i] = temp;
      write_symbol(symbol_addr, sym_table[i]);
      symbol_addr += sizeof(Elf32_Sym);
      
      correl_symbol[i] = nb_symbol;
      nb_symbol++;
    }
  }
  ef->section_table[sh_num].sh_size = nb_symbol*sizeof(Elf32_Sym);
}
