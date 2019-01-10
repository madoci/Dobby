#ifndef ELF_SECTION_CONTENT_H
#define ELF_SECTION_CONTENT_H

#include <stdio.h>
#include "elf_types_header.h"
#include "elf_types_section.h"

/* Return index of a section given by its name
   Return 0 if not found */
Elf32_Half search_elf_section_num(Elf32_Half shnum, Elf32_Shdr tab[], const char *name, unsigned char* string_table);

/* Return a string of a section's content read from an ELF file */
unsigned char * read_elf_section_content(FILE *f, Elf32_Shdr shdr);

/* Read all section's contents of an ELF file and fill the table tab */
int read_elf_all_section_content(FILE *f, Elf32_Ehdr hdr, Elf32_Shdr shdr[], unsigned char *tab[]);

/* Free all allocated memory of section's contents table */
void free_all_section_content(unsigned char *tab[], int size);

/* Write a string of a section's content in file */
void write_elf_section_content(FILE *f, Elf32_Shdr shdr, unsigned char *content);

/* Write all section's contents in a file */
void write_elf_all_section_content(FILE *f, Elf32_Half shnum, Elf32_Shdr shdr[], unsigned char *content[]);

/* Display a string of a section's content */
void display_elf_section_content(unsigned char *content, Elf32_Word size);

#endif
