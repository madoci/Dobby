#ifndef ELF_SECTION_CONTENT_H
#define ELF_SECTION_CONTENT_H

#include <stdio.h>
#include "elf_types_header.h"
#include "elf_types_section.h"

Elf32_Half search_elf_section_num(Elf32_Half shnum, Elf32_Shdr tab[], const char *name, unsigned char* string_table);

unsigned char * read_elf_section_content(FILE *f, Elf32_Shdr shdr);
int read_elf_all_section_content(FILE *f, Elf32_Ehdr hdr, Elf32_Shdr shdr[], unsigned char *tab[]);
void free_all_section_content(unsigned char *tab[], int size);

void write_elf_section_content(FILE *f, Elf32_Shdr shdr, unsigned char *content);
void write_elf_all_section_content(FILE *f, Elf32_Half shnum, Elf32_Shdr shdr[], unsigned char *content[]);

void display_elf_section_content(unsigned char *content, Elf32_Word size);

#endif
