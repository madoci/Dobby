#include <stdlib.h>
#include <string.h>

#include "elf_load_section.h"
#include "elf_load_symbol.h"


typedef enum {
  ERR_OL_NONE,
  ERR_OL_TOOMANY_O,
  ERR_OL_TOOMANY_S,
  ERR_OL_OUTOFRANGE_O,
  ERR_OL_OUTOFRANGE_S
} Err_Opt_Load;


Err_Opt_Load check_option_index(int argc, int o_ndx, int s_ndx){
  if (o_ndx >= argc){
    return ERR_OL_OUTOFRANGE_O;
  } else if (s_ndx >= argc){
    return ERR_OL_OUTOFRANGE_S;
  }
  return ERR_OL_NONE;
}

Err_Opt_Load get_option_index(int argc, char* argv[], int *o_ndx, int *s_ndx){
  *o_ndx = 0;
  *s_ndx = 0;
  for (int i=2; i<argc; i++){
    if (!strcmp(argv[i], "--output") || !strcmp(argv[i], "-o")){
      if (*o_ndx != 0){
        return ERR_OL_TOOMANY_O;
      }
      *o_ndx = i + 1;
    } else if (!strcmp(argv[i], "--section-start") || !strcmp(argv[i], "-s")){
      if (*s_ndx != 0){
        return ERR_OL_TOOMANY_S;
      }
      *s_ndx = i + 1;
    }
  }
  return check_option_index(argc, *o_ndx, *s_ndx);
}

char* str_opt_load_error(Err_Opt_Load err){
  switch (err){
    case ERR_OL_TOOMANY_O:
      return "Trop d'arguments \"-o\"";
    case ERR_OL_TOOMANY_S:
      return "Trop d'arguments \"-s\"";
    case ERR_OL_OUTOFRANGE_O:
      return "Manque l'argument après -o";
    case ERR_OL_OUTOFRANGE_S:
      return "Manque le ou les arguments après -s";
    default:
      return "";
  }
}

char* get_output_name(char* argv[], int o_ndx){
  char* dest = NULL;
  if (o_ndx == 0){
    int length = 1;
    char* c = argv[1];
    while (*c != '\0' && *c != '.'){
      ++length;
      ++c;
    }
    dest = malloc(sizeof(char) * length);
    memcpy(dest, argv[1], length-1);
    dest[length-1] = '\0';
  } else {
    dest = malloc(sizeof(char) * strlen(argv[o_ndx]));
    memcpy(dest, argv[o_ndx], strlen(argv[o_ndx]));
  }
  return dest;
}

void init_correl_table(Elf32_Half correl_table[], Elf32_Half shnum, Elf32_Half value){
  for (int i=0; i<shnum; i++){
    correl_table[i] = value;
  }
}


int main(int argc, char* argv[]){
  if (argc < 2){
    printf("Format : %s <fichier> <options>\n", argv[0]);
    printf("  Options : -o --output         <Chemin/Du/FichierSortie>\n");
    printf("            -s --section-start  <nome de section>=<adresse> ...\n");
    return 1;
  }

  FILE *f = fopen(argv[1], "r");
  if (f == NULL){
    printf("Impossible d'ouvrir le fichier \"%s\".\n", argv[1]);
    return 1;
  }

  int o_ndx, s_ndx;
  Err_Opt_Load err_opt = get_option_index(argc, argv, &o_ndx, &s_ndx);
  if (err_opt != ERR_OL_NONE){
    printf("Erreur : %s\n", str_opt_load_error(err_opt));
  }

  char* output_name = get_output_name(argv, o_ndx);
  if (output_name == NULL){
    printf("Impossible de récupérer le nom du fichier de sortie\n");
    fclose(f);
    return 1;
  }

  FILE* output = fopen(output_name, "w");
  if (output == NULL){
    printf("Impossible d'ouvrir le fichier \"%s\".\n", output_name);
    fclose(f);
    free(output_name);
    return 1;
  }
  free(output_name);

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
  init_correl_table(correl_table, src.header.e_shnum, 0);

  renum_section_elf_file(&dest, src, correl_table);

  dest.section_table[1].sh_addr = 1;

  unsigned int i;
  for (i=0; i<dest.header.e_shnum; i++){
    if (dest.section_table[i].sh_type == SHT_SYMTAB){
      correct_all_symbol(&dest, i, correl_table);
    }
  }

  reorder_elf_file(&dest);
  write_elf_file(output, dest);

  free_elf_file(&src);
  free_elf_file(&dest);

  fclose(f);
  fclose(output);

  return 0;
}
