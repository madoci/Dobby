#ifndef ELF_FILE_H
#define ELF_FILE_H

#include "elf_types.h"

typedef struct {
  Elf32_Ehdr header;
  Elf32_Shdr *section_table;
  unsigned char **section_content;
} Elf32_File;

/* Fichier préalablement ouvert, à fermer vous même*/
int read_elf_file(FILE* f, Elf32_File* ef);

int free_elf_file(Elf32_File* f);



#endif
