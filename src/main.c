#include "board.h"
#include "funcs.h"
#include "board_print_html.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void ArgsHandler(char **argv, int n) {
    int i;
    for (i=1; i<n; i++) {
        if (!strcmp(argv[i],"--html")) html_mode = 1;
        if (!strcmp(argv[i],"--file") && i<n-1) {
            if (!OpenFile(argv[i+1])) {
                ExitProgram("Couldn't open the file.",3);
            } else {
                file_mode = 1;
            }
        }
    }
}

int main(int argc, char **argv) {
    ArgsHandler(argv,argc);
    InitLog();
    InitBoard();
    if (html_mode) PrintHtmlHead();
    while (MakeTurn()) {
        if (!html_mode) PrintLog();
        PrintBoard();
        fprintf(outfile,"\n\n");
    }
    if (!html_mode) PrintLog();
    PrintBoard();
    if (html_mode) PrintHtmlBottom();
    ClearLog();
    ClearBoard();
    if (file_mode) CloseFile();
    if (html_mode) printf("Output saved to './output.html'\n");
        else printf("Output saved to './output.txt'\n");
    return 0;
}

