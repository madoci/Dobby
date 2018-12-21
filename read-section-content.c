#include <stdlib.h>
#include <string.h>

#include "elf_header.h"
#include "elf_section_table.h"
#include "elf_section_content.h"


typedef enum {
    SELSECTION_OPT_NONE,
    SELSECTION_OPT_NAME,
    SELSECTION_OPT_NUM
} SelSection_Option;


SelSection_Option get_option(int argc, char *argv[], int *argopt, int *argfile){
  SelSection_Option opt = SELSECTION_OPT_NONE;

  for (int i=1; i < argc-1; i++){
    if (!strcmp(argv[i], "-s")){
      *argopt = i + 1;
      opt = SELSECTION_OPT_NAME;
    } else if (!strcmp(argv[i], "-i")) {
      *argopt = i + 1;
      opt = SELSECTION_OPT_NUM;
    }
  }

  *argfile = (*argopt == 2) ? 3 : 1;

  return opt;
}


int get_num(){
  int num = -1;
  if (opt == SELSECTION_OPT_NAME){
    num = search_elf_section_num(f, sh_tab, hdr, argv[sel_i]);
    if (num == hdr.e_shnum){
      printf("Le nom de section n'existe pas.\n");
    }
  } else {
    num = atoi(argv[sel_i]);
    if (num < 0 || hdr.e_shnum <= num){
      printf("Le numéro de section n'existe pas.\n");
      return -1;
    }
  }
}

int main(int argc, char *argv[]){
  if (argc != 4){
    printf("Format : %s <nom du fichier> -<s|i> <section>\n", argv[0]);
    return -1;
  }

  int sel_num = -1;
  int sel_file = -1;
  SelSection_Option opt = get_option(argc, argv, &sel_num, &sel_file);
  if (opt == SELSECTION_OPT_NONE){
    printf("Option manquante :\n");
    printf("-s : section donnée par son nom\n");
    printf("-i : section donnée par son numéro\n");
    return -1;
  }

  FILE *f = fopen(argv[sel_f], "r");
  if (f == NULL){
    printf("Impossible d'ouvrir le fichier \"%s\".\n", argv[sel_f]);
    return -1;
  }

  Elf32_Ehdr hdr;
  Err_ELF_Header err_hdr = read_elf_header(f, &hdr);
  if (err_hdr != ERR_EH_NONE){
    printf("Erreur de lecture du header : %d\n.", err_hdr);
    fclose(f);
    return -1;
  }

  Elf32_Shdr sh_tab[hdr.e_shnum];
  read_elf_section_table(f, &hdr, sh_tab);

  int num = -1;
  if (opt == SELSECTION_OPT_NAME){
    num = search_elf_section_num(f, sh_tab, hdr, argv[sel_i]);
    if (num == hdr.e_shnum){
      printf("Le nom de section n'existe pas.\n");
      return -1;
    }
  } else {
    num = atoi(argv[sel_i]);
    if (num < 0 || hdr.e_shnum <= num){
      printf("Le numéro de section n'existe pas.\n");
      return -1;
    }
  }

  unsigned char *content = read_elf_section_content(f, sh_tab[num]);
  display_elf_section_content(content, sh_tab[num].sh_size);

  free(content);
  fclose(f);

  return 0;
}
