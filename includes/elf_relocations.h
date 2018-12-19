#ifndef ELF_RELOCATIONS_H
#define ELF_RELOCATIONS_H

#include <stdio.h>
#include "elf_types_relocations.h"

/* Read the relocation table of a REL header section */
void read_rel_section(FILE* f, Elf32_Shdr *hdr, Elf32_Rel entries[]);

/* Read the relocation table of a RELA header section */
void read_rela_section(FILE* f, Elf32_Shdr *hdr, Elf32_Rela entries[]);


#endif