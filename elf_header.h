#ifndef ELF_HEADER_H
#define ELF_HEADER_H

#include "elf_types_header.h"

#include <stdio.h>

typedef enum ERR_ELF_HEADER{
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
}ERR_ELF_HEADER;

/* check if the identification is in correct ELF format :
	1 if true
	0 if false */
ERR_ELF_HEADER check_ident(Elf32_Ehdr* hdr);

ERR_ELF_HEADER check_type(Elf32_Ehdr* hdr);

ERR_ELF_HEADER check_machine(Elf32_Ehdr* hdr);

ERR_ELF_HEADER check_version(Elf32_Ehdr* hdr);

ERR_ELF_HEADER check_flags(Elf32_Ehdr* hdr);

/* read an elf header in specified file and fill the given struct with
   f must be opened and hdr a correct pointer.
   return 0 if everything okay, -1 else*/
ERR_ELF_HEADER read_elf_header(FILE *f, Elf32_Ehdr* hdr);

#endif
