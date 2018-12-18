BIN_DIR=bin
INC_DIR=includes

CC=clang
CSTD=c99
CFLAGS=-Wall -Werror --std=$(CSTD) -I$(INC_DIR)



init:
	mkdir bin; mkdir includes

usage:
	@echo "Includes files : $(INC_DIR)\nExec files : $(BIN_DIR)"
	@echo "Current compilation : $(CC) $(CFLAGS)"
	@echo "Objectif : Dobby"
clean:
	rm -rf $(BIN_DIR)/* *.o ; mv *.h $(INC_DIR)/

%.o: %.c $(INC_DIR)/%.h
	$(CC) $(CFLAGS) $(IFLAGS) $< -c

#Final executables

$(BIN_DIR)/dobby-read-header: read-header
	mv $< $@

$(BIN_DIR)/dobby-read-section-table: read-section-table
	mv $< $@

#Tmp executables
read-header: read-header.o elf_header.o fread.o util.o
read-section-table: read-section-table.o elf_header.o elf_section.o fread.o util.o

#Objects
read-header.o: $(INC_DIR)/elf_types.h

elf_header.o: $(INC_DIR)/elf_types.h $(INC_DIR)/fread.h

elf.o: $(INC_DIR)/elf_types.h
elf_section.o: $(INC_DIR)/elf_types.h $(INC_DIR)/elf_header.h $(INC_DIR)/fread.h

fread.o: $(INC_DIR)/util.h

#Convenient to headers

$(INC_DIR)/elf_types.h: $(INC_DIR)/elf_types_*.h

