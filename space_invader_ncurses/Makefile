CC = gcc
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
LIB =  ../space_invader/space_invader.a
BIN = space-invader

%.o: %.c
	$(CC) -g -c $< -o $@

$(BIN): $(OBJ)
	$(CC) $(OBJ) $(LIB) -o $(BIN) -lncurses

.PHONY: clean
clean: $(BIN)
	@rm $(OBJ) $(BIN)
