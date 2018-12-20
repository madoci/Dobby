#include "elf_symbol.h"
#include "elf_types_symbol.h"
#include "elf_section_table.h"
#include "fread.h"

void read_elf_symbol_table(FILE *f, Elf32_Shdr* symbole_header, Elf32_Sym s_table[]){
	const int nb_tableSymbole = symbole_header/sizeof(Elf32_Sym);
	const int start_tableSymbole = symbole_header->sh_offset;

	for(i = O; i<nb_tableSymbole; i++){
		fseek(f, start_tableSymbole+i*sizeof(Elf32_Sym), SEEK_SET);
		s_table[i] = read_sym(f);
	}
}


Elf32_Sym read_sym(FILE *f){

  Elf32_Sym line;
  fread_32bits(&(line.st_name),1, f);
  fread_32bits(&(line.st_value), 1, f);
  fread_32bits(&(line.st_size), 1, f);
  fread_8bits(&(line.st_info), 1, f);
  fread_8bits(&(line.st_other), 1, f);
  fread_32bits(&(line.st_shndx), 1, f);

  return line;
}


void display_symbol_table(FILE* f, Elf32_Shdr* tab, Elf32_Ehdr header){

	// TODO printf("Table de symboles « .symtab » contient %d entrées:", nbr_sym);
	Elf32_Half nbr_sym = header.e_shnum;
	Elf32_Sym ElfS;
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
			break;
		default:
			printf("Erreur: Type symbole");
			break;
		}
		Elf32_Word nom = ElfS.st_name;
		Elf32_Half ndx = ElfS.st_shndx;
		printf(" %2d:\t%08x\t%d\t %s\t%s\t%d\t%d", i, val, taille, type, lien, ndx, nom);
	}
}

int main(int argc, char **argv){
	FILE* f = fopen(argv[1], "r");
	Elf32_Shdr Shdr;
	Elf32_Sym s_table;
	read_elf_symbol_table(f, &Shdr, &s_table);
	display_symbol_table(f, &Shdr);
	fclose(f);
}
