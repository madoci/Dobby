#ifndef ELF_LOAD_SYMBOL_H
#define ELF_LOAD_SYMBOL_H

#include "elf_types_atomic.h"
#include "elf_types_symbol.h"
#include "elf_types_section.h"
#include "elf_file.h"

/* */
void correct_all_symbol(Elf32_File* ef, Elf32_Half sh_num, Elf32_Half correl_table[], Elf32_Half correl_symbol[]);

<<<<<<< HEAD
void correct_all_symbol(Elf32_File* ef, Elf32_Half sh_num, Elf32_Half correl_table[], Elf32_Half correl_symbol[]);
=======
#endif
>>>>>>> 520d69ec29cf57cf8bf021c0e6815ac633a8a29c
