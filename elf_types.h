#ifndef ELF_TYPES_H
#define ELF_TYPES_H

/* Elf32 data types */

/* Elf32 atomic types (page 8, figure 1-2, Format_ELF.pdf) */

typedef signed long int Elf32_Sword; /* Size : 32 bits */
typedef unsigned long int Elf32_Word;/* Size : 32 bits */
typedef unsigned short int Elf32_Half;/*Size : 16 bits */

typedef unsigned long int Elf32_Off; /* Size : 32 bits */
typedef unsigned long int Elf32_Addr;/* Size : 32 bits */

#endif
