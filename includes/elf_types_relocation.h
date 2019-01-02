#ifndef ELF_TYPES_RELOCATION_H
#define ELF_TYPES_RELOCATION_H

#include "elf_types_atomic.h"

/* Relocations */

typedef struct {
  Elf32_Addr   r_offset;
  Elf32_Word   r_info;
} Elf32_Rel;

typedef struct {
  Elf32_Addr   r_offset;
  Elf32_Word   r_info;
  Elf32_Sword  r_addend;
} Elf32_Rela;

#define ELF32_R_SYM(i)    ((i) >> 8)
#define ELF32_R_TYPE(i)   ((uint8_t)(i))
#define ELF32_R_INFO(s,t) (((s) << 8) + (uint8_t) t)

/* Relocations types, fig 1-22, page 29 */
typedef enum {
  R_386_NONE            = 0,  /* No relocation */
  R_386_32              = 1,  /* Symbol + Offset */
  R_ARM_ABS32           = 2,  /* Direct 32 bit  */
  R_ARM_ABS16           = 5,  /* Direct 16 bit */
  R_ARM_ABS12           = 6,  /* Direct 12 bit */
  R_ARM_ABS8            = 8,  /* Direct 8 bit */
  R_ARM_ABS32_NOI       = 55, /* Direct 32-bit.  */
  R_ARM_JUMP24          = 29, /* PC relative 24 bit */
  R_ARM_CALL            = 28  /* PC relative 24 bit (BL, BLX).  */
} Elf_RelT;

#endif
