#include "elf_header.h"

#include "fread.h"

#define printf_8x(s,x) printf("\t%-50s\t0x%08x\n",s,x)
#define printf_d(s,d) printf("\t%-50s\t%d\n",s,d)
#define printf_s(s,s2) printf("\t%-50s\t%s\n",s,s2)
#define printf_se(s) printf("\t%-50s\t",s)


/* READ HEADER */

Err_ELF_Header check_ident(Elf32_Ehdr* hdr){
  if (hdr->e_ident[EI_MAG0] != ELFMAG0 ||
      hdr->e_ident[EI_MAG1] != ELFMAG1 ||
      hdr->e_ident[EI_MAG2] != ELFMAG2 ||
      hdr->e_ident[EI_MAG3] != ELFMAG3){
    return ERR_EH_IMAG;
  }
  if (hdr->e_ident[EI_CLASS] != ELFCLASSNONE &&
      hdr->e_ident[EI_CLASS] != ELFCLASS32  &&
      hdr->e_ident[EI_CLASS] != ELFCLASS64){
    return ERR_EH_ICLASS;
  }
  if (hdr->e_ident[EI_DATA] != ELFDATANONE &&
      hdr->e_ident[EI_DATA] != ELFDATA2LSB &&
      hdr->e_ident[EI_DATA] != ELFDATA2MSB){
    return ERR_EH_IDATA;
  }
  if (hdr->e_ident[EI_VERSION] != EI_VALVERSION){
    return ERR_EH_IVERSION;
  }
  if (hdr->e_ident[EI_OSABI] != ELFOSABI_ARM_AEABI &&
      hdr->e_ident[EI_OSABI] != ELFOSABI_NONE){
    return ERR_EH_IOSABI;
  }
  if (hdr->e_ident[EI_PAD] != EI_VALPAD){
    return ERR_EH_IPAD;
  }
  return ERR_EH_NONE;
}

