#ifndef BYTES_READER_H
#define BYTES_READER_H

size_t fread_1byte(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t fread_2byte(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t fread_4byte(void *ptr, size_t size, size_t nmemb, FILE *stream);

#endif
