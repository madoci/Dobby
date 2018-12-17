#include "elf_types.h"
#include "elf_header.h"


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


ERR_ELF_READER check_type(Elf32_Ehdr* hdr){
  if(hdr->e_type != ET_NONE   &&
     hdr->e_type != ET_REL    &&
     hdr->e_type != ET_EXEC   &&
     hdr->e_type != ET_DYN    &&
     hdr->e_type != ET_CORE   &&
     hdr->e_type != ET_LOPROC &&
     hdr->e_type != ET_HIPROC){
    return 0;
  }
  return 1;
}


ERR_ELF_READER check_machine(Elf32_Ehdr* hdr){
  if(hdr->e_machine != EM_NONE &&
     hdr->e_machine != EM_ARM){
    return 0;
  }
  return 1;
}


ERR_ELF_READER check_version(Elf32_Ehdr* hdr){
  if(hdr->e_version != EV_NONE &&
     hdr->e_version != EV_CURRENT){
    return 0;
  }
  return 1;
}


ERR_ELF_READER check_flags(Elf32_Ehdr* hdr){
  if(hdr->e_flags != EF_ARM_ABIMASK        &&
     hdr->e_flags != EF_ARM_ABIVER         &&
     hdr->e_flags != EF_ARM_BE8            &&
     hdr->e_flags != EF_ARM_GCCMASK        &&
     hdr->e_flags != EF_ARM_ABI_FLOAT_HARD &&
     hdr->e_flags != EF_ARM_ABI_FLOAT_SOFT){
    return 0;
  }
  return 1;
}


ERR_ELF_READER read_elf_header(FILE *f, Elf32_Ehdr* hdr){

  /* ELF IDENTIFICATION */

  fread(hdr->e_ident, 1, 16, f);

  ERR_ELF_READER erreur = check_ident(hdr);
  if(erreur != ERR_NONE){
    return erreur;
  }

  /* ELF TYPE */

  fread(&(hdr->e_type), 2, 1, f);

  erreur = check_type(hdr);
  if(erreur != ERR_NONE){
    return erreur;
  }
  
  /* ELF MACHINE */

  fread(&(hdr->e_machine), 2, 1, f);

  erreur = check_machine(hdr);
  if(erreur != ERR_NONE){
    return erreur;
  }

  /* ELF VERSION */
  
  fread(&(hdr->e_version), 4, 1, f);
  erreur = check_version(hdr);
  if(erreur != ERR_NONE){
    return erreur;
  }

  /* ELF ENTRY */

  fread(&(hdr->e_entry), 4, 1, f);

  /* ELF PHOFF */

  fread(&(hdr->e_phoff), 4, 1, f);
  
  /* ELF SHOFF */

  fread(&(hdr->e_shoff), 4, 1, f);

  /* ELF FLAGS */

  fread(&(hdr->e_flags), 4, 1, f);
  erreur = check_flags(hdr);
  if(erreur != ERR_NONE){
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

  return 1;
}