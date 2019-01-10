#ifndef ELF_SYMBOL_H
#define ELF_SYMBOL_H

#include <stdio.h>
#include "elf_types_symbol.h"
#include "elf_types_section.h"

/* Read a string of a symbol table ection content and fill the sym_table */
void read_elf_symbol_table(unsigned char* symtab, Elf32_Shdr* symbol_header, Elf32_Sym sym_table[]);

/* Display an array of sombols */
void display_symbol_table(Elf32_Sym sym_table[], unsigned int num_symbols, unsigned char *string_table, unsigned char *section_name);

#endif
