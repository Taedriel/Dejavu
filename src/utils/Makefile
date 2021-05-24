PATH_SRCS_UTILS = ./src/utils
SRCS_UTILS = $(wildcard $(PATH_SRCS_UTILS)/*.c)
OBJS_UTILS = $(patsubst $(PATH_SRCS_UTILS)/%.c, $(PATH_OBJ)/%.o, $(SRCS_UTILS))

utils: $(OBJS_UTILS)
	@echo "\nUtils is done !\n"

$(PATH_OBJ)/%.o: $(PATH_SRCS_UTILS)/%.c
	$(CC) -o $@ $^ -c $(CFLAGS)
