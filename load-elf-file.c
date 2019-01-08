#include <stdlib.h>

#include "elf_load_section.h"

int main(int argc, char const * argv[]){
  if (argc != 2){
    printf("Format : %s <fichier>\n", argv[0]);
    return 1;
  }
  
  FILE *f = fopen(argv[1], "r");
  if (f == NULL){
    printf("Impossible d'ouvrir le fichier \"%s\".\n", argv[1]);
    return 1;
  }

  FILE* output = fopen("output", "w");
  if (output == NULL){
    printf("Impossible d'ouvrir le fichier \"%s\".\n", argv[1]);
    return 1;
  }
  
  Elf32_File src;

  // PENSER
  // A
  // LA
  // GESTION
  // DES
  // ERREURS
  int err_hdr = read_elf_file(f, &src);
  if (err_hdr != 0){
    //printf("Erreur de lecture du header : %s\n.", get_header_error(err_hdr));
    fclose(f);
    return 1;
  }
  
  Elf32_File dest;
  Elf32_Half correl_table[src.header.e_shnum];

  renum_section_elf_file(&dest, src, correl_table);

  reorder_elf_file(&dest);

  write_elf_file(output, dest);
  
  free_elf_file(&src);
  free_elf_file(&dest);

  fclose(f);
  fclose(output);

  return 0;
}