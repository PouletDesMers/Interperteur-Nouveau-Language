EXEC = interpreter

SRC_DIR = src
INCLUDE_DIR = include

SRC_FILES = $(SRC_DIR)/ast.c $(SRC_DIR)/interpreter.c $(SRC_DIR)/lexer.c $(SRC_DIR)/parser.c \
            $(SRC_DIR)/symbolTable.c $(SRC_DIR)/main.c

CC = gcc
CFLAGS = -Wall -I$(INCLUDE_DIR)

OBJ_FILES = $(SRC_FILES:.c=.o)

$(EXEC): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE_DIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(EXEC)

.PHONY: all clean
