#ifndef FREAD_H
#define FREAD_H

#include <stdio.h>
#include <stdlib.h>

size_t fread_8bits(void *ptr, size_t nmemb, FILE *stream);
size_t fread_16bits(void *ptr, size_t nmemb, FILE *stream);
size_t fread_32bits(void *ptr, size_t nmemb, FILE *stream);

#endif
