#include "elf_section_table.h"

void rewrite_section_table(Elf32_Ehdr *header, Elf32_Shdr *e_table, Elf32_Shdr *rew_e_table, Elf32_Half *corres){
	unsigned int i, marq=0;
	for(i=0; i<header->e_shnum; i++){
		if(e_table[i].sh_type != SHT_RELA && e_table[i].sh_type != SHT_REL){
			rew_e_table[marq] = e_table[i];
			rew_e_
			marq++;
			corres[i] = marq;
		}
	}
}
