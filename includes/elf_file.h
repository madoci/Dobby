#ifndef ELF_FILE_H
#define ELF_FILE_H

#include <stdio.h>
#include <stdlib.h>

#include "elf_types.h"

typedef enum {
  ERR_EF_NONE        =  0,
	ERR_EF_EH_IMAG     =  1,
	ERR_EF_EH_ICLASS   =  2,
	ERR_EF_EH_IDATA    =  3,
	ERR_EF_EH_IVERSION =  4,
	ERR_EF_EH_IOSABI   =  5,
	ERR_EF_EH_IPAD     =  6,
	ERR_EF_EH_TYPE     =  7,
	ERR_EF_EH_MACHINE  =  8,
	ERR_EF_EH_VERSION  =  9,
	ERR_EF_EH_FLAGS    = 10,
  ERR_EF_MALLOC      = 11,
  ERR_EF_CONTENT     = 12
} Err_ELF_File;

typedef struct {
  Elf32_Ehdr header;
  Elf32_Shdr *section_table;
  unsigned char **section_content;
} Elf32_File;

/* Fichier préalablement ouvert, à fermer vous même*/
Err_ELF_File read_elf_file(FILE* f, Elf32_File* ef);

const char* str_Err_ELF_File(Err_ELF_File err);

void write_elf_file(FILE* f, Elf32_File ef);

void reorder_elf_file(Elf32_File *ef);

void free_elf_file(Elf32_File* f);


#endif
