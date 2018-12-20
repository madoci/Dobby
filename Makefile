BIN_DIR=bin
INC_DIR=includes

CC=clang
CSTD=c99
CFLAGS=-Wall -Werror --std=$(CSTD) -I$(INC_DIR)


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
	rm -rf $(BIN_DIR)/* read-header read-section-table

clean_obj:
	rm -rf *.o

%.o: %.c $(INC_DIR)/%.h
	$(CC) $(CFLAGS) $(IFLAGS) $< -c

#Final executables

$(BIN_DIR)/dobby-read-header: read-header
	mv $< $@

$(BIN_DIR)/dobby-read-header:           $(OBJ_DIR)/elf_header.o                                                                  $(OBJ_DIR)/fread.o $(OBJ_DIR)/util.o
$(BIN_DIR)/dobby-read-section-table:    $(OBJ_DIR)/elf_header.o $(OBJ_DIR)/elf_section_table.o                                   $(OBJ_DIR)/fread.o $(OBJ_DIR)/util.o $(OBJ_DIR)/elf_string_table.o
$(BIN_DIR)/dobby-read-section-content:  $(OBJ_DIR)/elf_header.o $(OBJ_DIR)/elf_section_table.o $(OBJ_DIR)/elf_section_content.o  $(OBJ_DIR)/fread.o $(OBJ_DIR)/util.o $(OBJ_DIR)/elf_string_table.o
$(BIN_DIR)/dobby-read-relocation-table: $(OBJ_DIR)/elf_header.o $(OBJ_DIR)/elf_section_table.o $(OBJ_DIR)/elf_relocation.o       $(OBJ_DIR)/fread.o $(OBJ_DIR)/util.o $(OBJ_DIR)/elf_string_table.o
$(BIN_DIR)/elf_symbol: 					$(OBJ_DIR)/elf_symbol.o

#Objects

$(OBJ_DIR)/elf_header.o: $(INC_DIR)/elf_types.h $(INC_DIR)/fread.h

$(OBJ_DIR)/elf.o: $(INC_DIR)/elf_types.h
$(OBJ_DIR)/elf_section_table.o: $(INC_DIR)/elf_types.h $(INC_DIR)/elf_header.h $(INC_DIR)/fread.h

$(OBJ_DIR)/fread.o: $(INC_DIR)/util.h

$(OBJ_DIR)/elf_symbol.o: $(INC_DIR)/elf_symbol.h $(INC_DIR)/elf_types_symbol.h $(INC_DIR)/elf_section_table.h $(INC_DIR)/fread.h

#Convenient to headers

$(INC_DIR)/elf_types.h: $(INC_DIR)/elf_types_*.h
