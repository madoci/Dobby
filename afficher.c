#include "elf_types_header.h"
#include "elf_header.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv){
	
	Elf32_Ehdr Elf;
	
	if(argc != 2){
		printf("Erreur : arguments \n");
		exit(1);
	}
	else{
		FILE* f = fopen(argv[1], "r");
		if(f != NULL){
			Err_ELF_Header eeh = read_elf_header(f, &Elf);
			if(eeh != ERR_EH_NONE){
				printf("Erreur : read elf\n");
				exit(1);
			}
			else{
				printf("En-tête ELF:\n");
				printf(" Magique: ");
				for(int i = 0;i < 16;i++){
					printf("%02x ", Elf.e_ident[i]);
				}
				printf("\n");

				//Affichage de la classe soit 32 soit 64
				switch(Elf.e_ident[4]){
					case 0: 
						printf(" Classe: ELF invalid arch\n");
						break;
					case 1:
						printf(" Classe: ELF32\n");
						break;
					case 2:
						printf(" Classe: ELF64\n");
						break;
					default:
						printf(" Classe: Erreur\n");
						break;
				}
				
				//Encodage des données
				switch(Elf.e_ident[5]){
					case 0:
						printf(" Données: Invalid data\n");
						break;
					case 1:
						printf(" Données: Little Endian\n");
						break;
					case 2:
						printf(" Données: Big Endian\n");
						break;
					default:
						printf(" Données: Erreur\n");
						break;
				}
				
				//Version ELF
				switch(Elf.e_ident[6]){
					case 0:
						printf(" Version ELF: 0 (None)\n");
						break;
					case 1:
						printf(" Version ELF: 1 (Current)\n");
						break;
					default:
						printf(" Version ELF: Erreur\n");
						break;
				}
				
				//Valeur OS/ABI
				switch(Elf.e_ident[7]){
					case 0:
						printf(" OS/ABI: None\n");
						break;
					case 1:
						printf(" OS/ABI: ARM_AEABI\n");
						break;
					default:
						printf(" OS/ABI: Erreur");
						break;
				}
				
				//file type
				switch (Elf.e_type){
					case 0: 
						printf(" Type: No file type\n");
						break;
					case 1: 
						printf(" Type: Relocatable file\n");
						break;
					case 2: 
						printf(" Type: Executable file\n");
						break;
					case 3: 
						printf(" Type: Shared object file\n");
						break;
					case 4: 
						printf(" Type: Core file\n");
						break;
					case 0xff00:
						// Fall through
					case 0xffff: 
						printf(" Type: Processor-specific\n");
						break;
					default:
						printf(" Type: Erreur\n");
						break;
				}
			
				//Required  architecture for an individual file
				switch(Elf.e_machine){
					case 0:
						printf(" Machine: No machine\n");
						break;
					case 0x28:
						printf(" Machine: ARM\n");
						break;
					default:
						printf(" Machine: Erreur\n");
						break;
				}
				
				//file version
				switch(Elf.e_version){
					case 0: 
						printf(" Version: Invalid version\n");
						break;
					case 1:  
						printf(" Version: Current version\n");
						break;
					default:
						printf(" Version: Erreur\n");
						break;
				}
				
				printf(" Adresse du point d'entrée: 0x%08x\n", Elf.e_entry);
				printf(" Début des en-têtes du programme: %d\n", Elf.e_phoff);
				printf(" Début des en-têtes de section: %d\n", Elf.e_shoff);
				
				switch(Elf.e_flags){
					case 0xFF000000:
						printf(" Fanions: ARM ABIMASK\n");
						break;
					case 0x05000000:
						printf(" Fanions: ARM ABIVER\n");
						break;
					case 0x00800000:
						printf(" Fanions: ARM ABIVER\n");
						break;
					case 0x00400FFF:
						printf(" Fanions: ARM GCCMASK\n");
						break;
					case 0x00000400:
						printf(" Fanions: ARM ABI_FLOAT_HARD\n");
						break;
					case 0x00000200:
						printf(" Fanions: ARM ABI_FLOAT_SOFT\n");
						break;
					default:
						printf(" Fanion: Erreur\n");
						break;
				}
				
				printf(" Taille de cet en-tête du programme: %d\n", Elf.e_ehsize);
				printf(" Taille de l'en-tête du programme: %d\n", Elf.e_phentsize);
				printf(" Nombre d'en-tête du programme: %d\n", Elf.e_phnum);
				printf(" Taille des en-têtes de section: %d\n", Elf.e_shentsize);
				printf(" Nombre d'en-tête de section: %d\n", Elf.e_shnum);
				printf(" Table d'indexe des chaines d'en-tête de section: %d\n", Elf.e_shstrndx);
						
				
			}
		}
		else{
			printf("Erreur : lecture de fichier\n");
			exit(1);
		}
	}
}
