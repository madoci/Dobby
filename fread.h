#ifndef FREAD_H
#define FREAD_H

size_t fread_8bits(void *ptr, size_t nmemb, FILE *stream);
size_t fread_16bits(void *ptr, size_t nmemb, FILE *stream);
size_t fread_32bits(void *ptr, size_t nmemb, FILE *stream);

#endif
