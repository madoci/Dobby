#include <stdint.h>

#include "fread.h"
#include "util.h"

static char isBigEndian;

void set_big_endian(){
  isBigEndian = 1;
}

void set_little_endian(){
  isBigEndian = 0;
}

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
