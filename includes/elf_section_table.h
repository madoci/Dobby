#ifndef ELF_SECTIONS_TABLE_H
#define ELF_SECTIONS_TABLE_H
#include <stdio.h>
#include "elf_types.h"

void read_elf_section_table(FILE *f, Elf32_Ehdr *header, Elf32_Shdr e_table[]);

void display_section_header(FILE* f);

#endif
