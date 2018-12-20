#ifndef ELF_RELOCATION_H
#define ELF_RELOCATION_H

#include <stdio.h>
#include "elf_types_header.h"
#include "elf_types_section.h"
#include "elf_types_relocation.h"

/* Read the relocation table of a REL header section */
void read_rel_section(FILE* f, Elf32_Shdr *hdr, Elf32_Rel entries[]);

/* Read the relocation table of a RELA header section */
void read_rela_section(FILE* f, Elf32_Shdr *hdr, Elf32_Rela entries[]);

/* Display all relocation tables of an ELF file */
void display_all_relocation_table(FILE* f, Elf32_Ehdr *hdr, Elf32_Shdr shdr[]);

#endif
