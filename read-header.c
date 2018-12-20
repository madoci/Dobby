#include "elf_types_header.h"
#include "elf_header.h"
#include <stdio.h>

int main(int argc, char **argv){
	Elf32_Ehdr Elf;
	if(argc != 2){
		printf("Erreur : arguments\n");
		return 1;
	}
	FILE* f = fopen(argv[1], "r");
	if(f == NULL)
		return 1;
	Err_ELF_Header error = read_elf_header(f, &Elf);
	if(error != ERR_EH_NONE){
		printf("Erreur lors de la lecture du reader: (%d)\n",error);
		return 1;
	}
	display_header(&Elf);
	fclose(f);
	return 0;
}
