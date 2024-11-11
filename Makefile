EXEC = mon_interpreteur
SRC_OBJ = obj
SRC_DIR = src
INCLUDE_DIR = include

SRC_FILES = $(SRC_DIR)/ast.c $(SRC_DIR)/interpreter.c $(SRC_DIR)/lexer.c $(SRC_DIR)/parser.c \
            $(SRC_DIR)/symbolTable.c $(SRC_DIR)/main.c

CC = gcc
CFLAGS = -Wall -I$(INCLUDE_DIR)

OBJ_FILES = $(SRC_OBJ)/ast.o $(SRC_OBJ)/interpreter.o $(SRC_OBJ)/lexer.o $(SRC_OBJ)/parser.o \
            $(SRC_OBJ)/symbolTable.o $(SRC_OBJ)/main.o

$(EXEC): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

$(SRC_OBJ)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(SRC_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(EXEC)

.PHONY: all clean
