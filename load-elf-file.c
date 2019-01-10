#include <stdlib.h>
#include <string.h>

#include "elf_load_section.h"
#include "elf_load_symbol.h"
#include "elf_load_reloc.h"


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

const char* str_Err_Opt_Load(Err_Opt_Load err){
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

int get_last_s_index(int argc, int o_ndx, int s_first){
  if (s_first == 0){
    return 0;
  } else if (o_ndx < s_first){
    return argc - 1;
  } else {
    return o_ndx - 2;
  }
}

char* get_output_name(char* argv[], int o_ndx){
  char* dest = NULL;
  if (o_ndx == 0){
    int length = 1;
    char* c = argv[1];
    char* stop = strrchr(c, '.');
    while (*c != '\0' && c != stop){
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

Elf32_Addr string_to_addr(const char* string){
  if (string == NULL || string[0] == '\0'){
    return 0;
  } else if (string[0] == '0' && string[1] == 'x'){
    return (Elf32_Addr) strtol(string, NULL, 0);
  } else {
    return (Elf32_Addr) atoi(string);
  }
}

void manage_section_option(Elf32_File* ef, char* argv[], int s_first, int s_last){
  if (s_first == 0){
  	return;
  }
  for (int i=s_first; i<=s_last; i++){
    char* separator = strchr(argv[i], '=');
    if (separator == NULL){
      printf("Argument invalide : <nom de section>=<adresse>\n");
      continue;
    }
    int sep_ndx = strlen(argv[i]) - strlen(separator);
    char* section_name = malloc(sizeof(char) * sep_ndx);
    if (section_name == NULL){
      printf("Erreur d'allocation mémoire.\n");
      continue;
    }
    memmove(section_name, argv[i], sep_ndx);
    Elf32_Addr addr = string_to_addr(separator+1);
    if (change_section_address(ef, section_name, addr)){
      printf("La section \"%s\" n'existe pas.\n", section_name);
    }
    free(section_name);
  }
}


int main(int argc, char* argv[]){
  if (argc < 2){
    printf("Format : %s <fichier> <options>\n", argv[0]);
    printf("  Options : -o --output         <Chemin/Du/FichierSortie>\n");
    printf("            -s --section-start  <nom de section>=<adresse> ...\n");
    return -1;
  }

  FILE *f = fopen(argv[1], "r");
  if (f == NULL){
    printf("Impossible d'ouvrir le fichier \"%s\".\n", argv[1]);
    return -1;
  }

  int o_ndx, s_first, s_last;
  Err_Opt_Load err_opt = get_option_index(argc, argv, &o_ndx, &s_first);
  if (err_opt != ERR_OL_NONE){
    printf("Erreur : %s\n", str_Err_Opt_Load(err_opt));
    return -1;
  }
  s_last = get_last_s_index(argc, o_ndx, s_first);

  char* output_name = get_output_name(argv, o_ndx);
  if (output_name == NULL){
    printf("Impossible de récupérer le nom du fichier de sortie\n");
    fclose(f);
    return -1;
  }

  FILE* output = fopen(output_name, "w");
  if (output == NULL){
    printf("Impossible d'ouvrir le fichier de sortie \"%s\".\n", output_name);
    fclose(f);
    free(output_name);
    return -1;
  }
  free(output_name);

  Elf32_File src;
  Err_ELF_File err_ef = read_elf_file(f, &src);
  if (err_ef != ERR_EF_NONE){
    printf("Erreur de lecture du fichier ELF : %s\n.", str_Err_ELF_File(err_ef));
    fclose(f);
    return -1;
  }

  Elf32_File dest;
  Elf32_Half correl_table[src.header.e_shnum];
  init_correl_table(correl_table, src.header.e_shnum, 0);

  renum_section_elf_file(&dest, src, correl_table);

  manage_section_option(&dest, argv, s_first, s_last);

  unsigned int i_symtab;
  for (i_symtab=0; i_symtab<dest.header.e_shnum; i_symtab++){
    if (dest.section_table[i_symtab].sh_type == SHT_SYMTAB){
      break;
    }
  }

  Elf32_Half correl_symbol[dest.section_table[i_symtab].sh_size/sizeof(Elf32_Sym)];
  correct_all_symbol(&dest, i_symtab, correl_table, correl_symbol);

  for (Elf32_Half i = 0; i < src.header.e_shnum; i++){
    if (src.section_table[i].sh_type == SHT_REL){
      Elf32_Shdr reloc_shdr = src.section_table[i];
      reloc_shdr.sh_link = correl_table[reloc_shdr.sh_link];
      reloc_shdr.sh_info = correl_table[reloc_shdr.sh_info];
      execute_relocation_section(&dest, reloc_shdr, src.section_content[i], correl_symbol);
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
