#include "elf_section.h"
#include "elf_header.h"
#include "fread.h"
#include <stdio.h>

void read_elf_section_table(FILE *f, Elf32_Ehdr *header, Elf32_Shdr e_table[]){
  unsigned int i;
  for (i = 0; i<header->e_shnum; i++){
    fseek(f, header->e_shoff+i*header->e_shentsize, SEEK_SET);
    e_table[i] = read_section_header(f);
  }
}

Elf32_Shdr read_section_header(FILE *f){

  Elf32_Shdr line;
  fread_32bits(&(line.sh_name), 1, f);
  fread_32bits(&(line.sh_type), 1, f);
  fread_32bits(&(line.sh_flags), 1, f);
  fread_32bits(&(line.sh_addr), 1, f);
  fread_32bits(&(line.sh_offset), 1, f);
  fread_32bits(&(line.sh_size), 1, f);
  fread_32bits(&(line.sh_link), 1, f);
  fread_32bits(&(line.sh_info), 1, f);
  fread_32bits(&(line.sh_addralign), 1, f);
  fread_32bits(&(line.sh_entsize), 1, f);

  return line;
}

const char * section_type(Elf32_Shdr *hdr){

  switch (hdr->sh_type) {
    case SHT_NULL:
      return "NULL";
    case SHT_PROGBITS:
      return "PROGBITS";
    case SHT_SYMTAB :
        return "SYMTAB ";
    case SHT_STRTAB:
        return "STRTAB";
    case SHT_RELA:
        return "RELA";
    case SHT_HASH :
        return "HASH";
    case SHT_DYNAMIC:
        return "DYNAMIC";
    case SHT_NOTE:
        return "NOTE";
    case SHT_NOBITS:
      return "NOBITS";
    case SHT_REL:
      return "REL";
    case SHT_SHLIB:
        return "SHLIB";
    case SHT_DYNSYM:
        return "DYNSYM";
    case SHT_ARM_EXIDX:
        return "ARM_EXIDX";
    case SHT_ARM_PREEMPTMAP:
        return "ARM_PREEMPTMAP";
    case SHT_ARM_ATTRIBUTES:
        return "ARM_ATTRIBUTES";
    case SHT_ARM_DEBUGOVERLAY:
        return "ARM_DEBUGOVERLAY";
    case SHT_ARM_OVERLAYSECTION:
      return "ARM_OVERLAYSECTION";
    case SHT_LOPROC:
      return "LOPROC";
    case SHT_HIPROC:
        return "HIPROC";
    case SHT_LOUSER:
        return "LOUSER";
    case SHT_HIUSER:
        return "HIUSER";
  }
  return "erreurType";
}

inline const char * section_name(char* str_table, Elf32_Word sh_name){
    return str_table+sh_name;
}

const char * section_flags(Elf32_Shdr hdr){
  Elf32_Word flag = hdr.sh_flags;
  char * tab = malloc(4); //3 flags maximum plus le \0 final
  unsigned int indice = 0;
  if((flag & SHF_WRITE) != 0){
    tab[indice] = 'W';
    indice++;
  }
  if((flag & SHF_ALLOC) != 0){
    tab[indice] = 'A';
    indice ++;
  }
  if((flag & SHF_EXECINSTR) !=0){
    tab[indice] = 'X';
    indice ++;
  }
  tab[indice] = '\0';

  return tab;
}

char * extract_string_table(FILE *f, Elf32_Shdr str){
    char* str_table = malloc(sizeof(char)*str.sh_size);
    fseek(f,str.sh_offset,SEEK_SET);
    fread(str_table,1,str.sh_size,f);
    return str_table;
}

void display_section_header(FILE* f){
  Elf32_Ehdr header;
  Elf32_Half i;
  read_elf_header(f, &header);

  Elf32_Half nbr_section = header.e_shnum;
  Elf32_Shdr tab_section_hdr[nbr_section];
  read_elf_section_table(f, &header, tab_section_hdr);

  char * symbole_table = NULL;
  symbole_table = extract_string_table(f, tab_section_hdr[header.e_shstrndx]);

  printf("\nIl y a %d en-têtes de section,\
  débutant à l'adresse de décalage 0x%08x:\n\n",nbr_section,header.e_shoff);

  printf("[%2s] %-20s %-16s %-8s %-6s %-6s %-2s %-3s %-2s %-3s %-2s\n",
         "Nr","Nom","Type","Adr","Décala.","Taille","ES","Fan","LN","Inf","Al");

  for(i=0; i<nbr_section; i++){
    const char *nom   = symbole_table+tab_section_hdr[i].sh_name;
    const char *type  = section_type(&tab_section_hdr[i]);
    const Elf32_Addr addr = tab_section_hdr[i].sh_addr;
    const Elf32_Word offset = tab_section_hdr[i].sh_offset;
    const Elf32_Word size = tab_section_hdr[i].sh_size;
    const Elf32_Word es = tab_section_hdr[i].sh_entsize;
    const char *flags = section_flags(tab_section_hdr[i]);
    const Elf32_Word ln = tab_section_hdr[i].sh_link;
    const Elf32_Word inf = tab_section_hdr[i].sh_info;
    const Elf32_Word al = tab_section_hdr[i].sh_addralign;
    printf("[%2d] %-20s %-16s %08x %06x  %06x %02x %3s %2d %3d %2d\n",
            i, nom,type,addr,offset,size,es,flags,ln,inf,al);
  }
}
