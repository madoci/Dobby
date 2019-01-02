#include "rewrite_section_table.h"

void rewrite_section_table(Elf32_Ehdr *header, Elf32_Shdr e_table[], Elf32_Shdr rew_e_table[], Elf32_Half corres[]){
	unsigned int i, marq=1;

	//First section is null and must stay null
	rew_e_table[0] = e_table[0];
	corres[0] = 0;

	//Significant sections
	for(i=1; i<header->e_shnum; i++){

		if(e_table[i].sh_type != SHT_RELA && e_table[i].sh_type != SHT_REL){
			rew_e_table[marq] = e_table[i];
			corres[i] = marq;

			if(marq != 1){
				rew_e_table[marq].sh_offset = rew_e_table[marq-1].sh_offset +
																			rew_e_table[marq-1].sh_size;
			}

			//DEBUG: Help to see what changed
			/*
			printf( "Section %d mapped on %d has offset %d -> %d\n",i,marq,
							e_table[i].sh_offset, rew_e_table[marq].sh_offset);
							*/
			marq++;

		}
	}
}

void correct_header(Elf32_Ehdr *hdr, Elf32_Half corres[], Elf32_Half shnum){
	hdr->e_shstrndx = corres[hdr->e_shstrndx];
	hdr->e_shnum = shnum;
}


Elf32_Half compte_shnum(Elf32_Ehdr *header, Elf32_Shdr e_table[]){
	unsigned int i;
	Elf32_Half cpt=0;
	for(i=0; i<header->e_shnum; i++){
		if(e_table[i].sh_type != SHT_RELA && e_table[i].sh_type != SHT_REL){
			cpt++;
		}
	}
	return cpt;
}
