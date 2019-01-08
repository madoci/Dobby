#ifndef REWRITE_SECTION_TABLE_H
#define REWRITE_SECTION_TABLE_H

#include "elf_section_table.h"
#include "elf_header.h"

void rewrite_section_table(Elf32_Shdr e_table[], Elf32_Half shnum, Elf32_Shdr new_e_table[], Elf32_Half new_shnum, Elf32_Half correl_table[]);

void correct_header(Elf32_Ehdr *hdr, Elf32_Half shnum, Elf32_Half correl_table[]);

void correct_symtab_header(Elf32_Shdr e_table[], Elf32_Half shnum, Elf32_Half correl_table[]);

Elf32_Half count_shnum(Elf32_Shdr e_table[], Elf32_Half shnum);

#endif
