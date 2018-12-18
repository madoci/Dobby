#include "elf_section_content.h"

#include <stdio.h>
#include "fread.h"
#include "elf_header.h"
#include "elf_section.h"


int compare_name(FILE *f, char *str){
  char *c_str = str;
  char c_f = fgetc(f);
  while (*c_str != '\0' && c_f != '\0' && *c_str == c_f){
  	c_f = fgetc(f);
  	++c_str;
  }
  return (*c_str == c_f);
}

void read_elf_section_content_by_name(FILE *f, Elf32_Shdr tab[], Elf32_Ehdr hdr, char *name){
  Elf32_Half num;
  long int str_offset = tab[hdr.e_shstrndx].sh_offset;
  for (int i=0; i<hdr.e_shnum; i++){
  	fseek(f, str_offset + tab[i].sh_name, SEEK_SET);
  	if (compare_name(f, name)){
      num = i;
      break;
  	}
  }
  read_elf_section_content_by_num(f, tab, hdr, num);
}

void read_elf_section_content_by_num(FILE *f, Elf32_Shdr tab[], Elf32_Ehdr hdr, Elf32_Half num){
  fseek(f, tab[num].sh_offset, SEEK_SET);
  char c;
  for (int i=0; i<tab[num].sh_size; i++){
  	fread_8bits(&c, 1, f);
  	printf("%02x ", c);
  	if ((i % 16) == 15){
  		printf("\n");
  	}
  }
}

int main(int argc, char* argv[]){
	FILE *f = fopen(argv[1], "r");
	Elf32_Ehdr hdr;
	read_elf_header(f, &hdr);
	Elf32_Shdr sh_tab[hdr.e_shnum];
	read_elf_section_table(f, &hdr, sh_tab);
	read_elf_section_content_by_name(f, sh_tab, hdr, argv[2]);
	return 0;
}