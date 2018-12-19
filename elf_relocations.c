#include "elf_types_relocations.h"
#include <stdio.h>

void read_rel_section(FILE* f, Elf32_Shdr *hdr, Elf32_Rel entries[]){
  unsigned int i;
  for (i = 0; i<(hdr->sh_size/sizeof(Elf32_Rel)); i++){
    fseek(f, hdr->sh_offset+i*sizeof(Elf32_Rel), SEEK_SET);
    entries[i] = read_rel(f);
  }
}

int read_rela_section(FILE* f, Elf32_Shdr *hdr, Elf32_Rela entries[]){
  unsigned int i;
  for (i = 0; i<(hdr->sh_size/sizeof(Elf32_Rela)); i++){
    fseek(f, hdr->sh_offset+i*sizeof(Elf32_Rela), SEEK_SET);
    entries[i] = read_rela(f);
  }
}

Elf32_Rel read_rel(FILE* f){
  Elf32_Rel r;
  fread_32bits(&r.r_offset,1,f);
  fread_32bits(&r.r_info,1,f);
  return r;
}

Elf32_Rela read_rel(FILE* f){
  Elf32_Rela r;
  fread_32bits(&r.r_offset,1,f);
  fread_32bits(&r.r_info,1,f);
  fread_32bits(&r.r_addend,1,f);
  return r;
}
