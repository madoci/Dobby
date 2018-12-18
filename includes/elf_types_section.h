#ifndef ELF_TYPES_SECTION_H
#define ELF_TYPES_SECTION_H

#include "elf_types_atomic.h"

/* Sections data types */

//Undefined section
enum Elf_SIndex{
  SHN_UNDEF     = 0,
  SHN_LORESERVE = 0xff00,
  SHN_LOPROC    = 0xff00,
  SHN_HIPROC    = 0xff1f,
  SHN_ABS       = 0xfff1,
  SHN_COMMON    = 0xfff2,
  SHN_HIRESERVE = 0xffff
};

typedef struct {
  Elf32_Word sh_name; //Index into section header string table
  Elf32_Word sh_type; //Section type
  Elf32_Word sh_flags;
  Elf32_Addr sh_addr;//If != 0, Adress where section must be placed in memory
  Elf32_Word sh_offset;//Location of the section in bytes from beginning of file
  Elf32_Word sh_size;//Section size in bytes
  Elf32_Word sh_link;//See page 19, figure 1-13 Format_elf.pdf
  Elf32_Word sh_info;//idem
  Elf32_Word sh_addralign;//Address align constraints
  Elf32_Word sh_entsize;//Size of entries if "symbol table" in section
} Elf32_Shdr;

//sh_types values
enum Elf_ShType {
  SHT_NULL      = 0, //Inactive section
  SHT_PROGBITS  = 1, //Program section
  SHT_SYMTAB    = 2, //Symbol table (for link editing)
  SHT_STRTAB    = 3, //String table
  SHT_RELA      = 4, //Relocation entries + "addends"
  SHT_HASH      = 5, //Symbol hash table
  SHT_DYNAMIC   = 6, //Dynamic linking
  SHT_NOTE      = 7, //Note on program
  SHT_NOBITS    = 8, //Section without space in file
  SHT_REL       = 9, //Relocation entries without "addends"
  SHT_SHLIB     = 10,//Not conforming to abi
  SHT_DYNSYM    = 11,//Symbol table
  //Specific to ARM
  SHT_ARM_EXIDX          = 0x7000001, //Exception
  SHT_ARM_PREEMPTMAP     = 0x7000002, //Dynamic linking bpapi dll
  SHT_ARM_ATTRIBUTES     = 0x7000003, //Compatibility attributes
  SHT_ARM_DEBUGOVERLAY   = 0x7000004,
  SHT_ARM_OVERLAYSECTION = 0x7000005,
  //Reserved
  SHT_LOPROC    = 0x7000000,
  SHT_HIPROC    = 0x7ffffff,
  SHT_LOUSER    = 0x8000000,
  SHT_HIUSER    = 0xfffffff
};

enum Elf_ShFlags {
  SHF_WRITE     = 0x1,
  SHF_ALLOC     = 0x2,
  SHF_EXECINSTR = 0x3,
  SHF_MASKPROC  = 0xf0000000
};

#endif