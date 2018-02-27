CC = gcc
CFLAGS  = -Wall -Werror

.PHONY: clean

all: bin/chessviz

bin/chessviz: build/main.o
	$(CC) $(CFLAGS) build/main.o -o bin/chessviz

build/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o

clean:
	$(RM) build/* bin/* src/*~
