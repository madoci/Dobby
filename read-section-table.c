#include "elf_header.h"
#include "elf_section_table.h"

int main(int argc, char const *argv[]) {
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
  read_elf_header(f, &header);

  Elf32_Shdr tab_section_hdr[header.e_shnum];
  read_elf_section_table(f, &header, tab_section_hdr);
  
  display_section_header(&header, tab_section_hdr);
  
  fclose(f);
  return 0;
}
