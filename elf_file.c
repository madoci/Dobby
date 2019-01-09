#include <stdio.h>
#include <stdlib.h>

#include "elf_types.h"
#include "elf_file.h"
#include "elf_header.h"
#include "elf_section_content.h"
#include "elf_section_table.h"


Err_ELF_File read_elf_file(FILE* f, Elf32_File *ef){
  ef->section_table = NULL;
  ef->section_content = NULL;

  int err_eh = read_elf_header(f, &(ef->header));
  if (err_eh != ERR_EH_NONE){
    return (Err_ELF_File) err_eh;
  }

  ef->section_table = malloc(ef->header.e_shentsize * ef->header.e_shnum);
  if (ef->section_table == NULL){
    return ERR_EF_MALLOC;
  }

  init_section_table(ef->section_table, ef->header.e_shnum);
  read_elf_section_table(f, &(ef->header), (ef->section_table));

  ef->section_content = malloc(sizeof(unsigned char *) * ef->header.e_shnum);
  if (ef->section_content == NULL){
    free(ef->section_table);
    return ERR_EF_MALLOC;
  }

  if (read_elf_all_section_content(f, ef->header, ef->section_table, ef->section_content) == -1){
      free_all_section_content(ef->section_content, ef->header.e_shnum);
      return ERR_EF_CONTENT;
  }

  return ERR_EF_NONE;
}


const char* str_Err_ELF_File(Err_ELF_File err){
  switch (err){
    case ERR_EF_EH_IMAG:
    case ERR_EF_EH_ICLASS:
    case ERR_EF_EH_IDATA:
    case ERR_EF_EH_IVERSION:
    case ERR_EF_EH_IOSABI:
    case ERR_EF_EH_IPAD:
    case ERR_EF_EH_TYPE:
    case ERR_EF_EH_MACHINE:
    case ERR_EF_EH_VERSION:
    case ERR_EF_EH_FLAGS:
      return str_Err_ELF_Header((Err_ELF_Header) err);
    case ERR_EF_MALLOC:
      return "ERR_EF_MALLOC";
    case ERR_EF_CONTENT:
      return "ERR_EF_CONTENT";
    case ERR_EF_NONE:
      return "ERR_EF_NONE";
    default:
      return "";
  }
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
  if (f != NULL){
    for (Elf32_Half i = 0; i < f->header.e_shnum;i++){
      free(f->section_content[i]);
    }
    free(f->section_content);
    free(f->section_table);
  }
}
