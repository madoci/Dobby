#include <stdio.h>
#include "elf_section_table.h"

int main(int argc, char const *argv[]) {

  if (argc != 2){
  	printf("Format : %s <fichier>\n", argv[0]);
  	return 1;
  }

  FILE * f;
  f = fopen(argv[1], "r");

  if (f == NULL){
  	printf("Impossible d'ouvrir le fichier \"%s\".\n", argv[1]);
  	return 1;
  }

  display_section_header(f);
  fclose(f);

  return 0;
}
