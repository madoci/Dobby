#include <stdio.h>
#include <stdlib.h>
#include "elf_types.h"
#include "elf_file.h"
#include "elf_header.h"
#include "elf_section_content.h"
#include "elf_section_table.h"

int read_elf_file(FILE* f, Elf32_File *ef){
  int err = read_elf_header(f, &(ef->header));

  ef->section_table = NULL;
  ef->section_content = NULL;
  if (err != ERR_EH_NONE){
    return err;
  }

  ef->section_table = malloc(ef->header.e_shentsize * ef->header.e_shnum);
  if (ef->section_table == NULL){
    return -1;
  }
  init_section_table(ef->section_table, ef->header.e_shnum);
  read_elf_section_table(f, &(ef->header), (ef->section_table));

  ef->section_content = malloc(\
        sizeof(unsigned char *) * ef->header.e_shnum);
  if (ef->section_content == NULL){
    free(ef->section_table);
    return -1;
  }
  if (read_elf_all_section_content(f, ef->header, \
          ef->section_table, ef->section_content) == -1){
      free_all_section_content(ef->section_content, \
         ef->header.e_shnum);
      return -1;
  }
  return 0;
}

void write_elf_file(FILE* f, Elf32_File ef){
  write_elf_header(f, ef.header);
  write_elf_section_table(f, ef.header, ef.section_table);
  write_elf_all_section_content(f, ef.header.e_shnum, ef.section_table, ef.section_content);
}

void reorder_elf_file(Elf32_File *ef){
  ef->header.e_shoff = ef->header.e_ehsize;
  ef->section_table[1].sh_offset = ef->header.e_shoff + ef->header.e_shnum * ef->header.e_shentsize;
  for (int i=2; i<ef->header.e_shnum; i++){
    ef->section_table[i].sh_offset = ef->section_table[i-1].sh_offset + ef->section_table[i-1].sh_size;
  }
}

void free_elf_file(Elf32_File* f){
  for (Elf32_Half i = 0; i < f->header.e_shnum;i++){
    free(f->section_content[i]);
  }
  free(f->section_content);
  free(f->section_table);
}
