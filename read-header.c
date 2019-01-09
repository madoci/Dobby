#include "elf_header.h"

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
  Elf32_Ehdr header;
  Err_ELF_Header error = read_elf_header(f, &header);

  if (error != ERR_EH_NONE){
    printf("Erreur de lecture du header : %s\n", str_Err_ELF_Header(error));
    fclose(f);
    return 1;
  }
  display_header(&header);

  fclose(f);

  return 0;
}
