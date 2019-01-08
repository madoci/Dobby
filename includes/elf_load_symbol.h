#include "elf_types_atomic.h"
#include "elf_types_symbol.h"
#include "elf_types_section.h"
#include "elf_file.h"

Elf32_Sym correct_symbol_section(Elf32_Sym sym, Elf32_Half correl_table[]);

Elf32_Sym correct_symbol_value(Elf32_Sym sym, Elf32_Shdr section_table[]);

void correct_all_symbol(Elf32_File ef, Elf32_Half sh_num, Elf32_Half correl_table[]);
