#include "elf_symbol.h"
#include "elf_types_symbol.h"
#include "elf_section.h"
#include "fread.h"

#include <stdio.h>

void read_elf_symbole_table(FILE *f, Elf32_Shdr Shdr, Elf32_sym s_table){
	if(Shdr.sh_type == 2){
		unsigned i=0;
		fseek(f, Shdr.sh_offset, SEEK_SET);
    s_table = red_sym(f);
    display_table_symbole(f, s_table);
	}
}

Elf32_sym read_sym(FILE *f){
  
  Elf32_sym line;
  fread_32bits(&(line.st_name),1, f);
  fread_32bits(&(line.st_value), 1, f);
  fread_32bits(&(line.st_size), 1, f);
  fread_32bits(&(line.st_info), 1, f);
  fread_32bits(&(line.st_other), 1, f);
  fread_32bits(&(line.st_shndx), 1, f);
  
  return line;
}


void display_table_sym(FILE* f, Elf32_Shdr tab){

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
