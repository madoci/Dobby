#include "elf_section_table.h"

#include "elf_section_content.h"
#include "fread.h"


/* READ SECTION HEADER */

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


void read_elf_section_table(FILE *f, Elf32_Ehdr *header, Elf32_Shdr e_table[]){
  unsigned int i;
  for (i = 0; i<header->e_shnum; i++){
    fseek(f, header->e_shoff + i * header->e_shentsize, SEEK_SET);
    e_table[i] = read_section_header(f);
  }
}


/* DISPLAY SECTION HEADER */

const char * section_type(Elf32_Shdr hdr){
  switch (hdr.sh_type) {
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
    return str_table + sh_name;
}


char * section_flags(Elf32_Shdr hdr){
  Elf32_Word flag = hdr.sh_flags;
  char * tab = malloc(15);   //14 flags maximum plus le \0 final
  unsigned int indice = 0;
  if ((flag & SHF_WRITE) != 0){
    tab[indice] = 'W';
    indice++;
  }
  if ((flag & SHF_ALLOC) != 0){
    tab[indice] = 'A';
    indice ++;
  }
  if ((flag & SHF_EXECINSTR) !=0){
    tab[indice] = 'X';
    indice ++;
  }
  if ((flag & SHF_MERGE) !=0){
    tab[indice] = 'M';
    indice ++;
  }
  if ((flag & SHF_STRINGS) !=0){
    tab[indice] = 'S';
    indice ++;
  }
  if ((flag & SHF_INFO_LINK) !=0){
    tab[indice] = 'I';
    indice ++;
  }
  if ((flag & SHF_LINK_ORDER) !=0){
    tab[indice] = 'L';
    indice ++;
  }
  if ((flag & SHF_OS_NONCONFORMING) !=0){
    tab[indice] = 'N';
    indice ++;
  }
  if ((flag & SHF_GROUP) !=0){
    tab[indice] = 'G';
    indice ++;
  }
  if ((flag & SHF_TLS) !=0){
    tab[indice] = 'T';
    indice ++;
  }
  if ((flag & SHF_MASKOS) !=0){
    tab[indice] = 'o';
    indice ++;
  }
  if ((flag & SHF_MASKPROC) !=0){
    tab[indice] = 'p';
    indice ++;
  }
  if ((flag & SHF_ORDERED) !=0){
    tab[indice] = 'O';
    indice ++;
  }
  if ((flag & SHF_EXCLUDE) !=0){
    tab[indice] = 'E';
    indice ++;
  }
  tab[indice] = '\0';

  return tab;
}


void display_section_header(FILE* f, Elf32_Ehdr *header, Elf32_Shdr e_table[]){

  unsigned char * str_table = NULL;
  str_table = read_elf_section_content(f, e_table[header->e_shstrndx]);

  printf("\nIl y a %d en-têtes de section,\
  débutant à l'adresse de décalage 0x%08x:\n\n", header->e_shnum, header->e_shoff);

  printf("[%2s] %-20s %-16s %-8s %-6s %-6s %-2s %5s %-2s %-3s %-2s\n",
         "Nr","Nom","Type","Adr","Décala.","Taille","ES","Fan","LN","Inf","Al");

  Elf32_Half i;
  for (i=0; i<header->e_shnum; i++){
    const unsigned char *nom   = str_table + e_table[i].sh_name;
    const char *type  = section_type(e_table[i]);
    const Elf32_Addr addr = e_table[i].sh_addr;
    const Elf32_Word offset = e_table[i].sh_offset;
    const Elf32_Word size = e_table[i].sh_size;
    const Elf32_Word es = e_table[i].sh_entsize;
    char *flags = section_flags(e_table[i]);
    const Elf32_Word ln = e_table[i].sh_link;
    const Elf32_Word inf = e_table[i].sh_info;
    const Elf32_Word al = e_table[i].sh_addralign;
    printf("[%2d] %-20s %-16s %08x %06x  %06x %02x %5s %2d %3d %2d\n",
            i, nom, type, addr, offset, size, es, flags, ln, inf, al);
    free(flags);
  }
  
  free(str_table);
}
