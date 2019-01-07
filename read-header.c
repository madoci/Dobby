#include "elf_file.h"
#include "elf_header.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

  if (argc != 2){
    printf("Format : %s <fichier>\n", argv[0]);
    return 1;
  }

  FILE* f = fopen(argv[1], "r");

  if (f == NULL){
    printf("Impossible d'ouvrir le fichier \"%s\".\n", argv[1]);
    return 1;
  }
#ifdef TEST
  Elf32_Ehdr header;
  Err_ELF_Header error = read_elf_header(f, &header);

  if (error != ERR_EH_NONE){
    printf("Erreur de lecture du header : %s\n", get_header_error(error));
    fclose(f);
    return 1;
  }
  display_header(&header);
#else
  Elf32_File ef;
  read_elf_file(f,&ef);
  display_header(&ef.header);
  free_elf_file(&ef);
#endif

  fclose(f);

  return 0;
}
