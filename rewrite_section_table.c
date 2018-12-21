#include "rewrite_section_table.h"

void rewrite_section_table(Elf32_Ehdr *header, Elf32_Shdr *e_table, Elf32_Shdr *rew_e_table, Elf32_Half *corres){
	unsigned int i, marq=0;

	for(i=0; i<header->e_shnum; i++){
		
		if(e_table[i].sh_type != SHT_RELA && e_table[i].sh_type != SHT_REL){
			rew_e_table[marq] = e_table[i];
			
			if(marq != 0){
				rew_e_table[marq].sh_offset = rew_e_table[marq-1].sh_offset + rew_e_table->sh_size;
			}
			marq++;
			corres[i] = marq;
		}
	}
}


Elf32_Half compte_shnum(Elf32_Ehdr *header, Elf32_Shdr *e_table){
	unsigned int i;
	Elf32_Half cpt=0;
	for(i=0; i<header->e_shnum; i++){
		if(e_table[i].sh_type != SHT_RELA && e_table[i].sh_type != SHT_REL){
			cpt++;
		}
	}
	return cpt;
} 




