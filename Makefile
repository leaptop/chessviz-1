CC = gcc
CFLAGS  = -Wall -Werror

.PHONY: clean

all: bin/chessviz

bin/chessviz: build/main.o build/board.o bin
	$(CC) $(CFLAGS) build/main.o build/board.o -o bin/chessviz

build/main.o: src/main.c src/board.h build
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o

build/board.o: src/board.c src/board.h build
	$(CC) $(CFLAGS) -c src/board.c -o build/board.o

build:
	mkdir build

bin:
	mkdir bin

clean:
	rm -rf build bin
