#include "rewrite_section_table.h"
#include "elf_section_table.h"

int main(int argc, char const * argv[]){
	if (argc != 2){
  		printf("Format : %s <fichier>\n", argv[0]);
		return 1;
	}

	FILE *f = fopen(argv[1], "r");
	if (f == NULL){
		printf("Impossible d'ouvrir le fichier \"%s\".\n", argv[1]);
  		return 1;
	}
  
	Elf32_Ehdr header;
	read_elf_header(f, &header);

	Elf32_Shdr e_table[header.e_shnum];
	read_elf_section_table(f, &header, e_table);
	Elf32_Half taille = compte_shnum(&header, e_table);

	Elf32_Shdr rew_e_table[taille];
	Elf32_Half corres[header.e_shnum];

	rewrite_section_table(&header, e_table, rew_e_table, corres);
	
	display_section_header(f, &header, rew_e_table);
  
	fclose(f);
	return 0;	
}
