#ifndef ELF_HEADER_H
#define ELF_HEADER_H

#include "elf_types.h"

#include <stdio.h>

#define xstr(s) str(s)
#define str(s) #s

typedef enum ERR_ELF_READER{
	ERR_NONE,
	ERR_MAG,
	ERR_CLASS,
	ERR_DATA,
	ERR_VERSION,
	ERR_OSABI,
	ERR_PAD
}ERR_ELF_READER;

/* check if the identification is in correct ELF format :
	1 if true
	0 if false */
ERR_ELF_READER check_ident(Elf32_Ehdr* hdr);

ERR_ELF_READER check_type(Elf32_Ehdr* hdr);

ERR_ELF_READER check_machine(Elf32_Ehdr* hdr);

ERR_ELF_READER check_version(Elf32_Ehdr* hdr);

ERR_ELF_READER check_flags(Elf32_Ehdr* hdr);

/* read an elf header in specified file and fill the given struct with
   f must be opened and hdr a correct pointer.
   return 0 if everything okay, -1 else*/
ERR_ELF_READER read_elf_header(FILE *f, Elf32_Ehdr* hdr);

#endif
