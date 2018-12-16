#include <stdio.h>
#include "elf.h"

int main(void){
  int result = check_types_size();
  if (result < 0){
    fprintf(stderr, "Error in %s bits type for elf format",
	    (char* []){"unsigned 32","signed 32","16"}[-(result +1)]);
    return -1;
  }
  return 0;
}
