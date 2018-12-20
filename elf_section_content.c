#include "elf_section_content.h"

#include "fread.h"


int compare_name(FILE *f, char *str){
  char *c_str = str;
  char c_f = fgetc(f);
  while (*c_str != '\0' && c_f != '\0' && *c_str == c_f){
  	c_f = fgetc(f);
  	++c_str;
  }
  return (*c_str == c_f);
}


Elf32_Half search_elf_section_num(FILE *f, Elf32_Shdr tab[], Elf32_Ehdr hdr, char *name){
  Elf32_Half num = 0;
  long int str_offset = tab[hdr.e_shstrndx].sh_offset;

  int i;
  for (i=0; i<hdr.e_shnum; i++){
    fseek(f, str_offset + tab[i].sh_name, SEEK_SET);

    if (compare_name(f, name)){
      break;
    }
  }
  num = i;
  return num;
}

unsigned char * read_elf_section_content(FILE *f, Elf32_Shdr shdr){
  unsigned char* shdr_table = malloc(sizeof(unsigned char)*shdr.sh_size);

  fseek(f, shdr.sh_offset, SEEK_SET);
  fread_8bits(shdr_table, shdr.sh_size, f);

  return shdr_table;
}


void display_elf_section_content_by_name(FILE *f, Elf32_Shdr tab[], Elf32_Ehdr hdr, char *name){
  Elf32_Half num = 0;

  num = search_elf_section_num(f, tab, hdr, name);

  if (num == hdr.e_shnum){
    printf("Le nom de section n'existe pas.\n");
    return;
  }

  display_elf_section_content_by_num(f, tab, hdr, num);
}


void display_elf_section_content_by_num(FILE *f, Elf32_Shdr tab[], Elf32_Ehdr hdr, Elf32_Half num){
  if (num < 0 || hdr.e_shnum <= num){
    printf("Le numéro de section n'existe pas.\n");
    return;
  }

  unsigned char * shdr_table = NULL;
  shdr_table = read_elf_section_content(f, tab[num]);

  printf(" ");

  for (int i=0; i<tab[num].sh_size; i++){
  	printf("%02x", *(shdr_table + i));

  	if ((i % 16) == 15){
  		printf("\n ");
  	} else if ((i % 4) == 3){
      printf(" ");
    }
  }
  printf("\n");

  free(shdr_table);
}
