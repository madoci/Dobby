#include <stdlib.h>

#include "elf_header.h"
#include "elf_section_table.h"
#include "elf_section_content.h"

int main(int argc, char *argv[]) {
  if (argc != 2){
    printf("Format : %s <fichier>\n", argv[0]);
    return 1;
  }

  FILE *f = fopen(argv[1], "r");
  if (f == NULL){
    printf("Impossible d'ouvrir le fichier \"%s\".\n", argv[1]);
    return 1;
  }

  Elf32_Ehdr header;
  Err_ELF_Header err_hdr = read_elf_header(f, &header);
  if (err_hdr != ERR_EH_NONE){
    printf("Erreur de lecture du header : %s\n.", str_Err_ELF_Header(err_hdr));
    fclose(f);
    return 1;
  }

  Elf32_Shdr tab_section_hdr[header.e_shnum];
  init_section_table(tab_section_hdr, header.e_shnum);
  read_elf_section_table(f, &header, tab_section_hdr);

  unsigned char *str_table = NULL;
  str_table = read_elf_section_content(f, tab_section_hdr[header.e_shstrndx]);
  if (str_table == NULL){
    printf("Erreur de lecture du contenu de section.\n");
    fclose(f);
    return 1;
  }

  display_section_table(&header, tab_section_hdr, str_table);

  free(str_table);
  fclose(f);

  return 0;
}
