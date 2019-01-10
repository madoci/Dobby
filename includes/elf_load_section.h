#ifndef ELF_LOAD_SECTION_H
#define ELF_LOAD_SECTION_H

#include "elf_file.h"

/* Renumerotate the section table and section content table of the Elf32_File src
   Changes are copied into the Elf32_File dest
   The correl_table is filled with correlation between indexes of src and indexes of dest */
void renum_section_elf_file(Elf32_File *dest, Elf32_File src, Elf32_Half correl_table[]);

/* Replace by addr the sh_addr attribute of a section (given by its name) */
int change_section_address(Elf32_File *dest, const char* section_name, Elf32_Half addr);

#endif
