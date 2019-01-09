#include <stdlib.h>

#include "elf_header.h"
#include "elf_section_table.h"
#include "elf_section_content.h"
#include "elf_relocation.h"


int main(int argc, char *argv[]){

  if(argc != 2){
    printf("Format : %s <fichier>\n", argv[0]);
    return 1;
  }

  FILE *f = fopen(argv[1], "r");
  if(f == NULL){
    printf("Impossible d'ouvrir le fichier \"%s\".\n", argv[1]);
    return 1;
  }

  Elf32_Ehdr hdr;
  Err_ELF_Header err_hdr = read_elf_header(f, &hdr);
  if (err_hdr != ERR_EH_NONE){
    printf("Erreur de lecture du header : %s\n.", str_Err_ELF_Header(err_hdr));
    fclose(f);
    return 1;
  }

  Elf32_Shdr shdr[hdr.e_shnum];
  read_elf_section_table(f, &hdr, shdr);

  unsigned char *str_table = NULL;
  str_table = read_elf_section_content(f, shdr[hdr.e_shstrndx]);
  if (str_table == NULL){
    printf("Erreur de lecture du contenu de section.\n");
    fclose(f);
    return 1;
  }

  unsigned int i;
  for (i=0; i<hdr.e_shnum; i++){
    if (shdr[i].sh_type == SHT_REL){
      Elf32_Rel entries[shdr[i].sh_size/sizeof(Elf32_Rel)];
      unsigned char* rel_content = read_elf_section_content(f, shdr[i]);
      read_rel_section(rel_content, &shdr[i], entries);

      display_rel_table(entries, shdr[i].sh_size/sizeof(Elf32_Rel), str_table + shdr[i].sh_name);

      free(rel_content);
    }
    else if (shdr[i].sh_type == SHT_RELA){
      Elf32_Rela entries[shdr[i].sh_size/sizeof(Elf32_Rela)];
      unsigned char* rela_content = read_elf_section_content(f, shdr[i]);
      read_rela_section(rela_content, &shdr[i], entries);

      display_rela_table(entries, shdr[i].sh_size/sizeof(Elf32_Rela), str_table + shdr[i].sh_name);

      free(rela_content);
    }
  }

  free(str_table);
  fclose(f);

  return 0;
}
