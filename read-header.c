#include "elf_types_header.h"
#include "elf_header.h"
#include "read-header.h"
#include <stdio.h>
#include <stdlib.h>

#define printf_8x(s,x) printf("%-50s : 0x%08x\n",s,x)
#define printf_d(s,d) printf("%-50s : %d\n",s,d)
#define printf_s(s,s2) printf("%-50s : %s\n",s,s2)

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
	printf_8x("Adresse du point d'entrée", Elf->e_entry);
	printf_d("Début des en-têtes du programme", Elf->e_phoff);
	printf_d("Début des en-têtes de section", Elf->e_shoff);
	display_flags(Elf->e_flags);
	printf_d("Taille de cet en-tête du programme", Elf->e_ehsize);
	printf_d("Taille de l'en-tête du programme", Elf->e_phentsize);
	printf_d("Nombre d'en-tête du programme", Elf->e_phnum);
	printf_d("Taille des en-têtes de section", Elf->e_shentsize);
	printf_d("Nombre d'en-tête de section", Elf->e_shnum);
	printf_d("Table d'indexe des chaines d'en-tête de section", Elf->e_shstrndx);
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
			printf_s("Classe","ELF invalid arch");
			break;
		case ELFCLASS32:
			printf_s("Classe","ELF32");
			break;
		case ELFCLASS64:
			printf_s("Classe","ELF64");
			break;
	}
}
void display_data(unsigned char data){
	switch(data){
		case ELFDATANONE:
			printf_s("Données","Invalid data");
			break;
		case ELFDATA2LSB:
			printf_s("Données","Little Endian");
			break;
		case ELFDATA2MSB:
			printf_s("Données","Big Endian");
			break;
	}
}
void display_eiVersion(unsigned char version){
	printf_d("Version courante",version);
}
void display_osabi(unsigned char osabi){

	switch(osabi){
		case ELFOSABI_NONE:
			printf_s("OS/ABI","None");
			break;
		case ELFOSABI_ARM_AEABI:
			printf_s("OS/ABI","ARM_AEABI");
			break;
}
}
void display_type(Elf32_Half type){

	switch (type){
		case ET_NONE:
			printf_s("Type","No file type");
			break;
		case ET_REL:
			printf_s("Type","Relocatable file");
			break;
		case ET_EXEC:
			printf_s("Type","Executable file");
			break;
		case ET_DYN:
			printf_s("Type","Shared object file");
			break;
		case ET_CORE:
			printf_s("Type","Core file");
			break;
		case ET_LOPROC:
		// Fall through
		case ET_HIPROC:
			printf_s("Type","Processor-specific");
			break;
	}
}
void display_machine(Elf32_Half machine){
	switch(machine){
		case EM_NONE:
		printf_s("Machine","No machine");
		break;
		case EM_ARM:
		printf_s("Machine","ARM");
		break;
	}
}
void display_fileVersion(Elf32_Word  version){
	switch(version){
		case EV_NONE:
			printf_s("Version", "Invalid version");
			break;
		case EV_CURRENT:
			printf_s(" Version","Current version");
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
	printf_d("Version ABI:", (flag & EF_ARM_ABIMASK) >>24);
}

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
