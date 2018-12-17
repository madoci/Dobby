#include "elf_types.h"
#include "elf.h"

int check_types_size(void){
  Elf32_Word word = 0xffff;
  Elf32_Sword sword = 0xffff;
  Elf32_Half half = 0xff;
  Elf32_Off off = 0xffff;
  Elf32_Addr addr = 0xffff;

  if (!chk_word_size(word) || !chk_off_size(off) || !chk_addr_size(addr))
    return -1;
  else if (!chk_sword_size(sword))
    return -2;
  else if (!chk_half_size(half))
    return -3;
  else
    return 1;
}

ERR_ELF_READER check_ident(Elf32_Ehdr* hdr){
  if(hdr->e_ident[EI_MAG0] != ELFMAG0 ||
     hdr->e_ident[EI_MAG1] != ELFMAG1 ||
     hdr->e_ident[EI_MAG2] != ELFMAG2 ||
     hdr->e_ident[EI_MAG3] != ELFMAG3){
    return ERR_MAG;
  }
  if(hdr->e_ident[EI_CLASS] != ELFCLASSNONE &&
     hdr->e_ident[EI_CLASS] != ELFCLASS32  &&
     hdr->e_ident[EI_CLASS] != ELFCLASS64){
    return ERR_CLASS;
  }
  if(hdr->e_ident[EI_DATA] != ELFDATANONE &&
     hdr->e_ident[EI_DATA] != ELFDATA2LSB &&
     hdr->e_ident[EI_DATA] != ELFDATA2MSB){
    return ERR_DATA;
  }
  if(hdr->e_ident[EI_VERSION] != EI_VALVERSION){
    return ERR_VERSION;
  }
  if(hdr->e_ident[EI_OSABI] != ELFOSABI_ARM_AEABI &&
     hdr->e_ident[EI_OSABI] != ELFOSABI_NONE){
    return ERR_OSABI;
  }
  if(hdr->e_ident[EI_PAD] != EI_VALPAD){
    return ERR_PAD;
  }
  return ERR_NONE;
}

ERR_ELF_READER read_elf_header(FILE *f, Elf32_Ehdr* hdr){
  if (f == NULL){
    return -1;
  }
  fread(hdr->e_ident, 1, 16, f);

  ERR_ELF_READER erreur = check_ident(hdr); 
  if(erreur != ERR_NONE){
    printf("erreur\n");
    return erreur;
  }
  printf("succes!!!!!!!!\n");

  

  /*for(int i =0; i<4; i++){
    printf("%c ", hdr->e_ident[i]);
  }
  printf("\n");
*/
  return 1;
}

int main(int argc, char *argv[]){
  Elf32_Ehdr hdr;
  FILE *f;
  f = fopen(argv[1], "r");
  read_elf_header(f, &hdr);
}