#include "rewrite_section_table.h"

void rewrite_section_table(Elf32_Shdr e_table[], Elf32_Half shnum, Elf32_Shdr new_e_table[], Elf32_Half correl_table[]){
  unsigned int i;
  unsigned int k = 1;
  
  //First section is null and must stay null
  new_e_table[0] = e_table[0];
  correl_table[0] = 0;
  
  //Significant sections
  for(i=1; i<shnum; i++){
    if(e_table[i].sh_type != SHT_RELA && e_table[i].sh_type != SHT_REL){
      new_e_table[k] = e_table[i];
      correl_table[i] = k;
      
      new_e_table[k].sh_offset = new_e_table[k-1].sh_offset + new_e_table[k-1].sh_size;
      
      //DEBUG: Help to see what changed
      /*
       *      printf( "Section %d mapped on %d has offset %d -> %d\n",i,k,
       *              e_table[i].sh_offset, rew_e_table[k].sh_offset);
       */
      ++k;
    }
  }
}

void correct_header(Elf32_Ehdr *hdr, Elf32_Half shnum, Elf32_Half correl_table[]){
  hdr->e_shstrndx = correl_table[hdr->e_shstrndx];
  hdr->e_shnum = shnum;
}

void correct_symtab(Elf32_Shdr e_table[], Elf32_Half shnum, Elf32_Half correl_table[]){
  unsigned int i;
  for(i=0; i<shnum; i++){
    if(e_table[i].sh_type == SHT_SYMTAB){
      e_table[i].sh_link = correl_table[e_table[i].sh_link];
      e_table[i].sh_info = i;
    }
  }
}

Elf32_Half count_shnum(Elf32_Shdr e_table[], Elf32_Half shnum){
  Elf32_Half non_rel = 0;
  
  unsigned int i;
  for(i=0; i<shnum; i++){
    if(e_table[i].sh_type != SHT_RELA && e_table[i].sh_type != SHT_REL){
      ++non_rel;
    }
  }
  
  return non_rel;
}
