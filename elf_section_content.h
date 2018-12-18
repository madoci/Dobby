#ifndef ELF_SECTION_CONTENT_H
#define ELF_SECTION_CONTENT_H

#include "elf_types_header.h"
#include "elf_types_section.h"

void read_elf_section_content_by_name(FILE *f, Elf32_Shdr tab[], Elf32_Ehdr hdr, char *name);
void read_elf_section_content_by_num(FILE *f, Elf32_Shdr tab[], Elf32_Ehdr hdr, Elf32_Half num);

#endif