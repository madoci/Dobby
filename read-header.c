#include "elf_file.h"


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
<<<<<<< HEAD
#ifdef TEST
=======

>>>>>>> 84c0458d5398c4cf589f07a82f7c9f0d0cfc357e
  Elf32_Ehdr header;
  Err_ELF_Header error = read_elf_header(f, &header);

  if (error != ERR_EH_NONE){
    printf("Erreur de lecture du header : %s\n", get_header_error(error));
    fclose(f);
    return 1;
  }
<<<<<<< HEAD
  display_header(&header);
#else
#endif TEST
=======

  display_header(&header);
>>>>>>> 84c0458d5398c4cf589f07a82f7c9f0d0cfc357e

  fclose(f);

  return 0;
}
