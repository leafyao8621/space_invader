CC = gcc
AR = ar
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
LIB = space_invader.a

%.o: %.c
	$(CC) -g -c $< -o $@

$(LIB): $(OBJ)
	@cp src/space_invader.h .
	$(AR) rcs $@ $^

all: clean
clean: $(LIB)
	@rm $(OBJ) $(LIB) space_invader.h
