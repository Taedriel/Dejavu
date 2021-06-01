PATH_BIN=./bin
PATH_SRC=./src
PATH_DOC=./doc
PATH_OBJ=./obj
PATH_INC=./inc

CC=gcc

CFLAGS = -Wall -Wextra -ansi -pedantic -std=c99 -Wpedantic -g -I$(PATH_INC) -Wno-unused-parameter
LDFLAGS= -lm
PILOT_NAME = Dejavu

SANITIZE=off
ifeq ($(SANITIZE),on)
CFLAGS += -fsanitize=address
LDFLAGS += -fsanitize=address
endif

SRCS = $(wildcard $(PATH_SRC)/*.c)
OBJS = $(patsubst $(PATH_SRC)/%.c, $(PATH_OBJ)/%.o, $(SRCS))

.PHONY: all utils dir clean dist-clean doxy

include $(PATH_SRC)/utils/Makefile

$(PILOT_NAME): all

all: utils dir $(PATH_BIN)/$(PILOT_NAME)
	@echo "\nAll is done !\n"

install: clean all
	rm -f ../GrandPrix2021_4.0.2/drivers/Dejavu
	cp ./bin/Dejavu ../GrandPrix2021_4.0.2/drivers/Dejavu 

dir:
	@mkdir -p $(PATH_BIN)
	@mkdir -p $(PATH_DOC)
	@mkdir -p $(PATH_OBJ)

doxy:	
	@mkdir -p $(PATH_DOC)
	@doxygen

$(PATH_BIN)/$(PILOT_NAME):$(OBJS) $(OBJS_UTILS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(PATH_OBJ)/%.o: $(PATH_SRC)/%.c
	$(CC) -o $@ $^ -c $(CFLAGS)

clean:
	rm -f $(PATH_OBJ)/*.o

dist-clean: clean
	rm -fr $(PATH_BIN)
	rm -fr $(PATH_DOC)
	rm -fr $(PATH_LIB)