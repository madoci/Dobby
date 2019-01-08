#include "elf_relocation.h"

#include "fread.h"


/* READ RELOCATION TABLE */

Elf32_Rel read_rel(unsigned char* line){
  Elf32_Rel r;

  read_32bits(&(r.r_offset), line);
  line += 4;
  read_32bits(&(r.r_info), line);

  return r;
}

Elf32_Rela read_rela(unsigned char* line){
  Elf32_Rela r;

  read_32bits(&(r.r_offset), line);
  line += 4;
  read_32bits(&(r.r_info), line);
  line += 4;
  read_32bits(&(r.r_addend), line);

  return r;
}


void read_rel_section(unsigned char* section_content, Elf32_Shdr *hdr, Elf32_Rel entries[]){
  unsigned int i;
  for (i=0; i<(hdr->sh_size/sizeof(Elf32_Rel)); i++){
    unsigned char* line = section_content + i * sizeof(Elf32_Rel); //fseek(f, hdr->sh_offset + i * sizeof(Elf32_Rel), SEEK_SET);
    entries[i] = read_rel(line);
  }
}

void read_rela_section(unsigned char* section_content, Elf32_Shdr *hdr, Elf32_Rela entries[]){
  unsigned int i;
  for (i=0; i<(hdr->sh_size/sizeof(Elf32_Rela)); i++){
    unsigned char* line = section_content + i * sizeof(Elf32_Rela); //fseek(f, hdr->sh_offset + i * sizeof(Elf32_Rela), SEEK_SET);
    entries[i] = read_rela(line);
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


void display_rel_table(Elf32_Rel entries[], const unsigned int num_entries, const unsigned char *name){
  printf("\nSection de relocalisation '%s' :\n", name);

  printf("%-8s  %-8s  %-15s  %-8s\n",
         "Decalage", "Info", "Type", "Ind.-sym");

  unsigned int i;
  for (i=0; i<num_entries; i++){
    const Elf32_Addr decal = entries[i].r_offset;
    const Elf32_Word inf = entries[i].r_info;
    const char *type = relocation_type(ELF32_R_TYPE(entries[i].r_info));
    const Elf32_Word ind = ELF32_R_SYM(entries[i].r_info);
    printf("%08x  %08x  %-15s  %-8d\n",
           decal, inf, type, ind);
  }
}


void display_rela_table(Elf32_Rela entries[], const unsigned int num_entries, const unsigned char *name){
  printf("\nSection de relocalisation '%s' :\n", name);

  printf("%-8s  %-8s  %-15s  %-8s  %-8s\n",
         "Decalage", "Info", "Type", "Ind.-sym", "Addend");

  unsigned int i;
  for (i=0; i<num_entries; i++){
    const Elf32_Addr decal = entries[i].r_offset;
    const Elf32_Word inf = entries[i].r_info;
    const char *type = relocation_type(ELF32_R_TYPE(entries[i].r_info));
    const Elf32_Word ind = ELF32_R_SYM(entries[i].r_info);
    const Elf32_Sword addend = entries[i].r_addend;
    printf("%08x  %08x  %-15s  %-8d  %-8d\n",
           decal, inf, type, ind, addend);
  }
}
