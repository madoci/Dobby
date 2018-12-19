#include "elf_symbol.h"
#include "elf_types_symbol.h"
#include "elf_section.h"
#include "fread.h"

void read_elf_symbole_table(FILE *f, *Elf32_Shdr Shdr, *Elf32_Sym s_table){
	if(Shdr.sh_type == 2){
		unsigned i=0;
		fseek(f, Shdr.sh_offset, SEEK_SET);
		s_table = read_sym(f);
		display_table_symbole(f, s_table);
	}
}

Elf32_Sym read_sym(FILE *f){
  
  Elf32_Sym line;
  fread_32bits(&(line.st_name),1, f);
  fread_32bits(&(line.st_value), 1, f);
  fread_32bits(&(line.st_size), 1, f);
  fread_32bits(&(line.st_info), 1, f);
  fread_32bits(&(line.st_other), 1, f);
  fread_32bits(&(line.st_shndx), 1, f);
  
  return line;
}


void display_table_sym(FILE* f, *Elf32_Shdr tab){

	// TODO printf("Table de symboles « .symtab » contient %d entrées:", nbr_sym);
	printf(" Num:\tValeur\tTail\tType\tLien\tVis\tNdx\tNom");
	
	for(Elf32_Half i = 0 ; i < nbr_sym ; i++){
		Elf32_Addr val = ElfS.st_value;
		Elf32_Word taille = ElfS.st_size;
		char *lien="NONE";
		
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
		char* type="NONE";
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
		Elf32_Word nom = ElfS.st_name;
		Elf32_Half ndx = ElfS.st_shndx;
		printf(" %2d:\t%08x\t%d\t %s\t%s\t%s\t%s\t%s", i, val, taille, type, lien, ndx, nom);
	}
}

int main(int argc, char **argv){
	FILE* f = fopen(argv[1], "r");
	Elf32_Shdr Shdr;
	Elf32_Sym s_table;
	read_elf_symbol_table(f, &Shdr, &s_table);
	display_table_sym(f, &Shdr);
	fclose(f);
}
