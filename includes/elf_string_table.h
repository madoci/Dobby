#ifndef ELF_STRING_TABLE_H
#define ELF_STRING_TABLE_H

#include <stdio.h>
#include "elf_types_section.h"

/* Return the string table */
char * extract_string_table(FILE *f, Elf32_Shdr str);

#endif
