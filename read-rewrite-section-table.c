#include <stdlib.h>

#include "rewrite_section_table.h"
#include "elf_section_table.h"
#include "elf_section_content.h"


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
  
  Elf32_Ehdr header;
  Err_ELF_Header err_hdr = read_elf_header(f, &header);
  if (err_hdr != ERR_EH_NONE){
    printf("Erreur de lecture du header : %s\n.", get_header_error(err_hdr));
    fclose(f);
    return 1;
  }
  
  Elf32_Shdr e_table[header.e_shnum];
  read_elf_section_table(f, &header, e_table);
  
  unsigned char *string_table = read_elf_section_content(f, e_table[header.e_shstrndx]);
  
#ifdef DEBUG
  puts("OLD");
  display_section_table(&header, e_table, string_table);
#endif
  
  Elf32_Half new_shnum = count_shnum(e_table, header.e_shnum);
  
#ifdef DEBUG
  printf("%d section headers without rela on %d sections header\n", new_shnum, header.e_shnum);
#endif
  
  Elf32_Shdr new_e_table[new_shnum];
  Elf32_Half correl_table[header.e_shnum];
  
  rewrite_section_table(e_table, header.e_shnum, new_e_table, correl_table);
  
  Elf32_Ehdr new_header = header;
  correct_header(&new_header, new_shnum, correl_table);
  correct_symtab_header(new_e_table, new_shnum, correl_table);

#ifdef DEBUG
  puts("NEW");
#endif
  
  display_section_table(&new_header, new_e_table, string_table);
  
  free(string_table);
  fclose(f);
  
  return 0;
}
