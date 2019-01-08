#ifndef ELF_FILE_H
#define ELF_FILE_H

#include <stdio.h>
#include <stdlib.h>

#include "elf_types.h"

typedef struct {
  Elf32_Ehdr header;
  Elf32_Shdr *section_table;
  unsigned char **section_content;
} Elf32_File;

/* Fichier préalablement ouvert, à fermer vous même*/
int read_elf_file(FILE* f, Elf32_File* ef);

void write_elf_file(FILE* f, Elf32_File ef);

void reorder_elf_file(Elf32_File *ef);

void free_elf_file(Elf32_File* f);


#endif
