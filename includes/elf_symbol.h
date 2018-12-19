#include "elf_types_symbol.h"

void read_elf_symbole_table(FILE *f, Elf32_Shdr *Shdr, Elf32_sym s_table);

void display_section_header(FILE* f);