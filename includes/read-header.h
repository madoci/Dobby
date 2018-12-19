#ifndef READ_HEADER_H
#define READ_HEADER_H
#include "elf_types_atomic.h"

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
