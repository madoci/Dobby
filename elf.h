#ifndef ELF_H
#define ELF_H

#include "elf_types.h"

/* Convenient macros to check atomic types size, according to Format_ELF.pdf*/

#define chk_word_size(word) (sizeof(word)==4)
#define chk_sword_size(sword) (sizeof(sword)==4)
#define chk_half_size(half) (sizeof(half)==2)
#define chk_off_size(off) (sizeof(off)==4)
#define chk_addr_size(addr) (sizeof(addr)==4)

/* wrapper to check all types once, return 1 if everything is okay else :
   -1 => 32 unsigned error
   -2 => 32 signed error
   -3 => 16 unsigned error*/
int check_types_size(void);


#endif
