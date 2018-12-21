#include "elf_header.h"
#include "elf_section_table.h"
#include "elf_section_content.h"
#include "elf_symbol.h"

int main(int argc, char **argv){
  FILE* f = fopen(argv[1], "r");
  // IF NULL

  Elf32_Ehdr header_base;
  read_elf_header(f, &header_base);

  Elf32_Shdr s_table[header_base.e_shnum];   //nb de section
  read_elf_section_table(f, &header_base, s_table);

  Elf32_Shdr string_table_hdr = s_table[search_elf_section_num(f, s_table, header_base, ".strtab")];

  Elf32_Shdr symbole_header = s_table[search_elf_section_num(f, s_table, header_base, ".symtab")];

  const int nb_tableSymbole = symbole_header.sh_size / sizeof(Elf32_Sym);
  Elf32_Sym sym_table[nb_tableSymbole];
  read_elf_symbol_table(f, &symbole_header, sym_table);

  display_symbol_table(f, &symbole_header, sym_table, &string_table_hdr);

  fclose(f);
}
