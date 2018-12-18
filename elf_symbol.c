#include "elf_symbols.h"
#include "elf_type_symbol"
#include "elf_header.h"

#include <stdio.h>

void read_elf_symbole_table(FILE *f, Elf32_Ehdr *hdr, Elf32_sym s_table){
	unsigned int i;
	for(i = 0; i<hdr.e_shnum; i++){
		
	}
}

void display_section_header(FILE* f){
	Elf32_sym ElfS;
	Elf32_Ehdr hrd;
	read_elf_header(f, &header);

	read_elf_symbole_table(f, &hdr);
	Elf32_Half nbr_sym = header.e_shnum; //Verif

	printf("Table de symboles « .symtab » contient %d entrées:", nbr_sym);
	printf(" Num:    Valeur Tail  Type   Lien   Vis      Ndx Nom");
//Refe place    0: 00000000     0 NOTYPE  LOCAL  DEFAULT  UND 	
	for(ELF32_Half i = 0 ; i < nbr_sym ; i++){
		Elf_Addr val = ElfS.st_value;
		Elf32_Word taille = ElfS.st_size;
		unsigned char lien="NONE";
		
		unsigned char info = ElfS.st_info;
		int b = ELF32_ST_BIND(info);
		switch(b){
		case 0:
			lien = "LOCAL";
			break;
		case 1: 
			lien = "GLOBAL";
			break;
		case 2:
			lien = "WEAK";
			break;
		case 13:
			lien = "LOPROC";
			break;
		case 15:
			lien = "HIPROC";
			break;
		default:
			printf("Erreur: Lien Symbole");
			break;
		}
		unsigned char type="NONE";
		int t = ELF32_ST_TYPE(info);
		switch(t){
		case 0:
			type = "NOTYPE";
			break;
		case 1:
			type = "OBJECT";
			break;
		case 2:
			type = "FUNC";
			break;
		case 3:
			type = "SECTION";
			break;
		case 4:
			type = "FILE";
			break;
		case 13:
			type = "LOPROC";
			break;
		case 15:
			type = "HIPROC";
		default:
			printf("Erreur: Type symbole");
			break;
		}
		Elf32_word nom = ElfS.st_name;
		Elf32_Half ndx = ElfS.st_shndx;
		printf(" %2d:    %08x %d  %s   %s  %s %s %s", i, val, taille, type, lien, ndx, nom);
	}
}
