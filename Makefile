BIN_DIR=bin
INC_DIR=includes

CC=clang
CSTD=c99
CFLAGS=-Wall -Werror --std=$(CSTD) -I$(INC_DIR)


usage:
	@echo "make config : afficher les variables actuelles"
	@echo "make init : créer les répertoires (sans test d'existence) et y envoyer les fichiers"
	@echo "make clean: supprimer les objets redondants et exécutables"
	@echo "make bin/dobby-<Tabulation> : éxécutables disponibles"

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

$(BIN_DIR)/dobby-read-section-table: read-section-table
	mv $< $@
$(BIN_DIR)/dobby-read-section-content: read-section-content
	mv $< $@

#Tmp executables
read-header: read-header.o elf_header.o fread.o util.o
read-section-table: read-section-table.o elf_header.o elf_section.o fread.o util.o
read-section-content: read-section-content.o elf_header.o elf_section.o elf_section_content.o fread.o util.o

#Objects

elf_header.o: $(INC_DIR)/elf_types.h $(INC_DIR)/fread.h

elf.o: $(INC_DIR)/elf_types.h
elf_section.o: $(INC_DIR)/elf_types.h $(INC_DIR)/elf_header.h $(INC_DIR)/fread.h

fread.o: $(INC_DIR)/util.h

#Convenient to headers

$(INC_DIR)/elf_types.h: $(INC_DIR)/elf_types_*.h

