#ifndef FREAD_H
#define FREAD_H

#include <stdio.h>
#include <stdlib.h>

void set_big_endian();
void set_little_endian();

size_t fread_8bits(void *ptr, size_t nmemb, FILE *stream);
size_t fread_16bits(void *ptr, size_t nmemb, FILE *stream);
size_t fread_32bits(void *ptr, size_t nmemb, FILE *stream);

size_t fwrite_8bits(void *ptr, size_t nmemb, FILE *stream);
size_t fwrite_16bits(void *ptr, size_t nmemb, FILE *stream);
size_t fwrite_32bits(void *ptr, size_t nmemb, FILE *stream);

void read_8bits(void *ptr, unsigned char* string);
void read_16bits(void *ptr, unsigned char* string);
void read_32bits(void *ptr, unsigned char* string);

void write_8bits(unsigned char* string, void *ptr);
void write_16bits(unsigned char* string, void *ptr);
void write_32bits(unsigned char* string, void *ptr);

#endif
