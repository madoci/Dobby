#include "elf_types_atomic.h"
#include "elf_types_symbol.h"
#include "elf_types_section.h"

void correct_symbol_section(Elf32_Sym *sym, Elf32_Half correl_table[]);

void correct_symbol_value(Elf32_Sym *sym, Elf32_Shdr section_table[]);
