#include <stdlib.h>

#include "rewrite_section_table.h"
#include "elf_section_table.h"
#include "elf_section_content.h"
#include "elf_file.h"


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
  
  Elf32_File src;

  // PENSER
  // A
  // LA
  // GESTION
  // DES
  // ERREURS

  int err_hdr = read_elf_file(f, &src);
  if (err_hdr != 0){
    printf("Erreur de lecture du header : %s\n.", get_header_error(err_hdr));
    fclose(f);
    return 1;
  }
  
#ifdef DEBUG
  puts("OLD");
  display_section_table(&src.header, src.section_table, src.section_content[src.header.e_shstrndx]);
#endif
  
  Elf32_File dest;
  dest.header = src.header;
  dest.header.e_shnum = count_shnum(src.section_table, src.header.e_shnum);
  
#ifdef DEBUG
  printf("%d section headers without rela on %d sections header\n", dest.header.e_shnum, src.header.e_shnum);
#endif
  
  dest.section_table = malloc(sizeof(Elf32_Shdr) * dest.header.e_shnum);

  Elf32_Half correl_table[src.header.e_shnum];
  
  rewrite_section_table(src.section_table, src.header.e_shnum, dest.section_table, dest.header.e_shnum, correl_table);
  
  correct_header(&(dest.header), dest.header.e_shnum, correl_table);
  correct_symtab_header(dest.section_table, dest.header.e_shnum, correl_table);

#ifdef DEBUG
  puts("NEW");
  display_section_table(&(dest.header), dest.section_table, src.section_content[src.header.e_shstrndx]);
#endif

  FILE* output = fopen("output", "w");

  dest.section_content = malloc(sizeof(unsigned char*) * dest.header.e_shnum);
  dest.section_content[0] = src.section_content[0];
  unsigned int k = 1;
  for (int i=1; i<src.header.e_shnum; i++){
    if(src.section_table[i].sh_type != SHT_RELA && src.section_table[i].sh_type != SHT_REL && src.section_table[i].sh_size != 0){
      dest.section_content[k] = src.section_content[i];
      ++k;
    }
  }

  reorder_elf_file(&dest);
  write_elf_file(output, dest);
  
  free_elf_file(&src);
  free(dest.section_table);
  free(dest.section_content);

  fclose(output);
  fclose(f);
  
  return 0;
}
