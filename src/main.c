#include "board.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int GetLine (char *buff, size_t sz) {
    int ch, extra;
    if (fgets (buff, sz, stdin) == NULL) {
        return 1;
    }
    if (buff[strlen(buff)-1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? 1 : 0;
    }
    buff[strlen(buff)-1] = '\0';
    return 0;
}

int main() {
    InitBoard();
    PrintBoard();
    ClearBoard();
    return 0;
}

