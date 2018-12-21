#include "elf_relocation.h"

#include "fread.h"
#include "elf_section_content.h"


/* READ RELOCATION TABLE */

Elf32_Rel read_rel(FILE* f){
  Elf32_Rel r;
  fread_32bits(&(r.r_offset), 1, f);
  fread_32bits(&(r.r_info), 1, f);
  return r;
}

Elf32_Rela read_rela(FILE* f){
  Elf32_Rela r;
  fread_32bits(&(r.r_offset), 1, f);
  fread_32bits(&(r.r_info), 1, f);
  fread_32bits(&(r.r_addend), 1, f);
  return r;
}


void read_rel_section(FILE* f, Elf32_Shdr *hdr, Elf32_Rel entries[]){
  unsigned int i;
  for (i=0; i<(hdr->sh_size/sizeof(Elf32_Rel)); i++){
    fseek(f, hdr->sh_offset + i * sizeof(Elf32_Rel), SEEK_SET);
    entries[i] = read_rel(f);
  }
}

void read_rela_section(FILE* f, Elf32_Shdr *hdr, Elf32_Rela entries[]){
  unsigned int i;
  for (i=0; i<(hdr->sh_size/sizeof(Elf32_Rela)); i++){
    fseek(f, hdr->sh_offset+i*sizeof(Elf32_Rela), SEEK_SET);
    entries[i] = read_rela(f);
  }
}


/* DISPLAY RELOCATION TABLE */

const char * relocation_type(Elf_RelT type){
  switch (type){
    case R_386_NONE:
      return "R_386_NONE";
    case R_386_32:
      return "R_386_32:";
    case R_ARM_ABS32:
      return "R_ARM_ABS32";
    case R_ARM_ABS16:
      return "R_ARM_ABS16";
    case R_ARM_ABS12:
      return "R_ARM_ABS12";
    case R_ARM_ABS8:
      return "R_ARM_ABS8";
    case R_ARM_ABS32_NOI:
      return "R_ARM_ABS32_NOI";
    case R_ARM_JUMP24:
      return "R_ARM_JUMP24";
    case R_ARM_CALL:
      return "R_ARM_CALL";
    default:
      return "erreurType";
  }
}

void display_rel_table(FILE* f, Elf32_Shdr *shdr){
  Elf32_Rel entries[shdr->sh_size/sizeof(Elf32_Rel)];
  read_rel_section(f, shdr, entries);

  printf(" %-8s  %-8s  %-15s  %-8s\n",
         "Decalage", "Info", "Type", "Ind.-sym");

  unsigned int i;
  for (i=0; i<shdr->sh_size/sizeof(Elf32_Rel); i++){
    const Elf32_Addr decal = entries[i].r_offset;
    const Elf32_Word inf = entries[i].r_info;
    const char *type = relocation_type(ELF32_R_TYPE(entries[i].r_info));
    const Elf32_Word ind = ELF32_R_SYM(entries[i].r_info);
    printf(" %08x  %08x  %-15s  %-8d\n",
           decal, inf, type, ind);
  }
}

void display_rela_table(FILE* f, Elf32_Shdr *shdr){
  Elf32_Rela entries[shdr->sh_size / sizeof(Elf32_Rela)];
  read_rela_section(f, shdr, entries);

  printf(" %-8s  %-8s  %-15s  %-8s  %-8s\n",
         "Decalage", "Info", "Type", "Ind.-sym", "Addend");

  unsigned int i;
  for (i=0; i<shdr->sh_size/sizeof(Elf32_Rel); i++){
    const Elf32_Addr decal = entries[i].r_offset;
    const Elf32_Word inf = entries[i].r_info;
    const char *type = relocation_type(ELF32_R_TYPE(entries[i].r_info));
    const Elf32_Word ind = ELF32_R_SYM(entries[i].r_info);
    const Elf32_Sword addend = entries[i].r_addend;
    printf(" %08x  %08x  %-15s  %-8d  %-8d\n",
           decal, inf, type, ind, addend);
  }
}

void display_all_relocation_table(FILE* f, Elf32_Ehdr *hdr, Elf32_Shdr shdr[]){
  unsigned char *str_table = read_elf_section_content(f, shdr[hdr->e_shstrndx]);

  unsigned int i;
  for (i=0; i<hdr->e_shnum; i++){
    if (shdr[i].sh_type == SHT_REL){
      printf("\nSection de relocalisation '%s' :\n", str_table + shdr[i].sh_name);
    	display_rel_table(f, &shdr[i]);
    }
    else if (shdr[i].sh_type == SHT_RELA){
      printf("\nSection de relocalisation '%s' :\n", str_table + shdr[i].sh_name);
    	display_rela_table(f, &shdr[i]);
    }
  }
  free(str_table);
}
