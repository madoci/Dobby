#ifndef ELF_H
#define ELF_H

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

/* Convenient macros to check atomic types size, according to Format_ELF.pdf*/

#define chk_word_size(word) (sizeof(word)==4)
#define chk_sword_size(sword) (sizeof(sword)==4)
#define chk_half_size(half) (sizeof(half)==2)
#define chk_off_size(off) (sizeof(off)==4)
#define chk_addr_size(addr) (sizeof(addr)==4)

/* wrapper to check all types once, return 1 if everything is okay else :
   -1 => 32 unsigned error
   -2 => 32 signed error
   -3 => 16 unsigned error*/
int check_types_size(void);

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
