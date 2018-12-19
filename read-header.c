#include "elf_types_header.h"
#include "elf_header.h"
#include "read-header.h"
#include <stdio.h>
#include <stdlib.h>

void display_header(Elf32_Ehdr * Elf){
	printf("En-tête ELF:\n");
	printf(" Magique: ");
	for(int i = 0;i < EI_NIDENT;i++){
		printf("%02x ", Elf->e_ident[i]);
	}
	printf("\n");
	display_ident(Elf->e_ident);
	display_verAbi(Elf->e_flags);
	display_type(Elf->e_type);
	display_machine(Elf->e_machine);
	display_fileVersion(Elf->e_version);
	printf(" Adresse du point d'entrée: 0x%08x\n", Elf->e_entry);
	printf(" Début des en-têtes du programme: %d\n", Elf->e_phoff);
	printf(" Début des en-têtes de section: %d\n", Elf->e_shoff);
	display_flags(Elf->e_flags);
	printf(" Taille de cet en-tête du programme: %d\n", Elf->e_ehsize);
	printf(" Taille de l'en-tête du programme: %d\n", Elf->e_phentsize);
	printf(" Nombre d'en-tête du programme: %d\n", Elf->e_phnum);
	printf(" Taille des en-têtes de section: %d\n", Elf->e_shentsize);
	printf(" Nombre d'en-tête de section: %d\n", Elf->e_shnum);
	printf(" Table d'indexe des chaines d'en-tête de section: %d\n", Elf->e_shstrndx);
}
void display_ident(unsigned char e_ident[]){
	display_class(e_ident[EI_CLASS]);
	display_data(e_ident[EI_DATA]);
	display_eiVersion(e_ident[EI_VERSION]);
	display_osabi(e_ident[EI_OSABI]);
}
void display_class(unsigned char class){
	switch(class){
		case ELFCLASSNONE:
			printf(" Classe: ELF invalid arch\n");
			break;
		case ELFCLASS32:
			printf(" Classe: ELF32\n");
			break;
		case ELFCLASS64:
			printf(" Classe: ELF64\n");
			break;
	}
}
void display_data(unsigned char data){
	switch(data){
		case ELFDATANONE:
			printf(" Données: Invalid data\n");
			break;
		case ELFDATA2LSB:
			printf(" Données: Little Endian\n");
			break;
		case ELFDATA2MSB:
			printf(" Données: Big Endian\n");
			break;
		default:
			printf(" Données: Erreur\n");
			break;
	}
}
void display_eiVersion(unsigned char version){
	printf(" Version courante : %d\n", version);
}
void display_osabi(unsigned char osabi){

	switch(osabi){
		case ELFOSABI_NONE:
			printf(" OS/ABI: None\n");
			break;
		case ELFOSABI_ARM_AEABI:
			printf(" OS/ABI: ARM_AEABI\n");
			break;
		default:
			printf(" OS/ABI: Erreur");
			break;
	}
}
void display_type(Elf32_Half type){

	switch (type){
		case ET_NONE:
			printf(" Type: No file type\n");
			break;
		case ET_REL:
			printf(" Type: Relocatable file\n");
			break;
		case ET_EXEC:
			printf(" Type: Executable file\n");
			break;
		case ET_DYN:
			printf(" Type: Shared object file\n");
			break;
		case ET_CORE:
			printf(" Type: Core file\n");
			break;
		case ET_LOPROC:
			// Fall through
		case ET_HIPROC:
			printf(" Type: Processor-specific\n");
			break;
	}
}
void display_machine(Elf32_Half machine){
	switch(machine){
		case EM_NONE:
			printf(" Machine: No machine\n");
			break;
		case EM_ARM:
			printf(" Machine: ARM\n");
			break;
	}
}
void display_fileVersion(Elf32_Word  version){
	switch(version){
		case EV_NONE:
			printf(" Version: Invalid version\n");
			break;
		case EV_CURRENT:
			printf(" Version: Current version\n");
			break;
	}
}
void display_flags(Elf32_Word flag){

	printf("Fanions:\t");

	if(flag & EF_ARM_BE8)
		printf("EF_ARM_BE8 ");
	if(flag & EF_ARM_GCCMASK)
		printf("GCC(0x%08x) ",flag & EF_ARM_GCCMASK);
	if(flag & EF_ARM_ABI_FLOAT_HARD)
		printf("EF_ARM_ABI_FLOAT_HARD ");
	if(flag & EF_ARM_ABI_FLOAT_SOFT)
		printf("ARM ABI_FLOAT_SOFT ");

	printf("\n");
}
void display_verAbi(Elf32_Word flag){
	printf("Version ABI: %d\n", (flag & EF_ARM_ABIMASK) >>24);
}

int main(int argc, char **argv){
	Elf32_Ehdr Elf;
	if(argc != 2){
		printf("Erreur : arguments\n");
		exit(1);
	}
	FILE* f = fopen(argv[1], "r");
	if(f == NULL)
		exit(1);
	Err_ELF_Header error = read_elf_header(f, &Elf);
	if(error != ERR_EH_NONE){
		printf("Erreur : read elf\n");
		exit(1);
		}
		display_header(&Elf);
		fclose(f);
}
