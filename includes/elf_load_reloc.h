#include "elf_types_section.h"
#include "elf_file.h"

void execute_relocation_section(Elf32_File *ef, Elf32_Shdr reloc_shdr,
                                unsigned char * reloc_content);
