#ifndef ELF_SYMBOL_H
#define ELF_SYMBOL_H
#include "elf_types_symbol.h"
#include "elf_types_section.h"


void read_elf_symbole_table(FILE *f, Elf32_Shdr Shdr, Elf32_sym s_table);

Elf32_sym read_sym(FILE *f);

void display_table_sym(FILE* f, Elf32_Shdr tab);
#endif