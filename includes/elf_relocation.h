#ifndef ELF_RELOCATION_H
#define ELF_RELOCATION_H

#include <stdio.h>
#include "elf_types_header.h"
#include "elf_types_section.h"
#include "elf_types_relocation.h"

/* Read the relocation table of a REL header section */
void read_rel_section(unsigned char* section_content, Elf32_Shdr *hdr, Elf32_Rel entries[]);

/* Read the relocation table of a RELA header section */
void read_rela_section(unsigned char* section_content, Elf32_Shdr *hdr, Elf32_Rela entries[]);

/* Display a relocation table (REL) of an ELF file */
void display_rel_table(Elf32_Rel entries[], const unsigned int num_entries, const unsigned char *name);

/* Display a relocation table (RELA) of an ELF file */
void display_rela_table(Elf32_Rela entries[], const unsigned int num_entries, const unsigned char *name);

#endif
