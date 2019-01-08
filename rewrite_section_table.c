#include "rewrite_section_table.h"
#include <stdlib.h>

void rewrite_section_table(Elf32_Shdr e_table[], Elf32_Half shnum, Elf32_Shdr new_e_table[], Elf32_Half new_shnum, Elf32_Half correl_table[]){
  unsigned int i;
  unsigned int k = 1;

  //First section is null and must stay null
  new_e_table[0] = e_table[0];
  correl_table[0] = 0;
  
  //Significant sections
  for(i=1; i<shnum; i++){
    if(e_table[i].sh_type != SHT_RELA && e_table[i].sh_type != SHT_REL && e_table[i].sh_size != 0){
      new_e_table[k] = e_table[i];
      correl_table[i] = k;
      ++k;
    }
  }
}

void correct_header(Elf32_Ehdr *hdr, Elf32_Half shnum, Elf32_Half correl_table[]){
  hdr->e_shstrndx = correl_table[hdr->e_shstrndx];
  hdr->e_shnum = shnum;
}

void correct_symtab_header(Elf32_Shdr e_table[], Elf32_Half shnum, Elf32_Half correl_table[]){
  unsigned int i;
  for(i=0; i<shnum; i++){
    if(e_table[i].sh_type == SHT_SYMTAB){
      e_table[i].sh_link = correl_table[e_table[i].sh_link];
      e_table[i].sh_info = i;
    }
  }
}

Elf32_Half count_shnum(Elf32_Shdr e_table[], Elf32_Half shnum){
  Elf32_Half non_rel = 1;
  
  unsigned int i;
  for(i=1; i<shnum; i++){
    if(e_table[i].sh_type != SHT_RELA && e_table[i].sh_type != SHT_REL && e_table[i].sh_size != 0){
      ++non_rel;
    }
  }
  
  return non_rel;
}
