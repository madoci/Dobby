#ifndef ELF_SYMBOL_H
#define ELF_SYMBOL_H

#include "elf_types_symbol.h"
#include "elf_types_section.h"
#include "elf_section_table.h"
#include "fread.h"
#include <stdio.h>

void read_elf_symbol_table(FILE *f, Elf32_Shdr* symbole_header, Elf32_Sym sym_table[]);
void display_symbol_table(FILE* f,Elf32_Shdr* symbole_header, Elf32_Sym sym_table[], Elf32_Shdr * string_table);
Elf32_Sym read_sym(FILE *f);
char * symbol_link(unsigned char info);
char * symbol_type(unsigned char info);

#endif
