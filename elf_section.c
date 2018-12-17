#include "elf_section.h"
#include <stdio.h>

void read_elf_section(FILE *f, Elf32_Ehdr *header, Elf32_Shdr e_table[]){
  unsigned int i;
  for (i = 0; i<header->e_shnum; i++){
    fseek(f, header->e_shoff+i*header->e_shentsize, SEEK_SET);
    e_table[i] = read_section_header(f);
  }
}

Elf32_Shdr read_section_header(FILE *f){

  Elf32_Shdr line;
  fread(&(line.sh_name), 4, 1, f);
  fread(&(line.sh_type), 4, 1, f);
  fread(&(line.sh_flags), 4, 1, f);
  fread(&(line.sh_addr), 4, 1, f);
  fread(&(line.sh_offset), 4, 1, f);
  fread(&(line.sh_size), 4, 1, f);
  fread(&(line.sh_link), 4, 1, f);
  fread(&(line.sh_info), 4, 1, f);
  fread(&(line.sh_addralign), 4, 1, f);
  fread(&(line.sh_entsize), 4, 1, f);

  return line;
}

#define xstr(x) str(x)
#define str(x) #x

const char * section_type(Elf32_Shdr hdr){
  return "AA";
  //return xstr(hdr.sh_type);
}

const char * section_name(FILE* f, Elf32_Shdr str_table, Elf32_Word sh_name){
  return "BB";
}

const char * section_flags(Elf32_Shdr hdr){
  return "CC";
}

void display_section_header(FILE* f,Elf32_Word num, Elf32_Word offset,
                            Elf32_Half e_shstrndx,Elf32_Shdr tab[]){
  int i;
  printf("Il y a %d en-têtes de section,\
  débutant à l'adresse de décalage 0x%08x:\n",num,offset);
  puts("[Nr]\tNom\tType\tAdr\tDécala.\tTaille\tES\tFan\tLN\tInf\tAl\n");
  for(i=0; i<num; i++){
    const char *nom = section_name(f,tab[e_shstrndx],tab[i].sh_name);
    const char *type = section_type(tab[i]);
    const char *flags = section_flags(tab[i]);
    printf("[%2d]\t%s\t%s\t%16x\t%6x\t%6x\t%2d\t%s\t%2d\t%2d\t%2d\n",
            i, nom,type,tab[i].sh_addr,tab[i].sh_offset,tab[i].sh_size,
            tab[i].sh_entsize,flags,tab[i].sh_link,tab[i].sh_info,
            tab[i].sh_addralign);
  }
}
