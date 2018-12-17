#include "fread.h"

#include "elf_linker_lib.h"

size_t fread_8bits(void *ptr, size_t nmemb, FILE *stream){
  size_t res = Fread(ptr, 1, nmemb, stream);
  return res;
}

size_t fread_16bits(void *ptr, size_t nmemb, FILE *stream){
  size_t res = Fread(ptr, 2, nmemb, stream);
  if (!is_big_endian()){
    uint16_t *adr = ptr;
    for (int i=0; i<res; i++){
      *adr = reverse_2(*adr);
      ++adr;
    }
  }
  return res;
}

size_t fread_32bits(void *ptr, size_t nmemb, FILE *stream){
  size_t res = Fread(ptr, 4, nmemb, stream);
  if (!is_big_endian()){
    uint32_t *adr = ptr;
    for (int i=0; i<res; i++){
      *adr = reverse_4(*adr);
      ++adr;
    }
  }
  return res;
}
