PATH_BIN=./bin
PATH_SRC=./src
PATH_DOC=./doc
PATH_OBJ=./obj
PATH_INC=./inc

CC=gcc

CFLAGS = -Wall -Wextra -ansi -pedantic -Wpedantic -g -I$(PATH_INC)
LDFLAGS= -lm
PILOT_NAME = $(PATH_BIN)/Dejavu

SANITIZE=off
ifeq ($(SANITIZE),on)
CFLAGS += -fsanitize=address
endif

OBJS = $(PATH_OBJ)/main.o $(PATH_OBJ)/racing_driver.o $(PATH_OBJ)/racing_io.o $(PATH_OBJ)/racing_map.o

.PHONY: all dir clean dist-clean doxy

all: dir $(PILOT_NAME)
	@echo "all is done !"
	@make -s clean

dir:
	@mkdir -p $(PATH_BIN)
	@mkdir -p $(PATH_DOC)
	@mkdir -p $(PATH_OBJ)

doxy:	
	@mkdir -p $(PATH_DOC)
	@doxygen

$(PILOT_NAME):$(OBJS)
	@$(CC) -o $@ $^ $(LDFLAGS)

$(PATH_OBJ)/main.o:  $(PATH_SRC)/main.c
	@$(CC) -o $@ $^ -c $(CFLAGS)

$(PATH_OBJ)/racing_driver.o: $(PATH_SRC)/racing_driver.c
	@$(CC) -o $@ $^ -c $(CFLAGS)

$(PATH_OBJ)/racing_io.o: $(PATH_SRC)/racing_io.c
	@$(CC) -o $@ $^ -c $(CFLAGS)

$(PATH_OBJ)/racing_map.o: $(PATH_SRC)/racing_map.c
	@$(CC) -o $@ $^ -c $(CFLAGS)

clean:
	@rm -f *.o

dist-clean: clean
	@rm -fr $(PATH_BIN)
	@rm -fr $(PATH_DOC)
	@rm -fr $(PATH_LIB)