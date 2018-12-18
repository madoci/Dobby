#ifndef ELF_HEADER_H
#define ELF_HEADER_H

#include "elf_types_header.h"

#include <stdio.h>

typedef enum Err_ELF_Header{
	ERR_EH_NONE,
	ERR_EH_IMAG,
	ERR_EH_ICLASS,
	ERR_EH_IDATA,
	ERR_EH_IVERSION,
	ERR_EH_IOSABI,
	ERR_EH_IPAD,
	ERR_EH_TYPE,
	ERR_EH_MACHINE,
	ERR_EH_VERSION,
	ERR_EH_FLAGS
} Err_ELF_Header;

/* read an elf header in specified file and fill the given struct with
   f must be opened and hdr a correct pointer.
   return ERR_EH_NONE if everything okay */
Err_ELF_Header read_elf_header(FILE *f, Elf32_Ehdr* hdr);

#endif
