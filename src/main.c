#include "board.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void ExitProgram(char *msg,int code) {
    printf("%s\n",msg);
    exit(code);
}

static int GetLine(char *buff, size_t sz) {
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

void MakeMove(char *move, int m1, int m2, int pawn) {
    int l1 = (int)(move[m1+1-pawn] - 'a');
    int l2 = (int)(move[m2-2] - 'a');
    int d1 = (int)(move[m1+2-pawn] - '1');
    int d2 = (int)(move[m2-1] - '1');
    if (((pawn && (board[l1][d1]=='P' || board[l1][d1]=='p')) || (board[l1][d1]==move[m1])) && board[l2][d2]==' ') {
        board[l2][d2] = board[l1][d1];
        board[l1][d1] = ' ';
    } else {
        ExitProgram("Wrong Input!",1);
    }
}

void MakeKill(char *move, int m1, int m2, int pawn) {
    int l1 = (int)(move[m1+1-pawn] - 'a');
    int l2 = (int)(move[m2-2] - 'a');
    int d1 = (int)(move[m1+2-pawn] - '1');
    int d2 = (int)(move[m2-1] - '1');
    if (((pawn && (board[l1][d1]=='P' || board[l1][d1]=='p')) || (board[l1][d1]==move[m1])) && board[l2][d2]!=' ') {
        board[l2][d2] = board[l1][d1];
        board[l1][d1] = ' ';
    } else {
        ExitProgram("Wrong Input!",1);
    }
}

void MakeTurn() {
    int i,sp;
    char turn[64];
    while (GetLine(turn, sizeof(turn))) {}
    for (i = 0; i < strlen(turn); i++){
        if (turn[i] == ' ') {
            sp = i;
            break;
        }
    }
    for (i = 0; i < strlen(turn); i++){
        if (turn[i] == '-') {
            if (i < sp) {
                MakeMove(turn, 0, sp, (i == 2));
            } else {
                MakeMove(turn, sp+1, strlen(turn), (i == sp+3));
            }
        } else if (turn[i] == 'x') {
            if (i < sp) {
                MakeKill(turn, 0, sp, (i == 2));
            } else {
                MakeKill(turn, sp+1, strlen(turn), (i == sp+3));
            }
        }
    }
}

int main() {
    InitBoard();
    while(1) {
        system("clear");
        PrintBoard();
        MakeTurn();
    }
    ClearBoard();
    return 0;
}

