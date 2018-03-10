CC = gcc
CFLAGS  = -Wall -Werror -std=gnu11

.PHONY: clean

default: bin/chessviz

test: bin/chessviz-test
	bin/chessviz-test

bin/chessviz: build/main.o build/board.o build/board_print_html.o build/funcs.o bin
	$(CC) $(CFLAGS) build/main.o build/board.o build/board_print_html.o build/funcs.o -o bin/chessviz

build/main.o: src/main.c src/board.h src/board_print_html.h src/funcs.h build
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o

build/board.o: src/board.c src/board.h src/board_print_html.h src/funcs.h build
	$(CC) $(CFLAGS) -c src/board.c -o build/board.o

build/board_print_html.o: src/board_print_html.c src/board_print_html.h src/board.h src/funcs.h build
	$(CC) $(CFLAGS) -c src/board_print_html.c -o build/board_print_html.o

build/funcs.o: src/funcs.c src/funcs.h build
	$(CC) $(CFLAGS) -c src/funcs.c -o build/funcs.o

bin/chessviz-test: build/main_test.o build/board.o build/funcs.o src bin
	$(CC) $(CFLAGS) build/main_test.o build/board.o build/board_print_html.o build/funcs.o -o bin/chessviz-test

build/main_test.o: test/main.c thirdparty/ctest.h src/board.h src/funcs.h build
	$(CC) $(CFLAGS) -I thirdparty -I src -c test/main.c -o build/main_test.o

build:
	mkdir build

bin:
	mkdir bin

clean:
	rm -rf build bin
