#ifndef ELF_SECTIONS_TABLE_H
#define ELF_SECTIONS_TABLE_H

#include <stdio.h>
#include "elf_types.h"

/* Init the section table */
void init_section_table(Elf32_Shdr e_table[], Elf32_Half e_shnum);

/* Read the section header table of an ELF file and fill the e_table argument */
void read_elf_section_table(FILE *f, Elf32_Ehdr *header, Elf32_Shdr e_table[]);

/* Display all section headers */
void display_section_table(Elf32_Ehdr *header, Elf32_Shdr e_table[], unsigned char *str_table);

#endif
