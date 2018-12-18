#ifndef ELF_TYPES_HEADER_H
#define ELF_TYPES_HEADER_H

#include "elf_types_atomic.h"

/* Elf32 file header type (page 9, figure 1-3, Format_ELF.pdf) */

/* Size of identification section in the header (bytes)*/
#define EI_NIDENT (16)

typedef struct {
  unsigned char e_ident[EI_NIDENT];
  Elf32_Half e_type;
  Elf32_Half e_machine;
  Elf32_Word e_version;
  Elf32_Addr e_entry;
  Elf32_Off  e_phoff;
  Elf32_Off  e_shoff;
  Elf32_Word e_flags;
  Elf32_Half e_ehsize;
  Elf32_Half e_phentsize;
  Elf32_Half e_phnum;
  Elf32_Half e_shentsize;
  Elf32_Half e_shnum;
  Elf32_Half e_shstrndx;
} Elf32_Ehdr;

//Indexes in the e_ident attribute.
enum Elf_Ident {
  EI_MAG0       = 0, // 0x7F
  EI_MAG1       = 1, // 'E'
  EI_MAG2	    = 2, // 'L'
  EI_MAG3	    = 3, // 'F'
  EI_CLASS	    = 4, // Architecture (32/64)
  EI_DATA	    = 5, // Byte Order
  EI_VERSION	= 6, // ELF Version
  EI_OSABI      = 7,
  EI_PAD	    = 8  // Padding
};

/* Potential contents of Ident attributes */

enum Elf_IMagic{
  ELFMAG0 = 0x7F, // e_ident[EI_MAG0]
  ELFMAG1 = 'E',  // e_ident[EI_MAG1]
  ELFMAG2 = 'L',  // e_ident[EI_MAG2]
  ELFMAG3 = 'F'   // e_ident[EI_MAG3]
};

enum Elf_IClass{
  ELFCLASSNONE  = 0,  //invalid arch
  ELFCLASS32    = 1,  //32 bits arch 
  ELFCLASS64    = 2   //64 bits arch
};

#define ARM_ELFICLASS (ELFCLASS32)

enum Elf_IOsabi {
  ELFOSABI_NONE      = 0,
  ELFOSABI_ARM_AEABI = 64
};

enum Elf_IData {
  ELFDATANONE = 0, // Invalid data encoding
  ELFDATA2LSB = 1, // Little Endian
  ELFDATA2MSB = 2  // Big Endian
};

#define EI_VALVERSION (EV_CURRENT)
#define EI_VALPAD  (0)

/*Potential contents of header attributes */

//Values of e_type
enum Elf_Type {
  ET_NONE   = 0,
  ET_REL    = 1,
  ET_EXEC   = 2,
  ET_DYN    = 3,
  ET_CORE   = 4,
  ET_LOPROC = 0xff00,
  ET_HIPROC = 0xffff
};

//Values of e_machine
enum Elf_Machine {
  EM_NONE = 0,
  EM_ARM  = 0x28
};

//Values of e_version
enum Elf_Version {
  EV_NONE    = 0,
  EV_CURRENT = 1
};

//Values of e_flags SPECIFIC TO ARM
enum Elf_Flags {
  EF_ARM_ABIMASK        = 0xFF000000,
  EF_ARM_ABIVER         = 0x05000000,
  EF_ARM_BE8            = 0x00800000,
  EF_ARM_GCCMASK        = 0x00400FFF,
  EF_ARM_ABI_FLOAT_HARD = 0x00000400,
  EF_ARM_ABI_FLOAT_SOFT = 0x00000200
};

#endif