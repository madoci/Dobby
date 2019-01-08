BIN_DIR=bin
INC_DIR=includes
OBJ_DIR=obj

CC=clang
CSTD=c99
CFLAGS=-Wall -Werror --std=$(CSTD) -I$(INC_DIR) -g


usage:
	@echo "make config : afficher les variables actuelles"
	@echo "make init : créer les répertoires (sans test d'existence) et y envoyer les fichiers"
	@echo "make clean: supprimer les objets redondants et exécutables"
	@echo "make bin/dobby-<Tabulation> : exécutables disponibles"

config:
	@echo "Includes files : $(INC_DIR) Exec files : $(BIN_DIR)"
	@echo "Current compilation : $(CC) $(CFLAGS)"
	@echo "Objectif : Dobby"

init:
	mkdir bin; mkdir includes; mv *. $(INC_DIR)/

clean: clean_bin clean_obj

clean_bin:
	rm -rf $(BIN_DIR)/*

clean_obj:
	rm -rf $(OBJ_DIR)/*.o

$(OBJ_DIR)/%.o: %.c $(INC_DIR)/%.h
	$(CC) $(CFLAGS) $(IFLAGS) $< -c -o $@

#Final executables

$(BIN_DIR)/dobby-%: %.c
	$(CC) $(CFLAGS) $(IFLAGS) $^ -o $@

$(BIN_DIR)/dobby-read-header:                  $(OBJ_DIR)/fread.o $(OBJ_DIR)/util.o $(OBJ_DIR)/elf_header.o
$(BIN_DIR)/dobby-read-section-table:           $(OBJ_DIR)/fread.o $(OBJ_DIR)/util.o $(OBJ_DIR)/elf_header.o $(OBJ_DIR)/elf_section_table.o $(OBJ_DIR)/elf_section_content.o
$(BIN_DIR)/dobby-read-section-content:         $(OBJ_DIR)/fread.o $(OBJ_DIR)/util.o $(OBJ_DIR)/elf_header.o $(OBJ_DIR)/elf_section_table.o $(OBJ_DIR)/elf_section_content.o
$(BIN_DIR)/dobby-read-relocation-table:        $(OBJ_DIR)/fread.o $(OBJ_DIR)/util.o $(OBJ_DIR)/elf_header.o $(OBJ_DIR)/elf_section_table.o $(OBJ_DIR)/elf_section_content.o $(OBJ_DIR)/elf_relocation.o
$(BIN_DIR)/dobby-read-symbol-table:            $(OBJ_DIR)/fread.o $(OBJ_DIR)/util.o $(OBJ_DIR)/elf_header.o $(OBJ_DIR)/elf_section_table.o $(OBJ_DIR)/elf_section_content.o $(OBJ_DIR)/elf_symbol.o
$(BIN_DIR)/dobby-load-elf-file:                $(OBJ_DIR)/fread.o $(OBJ_DIR)/util.o $(OBJ_DIR)/elf_header.o $(OBJ_DIR)/elf_section_table.o $(OBJ_DIR)/elf_section_content.o $(OBJ_DIR)/elf_file.o $(OBJ_DIR)/elf_load_section.o $(OBJ_DIR)/elf_load_symbol.o

#Objects

$(OBJ_DIR)/elf_header.o:          $(INC_DIR)/elf_types.h $(INC_DIR)/fread.h
$(OBJ_DIR)/elf_section_table.o:   $(INC_DIR)/elf_types.h $(INC_DIR)/fread.h
$(OBJ_DIR)/elf_section_content.o: $(INC_DIR)/elf_types.h $(INC_DIR)/fread.h
$(OBJ_DIR)/elf_relocation.o:      $(INC_DIR)/elf_types.h $(INC_DIR)/fread.h
$(OBJ_DIR)/elf_symbol.o:          $(INC_DIR)/elf_types.h $(INC_DIR)/fread.h
$(OBJ_DIR)/elf_file.o:            $(INC_DIR)/elf_types.h
$(OBJ_DIR)/elf_load_section.o:    $(INC_DIR)/elf_types.h
$(OBJ_DIR)/elf_load_symbol.o:     $(INC_DIR)/elf_types.h $(INC_DIR)/fread.h

$(OBJ_DIR)/fread.o: $(INC_DIR)/util.h

#Convenient to headers

$(INC_DIR)/elf_types.h: $(INC_DIR)/elf_types_*.h
