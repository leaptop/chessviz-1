#include "board.h"
#include "funcs.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    if (argc>1) {
        if (!OpenFile(argv[1])) {
            ExitProgram("Couldn't open the file.",3);
        } else {
            file_mode = 1;
        }
    } else {
        file_mode = 0;
    }
    InitLog();
    InitBoard();
    do {
        system("clear");
        PrintBoard();
        PrintLog();
    } while (MakeTurn());
    system("clear");
    PrintBoard();
    PrintLog();
    ClearLog();
    ClearBoard();
    if (file_mode) CloseFile();
    printf("\n");
    return 0;
}

