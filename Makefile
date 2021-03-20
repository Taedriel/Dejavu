PATH_BIN=./bin
PATH_LIB=./lib
PATH_SRC=./src
PATH_DOC=./doc

CC=gcc

CFLAGS= -g -Wall 
LDFLAGS=
EXE=$(PATH_BIN)/main

.PHONY: all lib dir clean dist-clean doxy

all: $(EXE) lib
	@echo "all is done !"
	@make -s clean

dir:
	@mkdir -p $(PATH_LIB)
	@mkdir -p $(PATH_BIN)
	@mkdir -p $(PATH_DOC)

doxy:	
	@mkdir -p $(PATH_DOC)
	@doxygen

main.o: main.c
	@$(CC) -o $@ $^ -c $(CFLAGS)

clean:
	@rm -f *.o

dist-clean: clean
	@rm -fr $(PATH_BIN)
	@rm -fr $(PATH_DOC)
	@rm -fr $(PATH_LIB)