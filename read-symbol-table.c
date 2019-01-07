#include <stdlib.h>

#include "elf_header.h"
#include "elf_section_table.h"
#include "elf_section_content.h"
#include "elf_symbol.h"


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

  Elf32_Ehdr hdr;
  Err_ELF_Header err_hdr = read_elf_header(f, &hdr);
  if (err_hdr != ERR_EH_NONE){
    printf("Erreur de lecture du header : %s\n.", get_header_error(err_hdr));
    fclose(f);
    return 1;
  }

  Elf32_Shdr s_table[hdr.e_shnum];
  read_elf_section_table(f, &hdr, s_table);

  unsigned char *str_section = NULL;
  str_section = read_elf_section_content(f, s_table[hdr.e_shstrndx]);
  if (str_section == NULL){
    printf("Erreur de lecture du contenu de section.\n");
    fclose(f);
    return 1;
  }

  unsigned char *string_table = NULL;
  unsigned int i;
  for (i=0; i<hdr.e_shnum; i++){
    if (s_table[i].sh_type == SHT_SYMTAB){
      string_table = read_elf_section_content(f, s_table[s_table[i].sh_link]);
      if (string_table == NULL){
        printf("Erreur de lecture du contenu de section.\n");
        fclose(f);
        return 1;
      }
      
      const unsigned int num_symbols = s_table[i].sh_size / sizeof(Elf32_Sym);
      
      Elf32_Sym sym_table[num_symbols];
      read_elf_symbol_table(f, &s_table[i], sym_table);

      display_symbol_table(sym_table, num_symbols, string_table, str_section + s_table[i].sh_name);
      
      free(string_table);
    }
  }
  
  free(str_section);
  fclose(f);
  
  return 0;
}
