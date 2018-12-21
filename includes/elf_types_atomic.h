#ifndef ELF_TYPES_ATOMIC_H
#define ELF_TYPES_ATOMIC_H

# include <stdint.h>

/* Elf32 atomic types (page 8, figure 1-2, Format_ELF.pdf) */

typedef int32_t Elf32_Sword; /* Size : 32 bits */
typedef uint32_t Elf32_Word; /* Size : 32 bits */
typedef uint16_t Elf32_Half; /* Size : 16 bits */

typedef uint32_t Elf32_Off;  /* Size : 32 bits */
typedef uint32_t Elf32_Addr; /* Size : 32 bits */

#endif
