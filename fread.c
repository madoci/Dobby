#include <stdint.h>
#include <string.h>

#include "fread.h"
#include "util.h"


static char isBigEndian;

void set_big_endian(){
  isBigEndian = 1;
}

void set_little_endian(){
  isBigEndian = 0;
}


/* FILE READ */

size_t fread_8bits(void *ptr, size_t nmemb, FILE *stream){
  size_t res = fread(ptr, 1, nmemb, stream);
  return res;
}

size_t fread_16bits(void *ptr, size_t nmemb, FILE *stream){
  size_t res = fread(ptr, 2, nmemb, stream);
  if (is_big_endian() != isBigEndian){
    uint16_t *adr = ptr;
    for (int i=0; i<res; i++){
      *adr = reverse_2(*adr);
      ++adr;
    }
  }
  return res;
}

size_t fread_32bits(void *ptr, size_t nmemb, FILE *stream){
  size_t res = fread(ptr, 4, nmemb, stream);
  if (is_big_endian() != isBigEndian){
    uint32_t *adr = ptr;
    for (int i=0; i<res; i++){
      *adr = reverse_4(*adr);
      ++adr;
    }
  }
  return res;
}


/* FILE WRITE */

size_t fwrite_8bits(void *ptr, size_t nmemb, FILE *stream){
  size_t res = fwrite(ptr, 1, nmemb, stream);
  return res;
}

size_t fwrite_16bits(void *ptr, size_t nmemb, FILE *stream){
  uint16_t adr[nmemb];
  memmove(adr, ptr, 2 * nmemb);

  if (is_big_endian() != isBigEndian){
    uint16_t *tmp = adr;
    for (int i=0; i<nmemb; i++){
      *tmp = reverse_2(*tmp);
      ++tmp;
    }
  }

  size_t res = fwrite(adr, 2, nmemb, stream);
  return res;
}

size_t fwrite_32bits(void *ptr, size_t nmemb, FILE *stream){
  uint32_t adr[nmemb];
  memmove(adr, ptr, 4 * nmemb);

  if (is_big_endian() != isBigEndian){
    uint32_t *tmp = adr;
    for (int i=0; i<nmemb; i++){
      *tmp = reverse_4(*tmp);
      ++tmp;
    }
  }

  size_t res = fwrite(adr, 4, nmemb, stream);
  return res;
}


/* STRING READ */

void read_8bits(void *ptr, unsigned char* string){
  uint8_t *adr = ptr;
  *adr = *((uint8_t*) string);
}

void read_16bits(void *ptr, unsigned char* string){
  uint16_t *adr = ptr;
  *adr = *((uint16_t*) string);
  if (is_big_endian() != isBigEndian){
    *adr = reverse_2(*adr);
  }
}

void read_32bits(void *ptr, unsigned char* string){
  uint32_t *adr = ptr;
  *adr = *((uint32_t*) string);
  if (is_big_endian() != isBigEndian){
    *adr = reverse_4(*adr);
  }
}


/* STRING WRITE */

void write_8bits(unsigned char* string, void *ptr){
  uint8_t *adr = ptr;
  memmove(string, adr, 1); //*string = *((unsigned char*) adr);
}

void write_16bits(unsigned char* string, void *ptr){
  uint16_t *adr = NULL;
  memmove(adr, ptr, 2);

  if (is_big_endian() != isBigEndian){
    *adr = reverse_2(*adr);
  }

  memmove(string, adr, 2);
}

void write_32bits(unsigned char* string, void *ptr){
  uint32_t *adr = NULL;
  memmove(adr, ptr, 4);

  if (is_big_endian() != isBigEndian){
    *adr = reverse_4(*adr);
  }

  memmove(string, adr, 4);
}
