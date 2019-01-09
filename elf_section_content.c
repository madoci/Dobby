#include "elf_section_content.h"

#include <string.h>
#include "elf_io.h"


/* READ SECTION CONTENT */

int compare_name(FILE *f, char *str){
  char *c_str = str;
  char c_f = fgetc(f);
  while (*c_str != '\0' && c_f != '\0' && *c_str == c_f){
    c_f = fgetc(f);
    ++c_str;
  }
  return (*c_str == c_f);
}


Elf32_Half search_elf_section_num(Elf32_Half shnum, Elf32_Shdr tab[], const char *name, unsigned char* string_table){
  Elf32_Half i;
  for (i=0; i<shnum; i++){
    char* ptr_name = (char*) (string_table + tab[i].sh_name);
    if (!strcmp(name, ptr_name)){
      break;
    }
  }
  return i;
}


unsigned char * read_elf_section_content(FILE *f, Elf32_Shdr shdr){
  unsigned char* shdr_table = malloc(sizeof(unsigned char)*shdr.sh_size);
  if (shdr_table == NULL){
    return NULL;
  }
  fseek(f, shdr.sh_offset, SEEK_SET);
  fread_8bits(shdr_table, shdr.sh_size, f);

  return shdr_table;
}


int read_elf_all_section_content(FILE *f, Elf32_Ehdr hdr, Elf32_Shdr shdr[], unsigned char *tab[]){
  tab[0] = NULL;
  for (Elf32_Half i = 1; i < hdr.e_shnum; i++){
    tab[i] = NULL;
    tab[i] = read_elf_section_content(f, shdr[i]);
    if (tab[i] == NULL){
      return -1;
    }
  }
  return 0;
}


void free_all_section_content(unsigned char *tab[], int size){
  for (int i=0; i<size; i++){
    if (tab[i] != NULL){
      free(tab[i]);
    }
  }
}


/* WRITE SECTION CONTENT */

void write_elf_section_content(FILE *f, Elf32_Shdr shdr, unsigned char *content){
  fseek(f, shdr.sh_offset, SEEK_SET);
  fwrite_8bits(content, shdr.sh_size, f);
}


void write_elf_all_section_content(FILE *f, Elf32_Half shnum, Elf32_Shdr shdr[], unsigned char *content[]){
  unsigned int i;
  for (i=1; i<shnum; i++){
    write_elf_section_content(f, shdr[i], content[i]);
  }
}


/* DISPLAY SECTION CONTENT */

void display_elf_section_content(unsigned char *content, Elf32_Word size){
  for (int i=0; i<size; i++){
    if ((i % 16) == 0){
      printf("\n ");
    } else if ((i % 4) == 0){
      printf(" ");
    }
    printf("%02x", *(content + i));
  }
  printf("\n ");
}
