#ifndef ELF_LOAD_SECTION_H
#define ELF_LOAD_SECTION_H

#include "elf_file.h"

void renum_section_elf_file(Elf32_File *dest, Elf32_File src, Elf32_Half correl_table[]);

int change_section_address(Elf32_File *dest, const char* section_name, Elf32_Half addr);

#endif
