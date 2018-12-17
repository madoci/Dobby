#ifndef ELF_SECTIONS_H
#define ELF_SECTIONS_H
#include <stdio.h>
#include "elf_types.h"

void read_elf_section(FILE *f, Elf32_Ehdr *header, Elf32_Shdr e_table[]);

Elf32_Shdr read_section_header(FILE *f);

void display_section_header(FILE* f,Elf32_Word num, Elf32_Word offset,
                            Elf32_Half e_shstrndx,Elf32_Shdr tab[]);
#endif
