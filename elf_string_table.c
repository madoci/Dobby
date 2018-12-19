#include "elf_string_table.h"

char * extract_string_table(FILE *f, Elf32_Shdr str){
    char* str_table = malloc(sizeof(char)*str.sh_size);
    fseek(f,str.sh_offset,SEEK_SET);
    fread(str_table,1,str.sh_size,f);
    return str_table;
}
