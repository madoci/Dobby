#ifndef ELF_TYPES_SYMBOL_H
#define ELF_TYPES_SYMBOL_H

#include "elf_types_atomic.h"

/* Symbol table page 23 fig 1-16 */

typedef struct {
  Elf32_Word st_name;
  Elf32_Addr st_value;
  Elf32_Word st_size;
  unsigned char st_info;
  unsigned char st_other;
  Elf32_Half st_shndx;
} Elf32_Sym;

enum Elf_StBind {
  STB_LOCAL  = 0,
  STB_GLOBAL = 1,
  STB_WEAK   = 2,
  STB_LOPROC = 13,
  STB_HIPROC = 15
};

enum Elf_StType{
  STT_NOTYPE  = 0,
  STT_OBJECT  = 1,
  STT_FUNC    = 2,
  STT_SECTION = 3,
  STT_FILE    = 4,
  STT_LOPROC  = 13,
  STT_HIPROC  = 15
};

#define ELF32_ST_BIND(i) ((i) >>4)
#define ELF32_ST_TYPE(i) ((i) &0xf)
#define ELF32_ST_INFO(b,t) ((b)<<4+((t)&0xf))

#endif