Err_ELF_Header check_type(Elf32_Ehdr* hdr){
  if (hdr->e_type != ET_NONE   &&
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
  if (hdr->e_machine != EM_NONE &&
      hdr->e_machine != EM_ARM){
    return ERR_EH_MACHINE;
  }
  return ERR_EH_NONE;
}

Err_ELF_Header check_version(Elf32_Ehdr* hdr){
  if (hdr->e_version != EV_NONE &&
      hdr->e_version != EV_CURRENT){
    return ERR_EH_VERSION;
  }
  return ERR_EH_NONE;
}

Err_ELF_Header check_flags(Elf32_Ehdr* hdr){
  if ((hdr->e_flags & ~EF_ARM_ABIMASK)        &
      (hdr->e_flags & ~EF_ARM_BE8)            &
      (hdr->e_flags & ~EF_ARM_GCCMASK)        &
      (hdr->e_flags & ~EF_ARM_ABI_FLOAT_HARD) &
      (hdr->e_flags & ~EF_ARM_ABI_FLOAT_SOFT)){
    return ERR_EH_FLAGS;
  }
  return ERR_EH_NONE;
}

Err_ELF_Header read_elf_header(FILE *f, Elf32_Ehdr* hdr){

  Err_ELF_Header erreur;

  /* ELF IDENTIFICATION */

  fread_8bits(hdr->e_ident, 16, f);

  erreur = check_ident(hdr);
  if (erreur != ERR_EH_NONE){
    return erreur;
  }

  if (hdr->e_ident[EI_DATA] == ELFDATA2MSB){
    set_big_endian();
  } else {
    set_little_endian();
  }

  /* ELF TYPE */

  fread_16bits(&(hdr->e_type), 1, f);

  erreur = check_type(hdr);
  if (erreur != ERR_EH_NONE){
    return erreur;
  }

  /* ELF MACHINE */

  fread_16bits(&(hdr->e_machine), 1, f);

  erreur = check_machine(hdr);
  if (erreur != ERR_EH_NONE){
    return erreur;
  }

  /* ELF VERSION */

  fread_32bits(&(hdr->e_version), 1, f);

  erreur = check_version(hdr);
  if (erreur != ERR_EH_NONE){
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
  if (erreur != ERR_EH_NONE){
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


/* DISPLAY HEADER */

void display_class(unsigned char class){
  switch (class){
    case ELFCLASSNONE:
      printf_s("Classe:","ELF invalid arch");
      break;
    case ELFCLASS32:
      printf_s("Classe:","ELF32");
      break;
    case ELFCLASS64:
      printf_s("Classe:","ELF64");
      break;
    default:
    	break;
  }
}

void display_data(unsigned char data){
  switch (data){
    case ELFDATANONE:
      printf_s("Données:","Invalid data");
      break;
    case ELFDATA2LSB:
      printf_s("Données:","Little Endian");
      break;
    case ELFDATA2MSB:
      printf_s("Données:","Big Endian");
      break;
    default:
    	break;
  }
}

void display_eiVersion(unsigned char version){
  printf_d("Version courante:",version);
}

void display_osabi(unsigned char osabi){
  switch (osabi){
    case ELFOSABI_NONE:
      printf_s("OS/ABI:","None");
      break;
    case ELFOSABI_ARM_AEABI:
      printf_s("OS/ABI:","ARM_AEABI");
      break;
    default:;
  }
}

void display_ident(unsigned char e_ident[]){
  display_class(e_ident[EI_CLASS]);
  display_data(e_ident[EI_DATA]);
  display_eiVersion(e_ident[EI_VERSION]);
  display_osabi(e_ident[EI_OSABI]);
}

void display_type(Elf32_Half type){
  switch (type){
    case ET_NONE:
      printf_s("Type:","No file type");
      break;
    case ET_REL:
      printf_s("Type:","Relocatable file");
      break;
    case ET_EXEC:
      printf_s("Type:","Executable file");
      break;
    case ET_DYN:
      printf_s("Type:","Shared object file");
      break;
    case ET_CORE:
      printf_s("Type:","Core file");
      break;
    case ET_LOPROC:
      // Fall through
    case ET_HIPROC:
      printf_s("Type:","Processor-specific");
      break;
     default:
     	break;
  }
}

void display_machine(Elf32_Half machine){
  switch (machine){
    case EM_NONE:
      printf_s("Machine:","No machine");
      break;
    case EM_ARM:
      printf_s("Machine:","ARM");
      break;
    default:
    	break;
  }
}

void display_fileVersion(Elf32_Word  version){
  switch (version){
    case EV_NONE:
      printf_s("Version:", "Invalid version");
      break;
    case EV_CURRENT:
      printf_s("Version:","Current version");
      break;
    default:
    	break;
  }
}

void display_flags(Elf32_Word flag){
  printf_se("Fanions:");

  if (flag & EF_ARM_BE8){
    printf("EF_ARM_BE8 ");
  }
  if (flag & EF_ARM_GCCMASK){
    printf("GCC(0x%08x) ",flag & EF_ARM_GCCMASK);
  }
  if (flag & EF_ARM_ABI_FLOAT_HARD){
    printf("EF_ARM_ABI_FLOAT_HARD ");
  }
  if (flag & EF_ARM_ABI_FLOAT_SOFT){
    printf("ARM ABI_FLOAT_SOFT ");
  }

  printf("\n");
}

void display_verAbi(Elf32_Word flag){
  printf_d("Version ABI:", (flag & EF_ARM_ABIMASK) >>24);
}

void display_header(Elf32_Ehdr * Elf){
  printf("En-tête ELF:\n");
  printf("\tMagique: ");
  for (int i = 0;i < EI_NIDENT;i++){
    printf("%02x ", Elf->e_ident[i]);
  }
  printf("\n");
  display_ident(Elf->e_ident);
  display_verAbi(Elf->e_flags);
  display_type(Elf->e_type);
  display_machine(Elf->e_machine);
  display_fileVersion(Elf->e_version);
  printf_8x("Adresse du point d'entrée:", Elf->e_entry);
  printf_d("Début des en-têtes du programme:", Elf->e_phoff);
  printf_d("Début des en-têtes de section:", Elf->e_shoff);
  display_flags(Elf->e_flags);
  printf_d("Taille de cet en-tête du programme:", Elf->e_ehsize);
  printf_d("Taille de l'en-tête du programme:", Elf->e_phentsize);
  printf_d("Nombre d'en-tête du programme:", Elf->e_phnum);
  printf_d("Taille des en-têtes de section:", Elf->e_shentsize);
  printf_d("Nombre d'en-tête de section:", Elf->e_shnum);
  printf_d("Table d'indexe des chaines d'en-tête de section:", Elf->e_shstrndx);
}
