#ifndef ELF_TYPES_H
#define ELF_TYPES_H

# include <stdint.h>

/* Elf32 data types */

/* Elf32 atomic types (page 8, figure 1-2, Format_ELF.pdf) */

typedef int32_t Elf32_Sword; /* Size : 32 bits */
typedef uint32_t Elf32_Word;/* Size : 32 bits */
typedef uint16_t Elf32_Half;/*Size : 16 bits */

typedef uint32_t Elf32_Off; /* Size : 32 bits */
typedef uint32_t Elf32_Addr;/* Size : 32 bits */

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
}Elf32_Ehdr;

//Indexes in the e_ident attribute.
enum Elf_Ident {
  EI_MAG0       = 0, // 0x7F
  EI_MAG1       = 1, // 'E'
  EI_MAG2	= 2, // 'L'
  EI_MAG3	= 3, // 'F'
  EI_CLASS	= 4, // Architecture (32/64)
  EI_DATA	= 5, // Byte Order
  EI_VERSION	= 6, // ELF Version
  EI_PAD	= 7  // Padding
};

/* Potential contents of Ident attributes */

enum Elf_IMagic{
  ELFMAG0 =0x7F, // e_ident[EI_MAG0]
  ELFMAG1 ='E',  // e_ident[EI_MAG1]
  ELFMAG2 ='L',  // e_ident[EI_MAG2]
  ELFMAG3 ='F'  // e_ident[EI_MAG3]
};

enum Elf_IClass{
  ELFCLASSNONE  =0, //invalid arch
  ELFCLASS32   =1,  //32 bits arch 
  ELFCLASS64   =2   //64 bits arch
};

#define ARM_ELFICLASS (Elf_IClass.ELFCLASS32)

enum Elf_IData {
  ELFDATANONE =0, // Invalid data encoding
  ELFDATA2LSB =1, // Little Endian
  ELFDATA2MSB =2 // Big Endian
};

#define EI_VERSION (Elf_Version.EV_CURRENT)
#define EI_PAD  (0)

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
  EF_ARM_ABIMASK = 0xFF000000,
  EF_ARM_ABIVER  = 0x05000000,
  EF_ARM_BE8     = 0x00800000,
  EF_ARM_GCCMASK = 0x00400FFF,
  EF_ARM_ABI_FLOAT_HARD =0x00000400,
  EF_ARM_ABI_FLOAT_SOFT =0x00000200
};

/* Sections data types */

//Undefined section
#define SHN_UNDEF (0)

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
}Elf32_Shdr;

//sh_types values
enum Elf_ShType {
  SHT_NULL      =0, //Inactive section
  SHT_PROGBITS  =1, //Program section
  SHT_SYMTAB    =2, //Symbol table (for link editing)
  SHT_STRTAB    =3, //String table
  SHT_RELA      =4, //Relocation entries + "addends"
  SHT_HASH      =5, //Symbol hash table
  SHT_DYNAMIC   =6, //Dynamic linking
  SHT_NOTE      =7, //Note on program
  SHT_NOBITS    =8, //Section without space in file
  SHT_REL       =9, //Relocation entries without "addends"
  SHT_SHLIB     =10,//Not conforming to abi
  SHT_DYNSYM    =11,//Symbol table
  //Specific to ARM
  SHT_ARM_EXIDX =0x7000001, //Exception
  SHT_ARM_PREEMPTMAP =0x7000002, //Dynamic linking bpapi dll
  SHT_ARM_ATTRIBUTES =0x7000003, //Compatibility attributes
  SHT_ARM_DEBUGOVERLAY =0x7000004,
  SHT_ARM_OVERLAYSECTION = 0x7000005,
  //Reserved
  SHT_LOPROC    =0x7000000,
  SHT_HIPROC    =0x7ffffff,
  SHT_LOUSER    =0x8000000,
  SHT_HIUSER    =0xfffffff
};

enum Elf_ShFlags {
  SHF_WRITE    =0x1,
  SHF_ALLOC    =0x2,
  SHF_EXECINSTR=0x3,
  SHF_MASKPROC =0xf0000000
};

const Elf32_Shdr entry0 = {
  .sh_name = 0,
  .sh_type = Elf_ShType.SHT_NULL,
  .sh_flags= 0,
  .sh_addr = 0,
  .sh_offset=0,
  .sh_size = 0,
  .sh_link = SHN_UNDEF,
  .sh_info = 0,
  .sh_addralign = 0,
  .sh_entsize = 0
};


#endif
