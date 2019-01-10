#ifndef FREAD_H
#define FREAD_H

#include <stdio.h>
#include <stdlib.h>

/* Functions to read and write an ELF file taking into account the endianess
   of the file and the endianess of the processor */

void set_big_endian();
void set_little_endian();

/* Read nmemb times Xbits from a file and change values pointed by ptr */
size_t fread_8bits(void *ptr, size_t nmemb, FILE *stream);
size_t fread_16bits(void *ptr, size_t nmemb, FILE *stream);
size_t fread_32bits(void *ptr, size_t nmemb, FILE *stream);

/* Write the N (nmemb) values of Xbits pointed by ptr in a file */
size_t fwrite_8bits(void *ptr, size_t nmemb, FILE *stream);
size_t fwrite_16bits(void *ptr, size_t nmemb, FILE *stream);
size_t fwrite_32bits(void *ptr, size_t nmemb, FILE *stream);

/* Read nmemb times Xbits from a string and change values pointed by ptr */
void read_8bits(void *ptr, unsigned char* string);
void read_16bits(void *ptr, unsigned char* string);
void read_32bits(void *ptr, unsigned char* string);

/* Write the N (nmemb) values of Xbits pointed by ptr in a string */
void write_8bits(unsigned char* string, void *ptr);
void write_16bits(unsigned char* string, void *ptr);
void write_32bits(unsigned char* string, void *ptr);

#endif
