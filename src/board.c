#include "board.h"

#include "funcs.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char **board;

void InitBoard(){
    int i,j;
    board = (char**)malloc(8 * sizeof(char*));
    for (i = 0; i < 8; i++) {
        board[i] = (char*)malloc(8 * sizeof(char));
        for (j = 0; j < 8; j++) {
            board[i][j] = ' ';
        }
    }
    FillBoard();
}

void FillBoard(){
    int i;
    for (i = 0; i < 8; i++){
        board[i][1] = 'P';
        board[i][6] = 'p';
    }
    board[0][0] = 'R';
    board[1][0] = 'N';
    board[2][0] = 'B';
    board[3][0] = 'Q';
    board[4][0] = 'K';
    board[5][0] = 'B';
    board[6][0] = 'N';
    board[7][0] = 'R';
    board[0][7] = 'r';
    board[1][7] = 'n';
    board[2][7] = 'b';
    board[3][7] = 'q';
    board[4][7] = 'k';
    board[5][7] = 'b';
    board[6][7] = 'n';
    board[7][7] = 'r';
}

void ClearBoard(){
    int i;
    for (i = 0; i < 8; i++) {
        free(board[i]);
    }
    free(board);
    board = NULL;
}

void PrintBoard(){
    int i,j;
    for (i = 7; i >= -1; i--) {
        fprintf(outfile,"  ---------------------------------\n");
        for (j = 8; j > -1; j--) {
            if (j > 7 && i < 0) {
                fprintf(outfile,"   ");
            } else  if (j > 7) {
                fprintf(outfile,"%d |",i + 1);
            } else if (i < 0) {
                fprintf(outfile," %c  ",'H' - j);
            } else {
                fprintf(outfile," %c |",board[7-j][i]);
            }
        }
        fprintf(outfile,"\n");
    }
}

int InBounds(char ch, char b1, char b2) {
    return (ch >= b1 && ch <= b2);
}

int CheckSyntax(char *str,int b,int p) {
    return ((InBounds(str[b],'A','Z') || p) &&
            InBounds(str[b+1-p],'a','h') &&
            InBounds(str[b+2-p],'1','8') &&
            (str[b+3-p] == '-' || str[b+3-p] == 'x') &&
            InBounds(str[b+4-p],'a','h') &&
            InBounds(str[b+5-p],'1','8'));
}

int MakeMove(char *move, int m1, int pawn) {
    int l1 = (int)(move[m1+1-pawn] - 'a');
    int l2 = (int)(move[m1+4-pawn] - 'a');
    int d1 = (int)(move[m1+2-pawn] - '1');
    int d2 = (int)(move[m1+5-pawn] - '1');
    if (CheckSyntax(move,m1,pawn) && ((pawn && (board[l1][d1]=='P' || board[l1][d1]=='p')) ||
            (board[l1][d1]==move[m1]||board[l1][d1]==move[m1]+32)) && board[l2][d2]==' ') {
        board[l2][d2] = board[l1][d1];
        board[l1][d1] = ' ';
    } else {
        return 0;
    }
    return 1;
}

int MakeKill(char *move, int m1, int pawn) {
    int l1 = (int)(move[m1+1-pawn] - 'a');
    int l2 = (int)(move[m1+4-pawn] - 'a');
    int d1 = (int)(move[m1+2-pawn] - '1');
    int d2 = (int)(move[m1+5-pawn] - '1');
    if (CheckSyntax(move,m1,pawn) && ((pawn && (board[l1][d1]=='P' || board[l1][d1]=='p')) ||
            (board[l1][d1]==move[m1]||board[l1][d1]==move[m1]+32)) && board[l2][d2]!=' ') {
        board[l2][d2] = board[l1][d1];
        board[l1][d1] = ' ';
    } else {
        return 0;
    }
    return 1;
}

int Castling(int w,int l) {
    if (l) {
        if (board['b'-'a'][7-7*w]==' ' && board['c'-'a'][7-7*w]==' ' && board['d'-'a'][7-7*w]==' ' &&
                board['a'-'a'][7-7*w]=='r'-(char)(32*w) && board['e'-'a'][7-7*w]=='k'-(char)(32*w)) {
            board['c'-'a'][7-7*w]=board['e'-'a'][7-7*w];
            board['d'-'a'][7-7*w]=board['a'-'a'][7-7*w];
            board['e'-'a'][7-7*w]=' ';
            board['a'-'a'][7-7*w]=' ';
        } else {
            return 0;
        }
    } else {
        if (board['f'-'a'][7-7*w]==' ' && board['g'-'a'][7-7*w]==' ' &&
                board['h'-'a'][7-7*w]=='r'-(char)(32*w) && board['e'-'a'][7-7*w]=='k'-(char)(32*w)) {
            board['g'-'a'][7-7*w]=board['e'-'a'][7-7*w];
            board['f'-'a'][7-7*w]=board['h'-'a'][7-7*w];
            board['e'-'a'][7-7*w]=' ';
            board['h'-'a'][7-7*w]=' ';
        } else {
            return 0;
        }
    }
    return 1;
}

int MakeTurn() {
    int i,sp;
    char turn[16];
    int correct_input = 0;
    GetLine(turn, sizeof(turn));
    sp=-1;
    for (i = 0; i < strlen(turn); i++){
        if (turn[i] == ' ' || turn[i] == '#') {
            sp = i;
            break;
        }
    }
    if (sp<0) {
        AddLog("Wrong input.");
        return 1;
    }
    for (i = 0; i < strlen(turn); i++){
        if (turn[i] == '-') {
            if (i < sp) {
                if (turn[0]=='0' && turn[2]=='0') {
                    correct_input = Castling(1,(turn[3]=='-' && turn[4]=='0'));
                    i+=3*(turn[3]=='-' && turn[4]=='0');
                } else {
                    correct_input = MakeMove(turn, 0, (i == 2));
                }
            } else {
                if (turn[sp+1]=='0' && turn[sp+3]=='0') {
                    correct_input = Castling(0,(turn[sp+4]=='-' && turn[sp+5]=='0'));
                    i+=3*(turn[sp+4]=='-' && turn[sp+5]=='0');
                } else {
                    correct_input = MakeMove(turn, sp+1, (i == sp+3));
                }
            }
        } else if (turn[i] == 'x') {
            if (i < sp) {
                correct_input = MakeKill(turn, 0, (i == 2));
            } else {
                correct_input = MakeKill(turn, sp+1, (i == sp+3));
            }
        } else if (turn[i]=='#') {
            AddLog(turn);
            return 0;
        }
    }
    if (correct_input) AddLog(turn); else AddLog("Wrong input.");
    return 1;
}
