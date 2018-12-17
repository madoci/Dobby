#include "elf_header.h"
#include <stdio.h>

int main(int argc,char **argv){
	
	Elf32_Ehdr Elf;
	
	if(argc!=2){
		printf("Erreur : arguments \n");
	}
	else{
		FILE* f=fopen(argv[1],"r");
		if(f != NULL){
			Err_ELF_Header tes = read_elf_header(f,&Elf);
			if(tes != ERR_EH_NONE){
				printf("Erreur : read elf :%d \n",tes);
			}
			else{
		
				//Affichage de la classe soit 32 soit 64
				switch(Elf.e_ident[4]){
					case 0: 
						printf("Classe: ELF invalid arch\n");
						break;
					case 1:
						printf("Classe: ELF32\n");
						break;
					case 2:
						printf("Classe: ELF64\n");
						break;
					default:
						printf("Erreur : ELF_Classe\n");
						break;
				}
				
				//Encodement des données
				switch(Elf.e_ident[5]){
					case 0:
						printf("Données: Invalid data\n");
						break;
					case 1:
						printf("Données: little Endian\n");
						break;
					case 2:
						printf("Données: Big Endian\n");
						break;
					default:
						printf("Erreur : erreur données\n");
				}
				
				//Version ELF
				switch(Elf.e_ident[6]){
					case 0:
						printf("Version ELF: 0(None)\n");
						break;
					case 1:
						printf("Version ELF: 1(Current)\n");
						break;
					default:
						printf("Erreur : erreur version ELF\n");
						break;
				}
				
				//Valeur OS/ABI
				switch(Elf.e_ident[7]){
					case 0:
						printf("OS/ABI: None\n");
						break;
					case 1:
						printf("OS/ABI: ARM_AEABI\n");
						break;
					default:
						printf("Erreur : Erreur Os/ABI");
				}
				
				//file type
				switch (Elf.e_type){
					case 0: 
						printf("Type: No file type\n");
						break;
					case 1: 
						printf("Type: Relocatable file\n");
						break;
					case 2: 
						printf("Type: Executable file\n");
						break;
					case 3: 
						printf("Type: Shared object file\n");
						break;
					case 4: 
						printf("Type: Core file\n");
						break;
					case 0xff00:
					case 0xffff: 
						printf("Type: Processor-specific\n");
						break;
					default:
						printf("Erreur type inconnu\n");
						break;
				}
			
				//Required  architecture for an individual file
				switch(Elf.e_machine){
					case 0:
						printf("Machine: No machine\n");
						break;
					case 28:
						printf("Machine: ARM\n");
						break;
					default:
						printf("Erreur: \n");
						break; 
				}
				
				//file version
				switch(Elf.e_version){
					case 0: 
						printf("Version: Invalid version\n");
						break;
					case 1:  
						printf("Version: Current version\n");
						break;
					default:
						 printf("Erreur : Erreur version\n");
				}
				
				printf("Adresse du point d'entrée: 0x%08x\n",Elf.e_entry);
				printf("Début des en-têtes du programme: 0x%08x\n",Elf.e_phoff);
				printf("Début des en-têtes de section: 0x%08x\n",Elf.e_shoff);
				printf("Fanions: 0x%08x\n",Elf.e_flags);
				
			}
		}
		else{
			printf("Erreur : lecture de fichier\n");
		}
	}
}
