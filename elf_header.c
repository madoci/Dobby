#include "elf_header.h"

#include "elf_types_header.h"
#include "fread.h"

Err_ELF_Header check_ident(Elf32_Ehdr* hdr){
  if(hdr->e_ident[EI_MAG0] != ELFMAG0 ||
     hdr->e_ident[EI_MAG1] != ELFMAG1 ||
     hdr->e_ident[EI_MAG2] != ELFMAG2 ||
     hdr->e_ident[EI_MAG3] != ELFMAG3){
    return ERR_EH_IMAG;
  }
  if(hdr->e_ident[EI_CLASS] != ELFCLASSNONE &&
     hdr->e_ident[EI_CLASS] != ELFCLASS32  &&
     hdr->e_ident[EI_CLASS] != ELFCLASS64){
    return ERR_EH_ICLASS;
  }
  if(hdr->e_ident[EI_DATA] != ELFDATANONE &&
     hdr->e_ident[EI_DATA] != ELFDATA2LSB &&
     hdr->e_ident[EI_DATA] != ELFDATA2MSB){
    return ERR_EH_IDATA;
  }
  if(hdr->e_ident[EI_VERSION] != EI_VALVERSION){
    return ERR_EH_IVERSION;
  }
  if(hdr->e_ident[EI_OSABI] != ELFOSABI_ARM_AEABI &&
     hdr->e_ident[EI_OSABI] != ELFOSABI_NONE){
    return ERR_EH_IOSABI;
  }
  if(hdr->e_ident[EI_PAD] != EI_VALPAD){
    return ERR_EH_IPAD;
  }
  return ERR_EH_NONE;
}


Err_ELF_Header check_type(Elf32_Ehdr* hdr){
  if(hdr->e_type != ET_NONE   &&
     hdr->e_type != ET_REL    &&
     hdr->e_type != ET_EXEC   &&
     hdr->e_type != ET_DYN    &&
     hdr->e_type != ET_CORE   &&
     hdr->e_type != ET_LOPROC &&
     hdr->e_type != ET_HIPROC){
    return ERR_EH_TYPE;
  }
  return ERR_EH_NONE;
}


Err_ELF_Header check_machine(Elf32_Ehdr* hdr){
  if(hdr->e_machine != EM_NONE &&
     hdr->e_machine != EM_ARM){
    return ERR_EH_MACHINE;
  }
  return ERR_EH_NONE;
}


Err_ELF_Header check_version(Elf32_Ehdr* hdr){
  if(hdr->e_version != EV_NONE &&
     hdr->e_version != EV_CURRENT){
    return ERR_EH_VERSION;
  }
  return ERR_EH_NONE;
}


Err_ELF_Header check_flags(Elf32_Ehdr* hdr){
  if(hdr->e_flags != EF_ARM_ABIMASK        &&
     hdr->e_flags != EF_ARM_ABIVER         &&
     hdr->e_flags != EF_ARM_BE8            &&
     hdr->e_flags != EF_ARM_GCCMASK        &&
     hdr->e_flags != EF_ARM_ABI_FLOAT_HARD &&
     hdr->e_flags != EF_ARM_ABI_FLOAT_SOFT){
    return ERR_EH_FLAGS;
  }
  return ERR_EH_NONE;
}


Err_ELF_Header read_elf_header(FILE *f, Elf32_Ehdr* hdr){

  Err_ELF_Header erreur;

  /* ELF IDENTIFICATION */

  fread_8bits(hdr->e_ident, 16, f);

  erreur = check_ident(hdr);
  if(erreur != ERR_EH_NONE){
    return erreur;
  }

  /* ELF TYPE */

  fread_16bits(&(hdr->e_type), 1, f);

  erreur = check_type(hdr);
  if(erreur != ERR_EH_NONE){
    return erreur;
  }
  
  /* ELF MACHINE */

  fread_16bits(&(hdr->e_machine), 1, f);

  erreur = check_machine(hdr);
  if(erreur != ERR_EH_NONE){
    return erreur;
  }

  /* ELF VERSION */
  
  fread_32bits(&(hdr->e_version), 1, f);

  erreur = check_version(hdr);
  if(erreur != ERR_EH_NONE){
    return erreur;
  }

  /* ELF ENTRY */

  fread_32bits(&(hdr->e_entry), 1, f);

  /* ELF PHOFF */

  fread_32bits(&(hdr->e_phoff), 1, f);
  
  /* ELF SHOFF */

  fread_32bits(&(hdr->e_shoff), 1, f);

  /* ELF FLAGS */

  fread_32bits(&(hdr->e_flags), 1, f);

  erreur = check_flags(hdr);
  if(erreur != ERR_EH_NONE){
    return erreur;
  }

  /* ELF EHSIZE */

  fread_16bits(&(hdr->e_ehsize), 1, f);

  /* ELF PHENTSIZE */

  fread_16bits(&(hdr->e_phentsize), 1, f);

  /* ELF PHNUM */

  fread_16bits(&(hdr->e_phnum), 1, f);

  /* ELF SHENTSIZE */

  fread_16bits(&(hdr->e_shentsize), 1, f);

  /* ELF SHNUM */

  fread_16bits(&(hdr->e_shnum), 1, f);

  /* ELF SHSTRNDX */

  fread_16bits(&(hdr->e_shstrndx), 1, f);

  return ERR_EH_NONE;
}

/*int main(int argc, char *argv[]){
  FILE *f = fopen(argv[1], "r");
  Err_ELF_Header test;
  Elf32_Ehdr hdr;
  test = read_elf_header(f, &hdr);
    if (test ==ERR_EH_NONE){
      printf ("ok\n");
    }
    printf("%d\n", test);
}*/
