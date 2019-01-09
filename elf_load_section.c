#include "elf_load_section.h"

#include <stdlib.h>
#include <string.h>


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


int copy_section_content(Elf32_File *dest, Elf32_File src, Elf32_Half correl_table[]){
  dest->section_content = malloc(sizeof(unsigned char*) * dest->header.e_shnum);
  if (dest->section_content == NULL){
  	return 1;
  }

  dest->section_content[0] = NULL;

  unsigned int i;
  for (i=1; i<src.header.e_shnum; i++){
  	if(src.section_table[i].sh_type != SHT_RELA && src.section_table[i].sh_type != SHT_REL && src.section_table[i].sh_size != 0){
  	  dest->section_content[correl_table[i]] = malloc(sizeof(unsigned char) * dest->section_table[correl_table[i]].sh_size);
  	  if (dest->section_content[correl_table[i]] == NULL){
  	    return 1;
  	  }
      memcpy(dest->section_content[correl_table[i]], src.section_content[i], sizeof(unsigned char) * dest->section_table[correl_table[i]].sh_size);
    }
  }

  return 0;
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


void renum_section_elf_file(Elf32_File *dest, Elf32_File src, Elf32_Half correl_table[]){
  dest->header = src.header;
  dest->header.e_shnum = count_shnum(src.section_table, src.header.e_shnum);
  dest->section_table = malloc(sizeof(Elf32_Shdr) * dest->header.e_shnum);

  // First section is null and must stay null
  dest->section_table[0] = src.section_table[0];
  correl_table[0] = 0;

  // Significant sections
  unsigned int i;
  unsigned int k = 1;
  for(i=1; i<src.header.e_shnum; i++){
    if(src.section_table[i].sh_type != SHT_RELA && src.section_table[i].sh_type != SHT_REL && src.section_table[i].sh_size != 0){
      dest->section_table[k] = src.section_table[i];
      correl_table[i] = k;
      ++k;
    }
  }

  dest->header.e_shstrndx = correl_table[src.header.e_shstrndx];

  correct_symtab_header(dest->section_table, dest->header.e_shnum, correl_table);

  copy_section_content(dest, src, correl_table);
}
