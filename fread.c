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
