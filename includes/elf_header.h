#ifndef ELF_HEADER_H
#define ELF_HEADER_H

#include "elf_types_header.h"

#include <stdio.h>

typedef enum Err_ELF_Header{
	ERR_EH_NONE     =  0,
	ERR_EH_IMAG     =  1,
	ERR_EH_ICLASS   =  2,
	ERR_EH_IDATA    =  3,
	ERR_EH_IVERSION =  4,
	ERR_EH_IOSABI   =  5,
	ERR_EH_IPAD     =  6,
	ERR_EH_TYPE     =  7,
	ERR_EH_MACHINE  =  8,
	ERR_EH_VERSION  =  9,
	ERR_EH_FLAGS    = 10
} Err_ELF_Header;

/* read an elf header in specified file and fill the given struct with
   f must be opened and hdr a correct pointer.
   return ERR_EH_NONE if everything okay */
Err_ELF_Header read_elf_header(FILE *f, Elf32_Ehdr* hdr);

#endif
