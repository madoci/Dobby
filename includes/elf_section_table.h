#ifndef ELF_SECTIONS_TABLE_H
#define ELF_SECTIONS_TABLE_H

#include <stdio.h>
#include "elf_types.h"

/* Lis la table des entêtes de sections et remplis le tableau e_table */
void read_elf_section_table(FILE *f, Elf32_Ehdr *header, Elf32_Shdr e_table[]);

/* Lis la liste des entêtes de sections */
void display_section_header(FILE* f);

#endif
