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

#define xstr(x) str(x)
#define str(x) #x

const char * section_type(Elf32_Shdr *hdr){

  switch (hdr->sh_type) {
    case SHT_NULL:
      return "SHT_NULL";
    case SHT_PROGBITS:
      return "SHT_PROGBITS";
    case SHT_SYMTAB :
        return "SHT_SYMTAB ";
    case SHT_STRTAB:
        return "SHT_STRTAB";
    case SHT_RELA:
        return "SHT_RELA";
    case SHT_HASH :
        return "SHT_HASH";
    case SHT_DYNAMIC:
        return "SHT_DYNAMIC";
    case SHT_NOTE:
        return "SHT_NOTE";
    case SHT_NOBITS:
      return "SHT_NOBITS";
    case SHT_REL:
      return "SHT_REL";
    case SHT_SHLIB:
        return "SHT_SHLIB";
    case SHT_DYNSYM:
        return "SHT_DYNSYM";
    case SHT_ARM_EXIDX:
        return "SHT_ARM_EXIDX";
    case SHT_ARM_PREEMPTMAP:
        return "SHT_ARM_PREEMPTMAP";
    case SHT_ARM_ATTRIBUTES:
        return "SHT_ARM_ATTRIBUTES";
    case SHT_ARM_DEBUGOVERLAY:
        return "SHT_ARM_DEBUGOVERLAY";
    case SHT_ARM_OVERLAYSECTION:
      return "SHT_ARM_OVERLAYSECTION";
    case SHT_LOPROC:
      return "SHT_LOPROC";
    case SHT_HIPROC:
        return "SHT_HIPROC";
    case SHT_LOUSER:
        return "SHT_LOUSER";
    case SHT_HIUSER:
        return "SHT_HIUSER";
  }
  return "erreurType";
}

const char * section_name(FILE* f, Elf32_Shdr str_table, Elf32_Word sh_name){
  return "BB";
}

const char * section_flags(Elf32_Shdr hdr){
  return "CC";
}

void display_section_header(FILE* f){
  Elf32_Ehdr header;
  Elf32_Half i;

  read_elf_header(f, &header);
  Elf32_Half nbr_section = header.e_shnum;
  Elf32_Shdr tab_section_hdr[nbr_section];
  read_elf_section_table(f, &header, tab_section_hdr);

  printf("\nIl y a %d en-têtes de section,\
  débutant à l'adresse de décalage 0x%08x:\n\n",nbr_section,header.e_shoff);
  printf("[%2s] %-16s %-16s %-8s %-6s %-6s %-2s %-3s %-2s %-3s %-2s\n","Nr","Nom","Type","Adr","Décala.","Taille","ES","Fan","LN","Inf","Al");
  for(i=0; i<nbr_section; i++){
    const char *nom = section_name(f,tab_section_hdr[header.e_shstrndx],tab_section_hdr[i].sh_name);
    const char *type = section_type(&tab_section_hdr[i]);
    const char *flags = section_flags(tab_section_hdr[i]);
    printf("[%2d] %-16s %-16s %08x %06x %06x %2d %3s %2d %3d %2d\n",
            i, nom,type,tab_section_hdr[i].sh_addr,tab_section_hdr[i].sh_offset,tab_section_hdr[i].sh_size,
            tab_section_hdr[i].sh_entsize,flags,tab_section_hdr[i].sh_link,tab_section_hdr[i].sh_info,
            tab_section_hdr[i].sh_addralign);
  }
}
