#include <stdio.h>
#include "elf_relocation.h"
#include "elf_header.h"
#include "elf_section_table.h"

int main(int argc, char *argv[]){

	if(argc != 2){
		printf("%s fichier", argv[0]);
		return -1;
	}

	FILE *f;
	f = fopen(argv[1], "r");

	Elf32_Ehdr hdr;
	read_elf_header(f, &hdr);

	Elf32_Shdr shdr[hdr.e_shnum];
	read_elf_section_table(f, &hdr, shdr);

	display_all_relocation_table(f, &hdr, shdr);

	fclose(f);
	return 0;
}