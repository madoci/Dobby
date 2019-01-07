#include <stdio.h>
#include <stdlib.h>
#include "elf_types.h"
#include "elf_file.h"
#include "elf_header.h"
#include "elf_section_content.h"
#include "elf_section_table.h"

int read_elf_file(FILE* f,Elf32_File *ef){
  int err = read_elf_header(f,&(ef->header));

  ef->section_table=NULL;
  ef->section_content=NULL;
  if (err != ERR_EH_NONE){
    return err;
  }

  ef->section_table = malloc(ef->header.e_shentsize*ef->header.e_shnum);
  if (ef->section_table==NULL){
    return -1;
  }
  init_section_table(ef->section_table, ef->header.e_shnum);
  read_elf_section_table(f,&(ef->header),(ef->section_table));

  ef->section_content = malloc(\
        sizeof(unsigned char *)*ef->header.e_shnum);
  if (ef->section_content == NULL){
    free(ef->section_table);
    return -1;
  }
  if (read_elf_all_section_content(f,ef->header,\
          ef->section_table,ef->section_content) == -1){
      free_all_section_content(ef->section_content,\
         ef->header.e_shnum);
      return -1;
  }
  return 0;
}

int free_elf_file(Elf32_File* f){
  return (int) f;
}
