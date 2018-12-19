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


void display_elf_section_content_by_name(FILE *f, Elf32_Shdr tab[], Elf32_Ehdr hdr, char *name){
  Elf32_Half num = 0;
  long int str_offset = tab[hdr.e_shstrndx].sh_offset;

  int i;
  for (i=0; i<hdr.e_shnum; i++){
  	fseek(f, str_offset + tab[i].sh_name, SEEK_SET);

  	if (compare_name(f, name)){
      num = i;
      break;
  	}
  }

  if (i == hdr.e_shnum){
    printf("Le nom de section n'existe pas.\n");
    return;
  }

  read_elf_section_content_by_num(f, tab, hdr, num);
}


void display_elf_section_content_by_num(FILE *f, Elf32_Shdr tab[], Elf32_Ehdr hdr, Elf32_Half num){
  if (num < 0 || hdr.e_shnum <= num){
    printf("Le numéro de section n'existe pas.\n");
    return;
  }

  fseek(f, tab[num].sh_offset, SEEK_SET);
  unsigned char c;

  for (int i=0; i<tab[num].sh_size; i++){
  	fread_8bits(&c, 1, f);
  	printf("%02x", c);

  	if ((i % 16) == 15){
  		printf("\n");
  	} else if ((i % 4) == 3){
      printf(" ");
    }
  }

  printf("\n");
}
