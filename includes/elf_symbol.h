#ifndef ELF_SYMBOL_H
#define ELF_SYMBOL_H

#include <stdio.h>
#include "elf_types_symbol.h"
#include "elf_types_section.h"

void read_elf_symbol_table(FILE *f, Elf32_Shdr* symbol_header, Elf32_Sym sym_table[]);

void display_symbol_table(Elf32_Sym sym_table[], unsigned int num_symbols, unsigned char *string_table, unsigned char *section_name);

#endif
