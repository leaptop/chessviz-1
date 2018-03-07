#include "board.h"
#include "funcs.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    if (argc>1) {
        if (!OpenFile(argv[1])) {
            ExitProgram("Couldn't open the file.",3);
        }
    } else {
        ExitProgram("Please, specify input file.",4);
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
    CloseFile();
    printf("\n");
    return 0;
}

