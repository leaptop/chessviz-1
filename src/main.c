#include "board.h"
#include "funcs.h"

#include <stdlib.h>
#include <stdio.h>

int main() {
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
    printf("\n");
    return 0;
}

