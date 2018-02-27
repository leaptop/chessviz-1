CC = gcc
CFLAGS  = -Wall -Werror

.PHONY: clean

all: bin/chessviz

bin/chessviz: build/main.o build/board.o
	$(CC) $(CFLAGS) build/main.o build/board.o -o bin/chessviz

build/main.o: src/main.c src/board.h
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o

build/board.o: src/board.c src/board.h
	$(CC) $(CFLAGS) -c src/board.c -o build/board.o

clean:
	$(RM) build/* bin/* src/*~
