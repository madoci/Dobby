#include "elf_section_table.h"

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

void init_section_table(Elf32_Shdr e_table[], Elf32_Half e_shnum){
  for(int i=0; i<e_shnum; i++){
    e_table[i].sh_name      = SHN_UNDEF;
    e_table[i].sh_type      = SHT_NULL;
    e_table[i].sh_flags     = 0;
    e_table[i].sh_addr      = 0;
    e_table[i].sh_offset    = 0;
    e_table[i].sh_size      = 0;
    e_table[i].sh_link      = 0;
    e_table[i].sh_info      = 0;
    e_table[i].sh_addralign = 0;
    e_table[i].sh_entsize   = 0;

  }

}

void read_elf_section_table(FILE *f, Elf32_Ehdr *header, Elf32_Shdr e_table[]){
  unsigned int i;
  for (i = 0; i<header->e_shnum; i++){
    fseek(f, header->e_shoff + i * header->e_shentsize, SEEK_SET);
    e_table[i] = read_section_header(f);
  }
}


/* READ SECTION HEADER */

void write_section_header(FILE *f, Elf32_Shdr line){
  fwrite_32bits(&(line.sh_name), 1, f);
  fwrite_32bits(&(line.sh_type), 1, f);
  fwrite_32bits(&(line.sh_flags), 1, f);
  fwrite_32bits(&(line.sh_addr), 1, f);
  fwrite_32bits(&(line.sh_offset), 1, f);
  fwrite_32bits(&(line.sh_size), 1, f);
  fwrite_32bits(&(line.sh_link), 1, f);
  fwrite_32bits(&(line.sh_info), 1, f);
  fwrite_32bits(&(line.sh_addralign), 1, f);
  fwrite_32bits(&(line.sh_entsize), 1, f);
}

void write_elf_section_table(FILE *f, Elf32_Ehdr header, Elf32_Shdr e_table[]){
  unsigned int i;
  for (i = 0; i<header.e_shnum; i++){
    fseek(f, header.e_shoff + i * header.e_shentsize, SEEK_SET);
    write_section_header(f, e_table[i]);
  }
}


/* DISPLAY SECTION HEADER */

const char * section_type(Elf32_Word sh_type){
  switch (sh_type) {
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
    default:
      break;
  }
  return "erreurType";
}


inline const unsigned char * section_name(unsigned char* str_table, Elf32_Word sh_name){
    return str_table + sh_name;
}


char * section_flags(Elf32_Word sh_flags){
  char * tab = malloc(15);   //14 flags maximum plus le \0 final
  unsigned int indice = 0;
  if ((sh_flags & SHF_WRITE) != 0){
    tab[indice] = 'W';
    indice++;
  }
  if ((sh_flags & SHF_ALLOC) != 0){
    tab[indice] = 'A';
    indice ++;
  }
  if ((sh_flags & SHF_EXECINSTR) != 0){
    tab[indice] = 'X';
    indice ++;
  }
  if ((sh_flags & SHF_MERGE) != 0){
    tab[indice] = 'M';
    indice ++;
  }
  if ((sh_flags & SHF_STRINGS) != 0){
    tab[indice] = 'S';
    indice ++;
  }
  if ((sh_flags & SHF_INFO_LINK) != 0){
    tab[indice] = 'I';
    indice ++;
  }
  if ((sh_flags & SHF_LINK_ORDER) != 0){
    tab[indice] = 'L';
    indice ++;
  }
  if ((sh_flags & SHF_OS_NONCONFORMING) != 0){
    tab[indice] = 'N';
    indice ++;
  }
  if ((sh_flags & SHF_GROUP) != 0){
    tab[indice] = 'G';
    indice ++;
  }
  if ((sh_flags & SHF_TLS) != 0){
    tab[indice] = 'T';
    indice ++;
  }
  if ((sh_flags & SHF_MASKOS) != 0){
    tab[indice] = 'o';
    indice ++;
  }
  if ((sh_flags & SHF_MASKPROC) != 0){
    tab[indice] = 'p';
    indice ++;
  }
  if ((sh_flags & SHF_ORDERED) != 0){
    tab[indice] = 'O';
    indice ++;
  }
  if ((sh_flags & SHF_EXCLUDE) != 0){
    tab[indice] = 'E';
    indice ++;
  }
  tab[indice] = '\0';

  return tab;
}


void display_section_table(Elf32_Ehdr *header, Elf32_Shdr e_table[], unsigned char *str_table){
  printf("\nIl y a %d en-têtes de section,\
  débutant à l'adresse de décalage 0x%08x:\n\n", header->e_shnum, header->e_shoff);

  printf("[%2s] %-17.17s %-16s %-8s %-6s %-6s %-2s %5s %-2s %-3s %-2s\n",
         "Nr","Nom","Type","Adr","Décala.","Taille","ES","Fan","LN","Inf","Al");
  puts("En-tête de section:");
  
  Elf32_Half i;
  for (i=0; i<header->e_shnum; i++){
    const unsigned char *nom   = str_table + e_table[i].sh_name;
    const char *type  = section_type(e_table[i].sh_type);
    const Elf32_Addr addr = e_table[i].sh_addr;
    const Elf32_Word offset = e_table[i].sh_offset;
    const Elf32_Word size = e_table[i].sh_size;
    const Elf32_Word es = e_table[i].sh_entsize;
    char *flags = section_flags(e_table[i].sh_flags);
    const Elf32_Word ln = e_table[i].sh_link;
    const Elf32_Word inf = e_table[i].sh_info;
    const Elf32_Word al = e_table[i].sh_addralign;
    printf("[%2d] %-17.17s %-16s %08x %06x  %06x %02x %5s %2d %3d %2d\n",
            i, nom, type, addr, offset, size, es, flags, ln, inf, al);
    free(flags);
  }
  puts("Clé des fanions: \n \
  W (écriture), A (allocation), X (exécution), M (fusion), S (chaînes) \n \
  I (info), L (ordre des liens), G (groupe), T (TLS), E (exclu), x (inconnu) \n \
  O (traiterment additionnel requis pour l'OS) o (spécifique à l'OS), p (spécifique au processeur)");
}
