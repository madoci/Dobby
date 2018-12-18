#ifndef ELF_SECTIONS_H
#define ELF_SECTIONS_H
#include <stdio.h>
#include "elf_types.h"
//test
void read_elf_section_table(FILE *f, Elf32_Ehdr *header, Elf32_Shdr e_table[]);

Elf32_Shdr read_section_header(FILE *f);

void display_section_header(FILE* f);
#endif
