#ifndef ELF_SYMBOL_H
#define ELF_SYMBOL_H
#include "elf_types_symbol.h"
#include "elf_types_section.h"
#include <stdio.h>


void read_elf_symbole_table(FILE *f, Elf32_Shdr Shdr, Elf32_Sym s_table);

Elf32_Sym read_sym(FILE *f);

void display_table_sym(FILE* f, Elf32_Shdr tab);

#endif
