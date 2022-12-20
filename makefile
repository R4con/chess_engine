CC := g++
CFLAGS :=

VPATH := 

ROOT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
SRC_DIR := $(ROOT_DIR)/src/
OBJ_DIR := $(ROOT_DIR)/bin/


all: $(OBJ_DIR)main.o $(OBJ_DIR)board.o
	$(CC) $(CFLAGS) $^ -o chess_engine

$(OBJ_DIR)main.o: $(SRC_DIR)main.cpp
	$(CC) $(CFLAGS) -o $@ -c $^

$(OBJ_DIR)board.o: $(SRC_DIR)board.cpp
	$(CC) $(CFLAGS) -o $@ -c $^

clean:
	rm $(OBJ_DIR)*.o 