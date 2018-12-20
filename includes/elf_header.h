#ifndef ELF_HEADER_H
#define ELF_HEADER_H

#include <stdio.h>
#include "elf_types_header.h"
#include "elf_types_atomic.h"

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

#define printf_8x(s,x) printf("\t%-50s\t0x%08x\n",s,x)
#define printf_d(s,d) printf("\t%-50s\t%d\n",s,d)
#define printf_s(s,s2) printf("\t%-50s\t%s\n",s,s2)
#define printf_se(s) printf("\t%-50s\t",s)


Err_ELF_Header read_elf_header(FILE *f, Elf32_Ehdr* hdr);

void display_header(Elf32_Ehdr * Elf);
void display_ident(unsigned char e_ident[]);

void display_class(unsigned char class);
void display_data(unsigned char data);
void display_eiVersion(unsigned char version);
void display_osabi(unsigned char osabi);
void display_type(Elf32_Half type);
void display_machine(Elf32_Half machine);
void display_fileVersion(Elf32_Word version);
void display_verAbi(Elf32_Word flag);

void display_flags(Elf32_Word flag);

#endif
