#include <stdio.h>
#include "elf_section.h"

int main(int argc, char const *argv[]) {

  FILE * f;
  f = fopen(argv[1], "r");
  display_section_header(f);
  fclose(f);

  return 0;
}
