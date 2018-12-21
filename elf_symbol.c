#include "elf_symbol.h"

#include "fread.h"
#include "elf_section_table.h"
#include "elf_section_content.h"


/* READ SYMBOL TABLE */

Elf32_Sym read_sym(FILE *f){

  Elf32_Sym line;
  fread_32bits(&(line.st_name),1, f);
  fread_32bits(&(line.st_value), 1, f);
  fread_32bits(&(line.st_size), 1, f);
  fread_8bits(&(line.st_info), 1, f);
  fread_8bits(&(line.st_other), 1, f);
  fread_16bits(&(line.st_shndx), 1, f);
	
  return line;
}


void read_elf_symbol_table(FILE *f, Elf32_Shdr* symbole_header, Elf32_Sym sym_table[]){
  const int nb_tableSymbole = symbole_header->sh_size / sizeof(Elf32_Sym);
  const int start_tableSymbole = symbole_header->sh_offset;
  int i;

  for (i=0; i<nb_tableSymbole; i++){
    fseek(f, start_tableSymbole+i*sizeof(Elf32_Sym), SEEK_SET);
    sym_table[i] = read_sym(f);
  }
}


/* DISPLAY SYMBOL TABLE */

char * symbol_vis(unsigned char other){
  switch (ELF32_ST_VIS(other)){
    case STV_DEFAULT:
      return "DEFAULT";
    case STV_INTERNAL:
      return "INTERNAL";
    case STV_HIDDEN:
      return "HIDDEN";
    case STV_PROTECTED:
      return "PROTECTED";
    default:
	  return "Error";
  }
}


char * symbol_link(unsigned char info){
  switch (ELF32_ST_BIND(info)){
    case STB_LOCAL:
      return "LOCAL";
    case STB_GLOBAL:
      return "GLOBAL";
    case STB_WEAK:
      return "WEAK";
    case STB_LOPROC:
      return "LOPROC";
    case STB_HIPROC:
      return "HIPROC";
    default:
	  return "Error";
  }
}


char * symbol_type(unsigned char info){
  switch (ELF32_ST_TYPE(info)){
    case STT_NOTYPE:
      return "NOTYPE";
    case STT_OBJECT:
      return "OBJECT";
    case STT_FUNC:
      return "FUNC";
    case STT_SECTION:
      return "SECTION";
    case STT_FILE:
      return "FILE";
    case STT_LOPROC:
      return "LOPROC";
    case STT_HIPROC:
      return "HIPROC";
    default:
	  return "Error";
  }
}


void display_symbol_table(FILE* f,Elf32_Shdr* symbole_header, Elf32_Sym sym_table[], Elf32_Shdr *string_table_hdr){
  int i = 0;
  const int nb_tableSymbole = (symbole_header->sh_size)/sizeof(Elf32_Sym);
  unsigned char * string_table = read_elf_section_content(f, *string_table_hdr);

  printf("\nLa table des symboles \" .symtab \" contient %d entrées \n\n", nb_tableSymbole);
  printf("%2s\t %8s\t %-1s\t %-7s\t %-6s\t %-9s\t %-3s\t %-12s\n",
         "Num:","Valeur","Tail","Type","Lien","Vis","Ndx","Nom");

  for (i = 0 ; i < nb_tableSymbole; i++){
    const unsigned char *nom = string_table + sym_table[i].st_name;
    const Elf32_Addr valeur = sym_table[i].st_value;
    const Elf32_Word size = sym_table[i].st_size;
    char * type = symbol_type(sym_table[i].st_info);
    char * lien = symbol_link(sym_table[i].st_info);
    char * vis = symbol_vis(sym_table[i].st_other);
    Elf32_Half ndx = sym_table[i].st_shndx;

    printf("%2d:\t %08x\t %-1d\t %-7s\t %-6s\t %-9s\t %-3d\t %-12s\n",
           i, valeur, size, type, lien, vis, ndx, nom);
  }
  free(string_table);
}
