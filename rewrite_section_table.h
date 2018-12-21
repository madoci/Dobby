#include "elf_section_table.h"
#include "elf_header.h"

void rewrite_section_table(Elf32_Ehdr *header, Elf32_Shdr *e_table, Elf32_Shdr *rew_e_table, Elf32_Half *corres);

Elf32_Half compte_shnum(Elf32_Ehdr *header, Elf32_Shdr *e_table);
