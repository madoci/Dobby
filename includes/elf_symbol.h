#ifndef ELF_SYMBOL_H
#define ELF_SYMBOL_H

#include <stdio.h>
#include "elf_types_symbol.h"
#include "elf_types_section.h"

void read_elf_symbol_table(FILE *f, Elf32_Shdr* symbole_header, Elf32_Sym sym_table[]);

void display_symbol_table(FILE* f, Elf32_Shdr* symbole_header, Elf32_Sym sym_table[], Elf32_Shdr * string_table);

#endif
