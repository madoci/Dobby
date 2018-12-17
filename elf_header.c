#include "elf_types_header.h"
#include "elf_header.h"

#include "../elf_linker-1.0/util.h"


Err_ELF_Header check_ident(Elf32_Ehdr* hdr){
  if(hdr->e_ident[EI_MAG0] != ELFMAG0 ||
     hdr->e_ident[EI_MAG1] != ELFMAG1 ||
     hdr->e_ident[EI_MAG2] != ELFMAG2 ||
     hdr->e_ident[EI_MAG3] != ELFMAG3){
    printf("%d\n, 0x%02x\n",hdr->e_ident[EI_MAG0],hdr->e_ident[EI_MAG0]);
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

  fread(hdr->e_ident, 1, 16, f);

  erreur = check_ident(hdr);
  if(erreur != ERR_EH_NONE){
    return erreur;
  }

  /* ELF TYPE */

  fread(&(hdr->e_type), 2, 1, f);
  hdr->e_type = reverse_2(hdr->e_type);

  erreur = check_type(hdr);
  if(erreur != ERR_EH_NONE){
    return erreur;
  }
  
  /* ELF MACHINE */

  fread(&(hdr->e_machine), 2, 1, f);
  hdr->e_machine = reverse_2(hdr->e_machine);

  erreur = check_machine(hdr);
  if(erreur != ERR_EH_NONE){
    return erreur;
  }

  /* ELF VERSION */
  
  fread(&(hdr->e_version), 4, 1, f);
  hdr->e_version = reverse_4(hdr->e_version);

  erreur = check_version(hdr);
  if(erreur != ERR_EH_NONE){
    return erreur;
  }

  /* ELF ENTRY */

  fread(&(hdr->e_entry), 4, 1, f);
  hdr->e_entry = reverse_4(hdr->e_entry);

  /* ELF PHOFF */

  fread(&(hdr->e_phoff), 4, 1, f);
  hdr->e_phoff = reverse_4(hdr->e_phoff);
  
  /* ELF SHOFF */

  fread(&(hdr->e_shoff), 4, 1, f);
  hdr->e_shoff = reverse_4(hdr->e_shoff);

  /* ELF FLAGS */

  fread(&(hdr->e_flags), 4, 1, f);
  hdr->e_flags = reverse_4(hdr->e_flags);

  erreur = check_flags(hdr);
  if(erreur != ERR_EH_NONE){
    return erreur;
  }

  /* ELF EHSIZE */

  fread(&(hdr->e_ehsize), 2, 1, f);

  /* ELF PHENTSIZE */

  fread(&(hdr->e_phentsize), 2, 1, f);

  /* ELF PHNUM */

  fread(&(hdr->e_phnum), 2, 1, f);

  /* ELF SHENTSIZE */

  fread(&(hdr->e_shentsize), 2, 1, f);

  /* ELF SHNUM */

  fread(&(hdr->e_shnum), 2, 1, f);

  /* ELF SHSTRNDX */

  fread(&(hdr->e_shstrndx), 2, 1, f);

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