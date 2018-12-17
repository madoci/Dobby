#include "elf_types.h"
#include "elf.h"

int check_types_size(void){
  Elf32_Word word = 0xffff;
  Elf32_Sword sword = 0xffff;
  Elf32_Half half = 0xff;
  Elf32_Off off = 0xffff;
  Elf32_Addr addr = 0xffff;

  if (!chk_word_size(word) || !chk_off_size(off) || !chk_addr_size(addr))
    return -1;
  else if (!chk_sword_size(sword))
    return -2;
  else if (!chk_half_size(half))
    return -3;
  else
    return 1;
}
