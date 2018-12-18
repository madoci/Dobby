#include <stdio.h>
#include "elf_header.h"
#include "elf_section.h"
#include "elf_section_content.h"

int main(int argc, char* argv[]){
	FILE *f = fopen(argv[1], "r");
	Elf32_Ehdr hdr;
	read_elf_header(f, &hdr);
	Elf32_Shdr sh_tab[hdr.e_shnum];
	read_elf_section_table(f, &hdr, sh_tab);
	read_elf_section_content_by_name(f, sh_tab, hdr, argv[2]);
	return 0;
}