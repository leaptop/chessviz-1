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
    while (MakeTurn()) {
        PrintLog();
        PrintBoard();
        fprintf(outfile,"\n\n");
    }
    PrintLog();
    PrintBoard();
    ClearLog();
    ClearBoard();
    if (file_mode) CloseFile();
    printf("Output saved to './output.txt'\n");
    return 0;
}

