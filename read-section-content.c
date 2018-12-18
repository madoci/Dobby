#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "elf_header.h"
#include "elf_section.h"
#include "elf_section_content.h"


typedef enum {
  SELSECTION_OPT_NONE,
  SELSECTION_OPT_NAME,
  SELSECTION_OPT_NUM
} SelSection_Option;


int main(int argc, char* argv[]){
  if (argc != 4){
	printf("Arguments invalides : %s <nom du fichier> -<s|i> <section>\n", argv[0]);
	return -1;
  }

  int sel_i = 0;
  SelSection_Option opt = SELSECTION_OPT_NONE;
  for (int i=1; i < argc-1; i++){
  	if (!strcmp(argv[i], "-s")){
  	  sel_i = i + 1;
      opt = SELSECTION_OPT_NAME;
  	} else if (!strcmp(argv[i], "-i")) {
  	  sel_i = i + 1;
  	  opt = SELSECTION_OPT_NUM;
  	}
  }
  if (opt == SELSECTION_OPT_NONE){
  	printf("Option manquante :\n");
  	printf("-s : section donnée par son nom\n");
  	printf("-i : section donnée par son numéro\n");
  	return -1;
  }

  int sel_f = 0;
  if (sel_i == 2){
  	sel_f = 3;
  } else {
  	sel_f = 1;
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
  	return -1;
  }

  Elf32_Shdr sh_tab[hdr.e_shnum];
  read_elf_section_table(f, &hdr, sh_tab);

  int num;
  switch (opt){
  	case SELSECTION_OPT_NAME:
      read_elf_section_content_by_name(f, sh_tab, hdr, argv[sel_i]);
      break;
    case SELSECTION_OPT_NUM:
      num = atoi(argv[sel_i]);
      read_elf_section_content_by_num(f, sh_tab, hdr, num);
      break;
    default:;
  }

  return 0;
}