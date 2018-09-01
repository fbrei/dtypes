# File paths
SRC=src
BIN=bin
OBJ=obj
SRC=src
TEST=$(SRC)/test
OBJTEST=$(OBJ)/test

CC=gcc
CFLAGS=-O0 -ggdb -Wall -Wextra -Wpedantic -Iinclude
LFLAGS=-lm

BASEDEPS=$(OBJ)/darray.o

graph_test: $(OBJ)/graph.o $(OBJ)/test/graph_test.o $(BASEDEPS)
	mkdir -p $(BIN)
	$(CC) -o $(BIN)/$@ $^ $(LFLAGS)
	valgrind --tool=memcheck --leak-check=full $(BIN)/graph_test

darray_test: $(OBJ)/darray.o $(OBJ)/test/darray_test.o $(BASEDEPS)
	mkdir -p $(BIN)
	$(CC) -o $(BIN)/$@ $^ $(LFLAGS)
	valgrind --tool=memcheck --leak-check=full $(BIN)/$@

obj/%.o: $(SRC)/%.c tmpdirs
	$(CC) -c -o $@ $< $(CFLAGS)

obj/test/%.o: $(TEST)/%.c tmpdirs
	$(CC) -c -o $@ $< $(CFLAGS)

tmpdirs:
	mkdir -p $(BIN) $(OBJ) $(OBJTEST)
