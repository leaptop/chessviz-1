#include "board.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct log {
    char line[16];
    struct log *next;
} log_t;

log_t *log_head;
log_t *log_curr;

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

void ExitProgram(char *msg,int code) {
    printf("%s\n",msg);
    exit(code);
}

void AddLog(char *msg) {
    log_t *log_next;
    strcpy(log_curr->line,msg);
    log_next = malloc(sizeof(log_t));
    log_curr->next = log_next;
    log_curr = log_curr->next;
}

void PrintLog() {
    int i = 1;
    log_t *log_tmp = log_head;
    while (log_tmp->next != NULL) {
        printf("%d. %s\n", i, log_tmp->line);
        log_tmp = log_tmp->next;
        i++;
    }
    printf("%d. ",i);
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

void MakeMove(char *move, int m1, int pawn) {
    int l1 = (int)(move[m1+1-pawn] - 'a');
    int l2 = (int)(move[m1+4-pawn] - 'a');
    int d1 = (int)(move[m1+2-pawn] - '1');
    int d2 = (int)(move[m1+5-pawn] - '1');
    if (CheckSyntax(move,m1,pawn) && ((pawn && (board[l1][d1]=='P' || board[l1][d1]=='p')) ||
            (board[l1][d1]==move[m1]||board[l1][d1]==move[m1]+32)) && board[l2][d2]==' ') {
        board[l2][d2] = board[l1][d1];
        board[l1][d1] = ' ';
    } else {
        ExitProgram("Wrong Input!",2);
    }
}

void MakeKill(char *move, int m1, int pawn) {
    int l1 = (int)(move[m1+1-pawn] - 'a');
    int l2 = (int)(move[m1+4-pawn] - 'a');
    int d1 = (int)(move[m1+2-pawn] - '1');
    int d2 = (int)(move[m1+5-pawn] - '1');
    if (CheckSyntax(move,m1,pawn) && ((pawn && (board[l1][d1]=='P' || board[l1][d1]=='p')) ||
            (board[l1][d1]==move[m1]||board[l1][d1]==move[m1]+32)) && board[l2][d2]!=' ') {
        board[l2][d2] = board[l1][d1];
        board[l1][d1] = ' ';
    } else {
        ExitProgram("Wrong Input!",4);
    }
}

void MakeTurn() {
    int i,sp;
    char turn[16];
    while (GetLine(turn, sizeof(turn))) {}
    for (i = 0; i < strlen(turn); i++){
        if (turn[i] == ' ' || turn[i] == '#') {
            sp = i;
            break;
        }
    }
    AddLog(turn);
    for (i = 0; i < strlen(turn); i++){
        if (turn[i] == '-') {
            if (i < sp) {
                MakeMove(turn, 0, (i == 2));
            } else {
                MakeMove(turn, sp+1, (i == sp+3));
            }
        } else if (turn[i] == 'x') {
            if (i < sp) {
                MakeKill(turn, 0, (i == 2));
            } else {
                MakeKill(turn, sp+1, (i == sp+3));
            }
        } else if (turn[i]=='#') {
            system("clear");
            PrintBoard();
            PrintLog();
            ClearBoard();
            ExitProgram("",0);
        }
    }
}

void InitLog() {
    log_head = malloc(sizeof(log_t));
    log_curr = log_head;
}

int main() {
    InitLog();
    InitBoard();
    while(1) {
        system("clear");
        PrintBoard();
        PrintLog();
        MakeTurn();
    }
    ClearBoard();
    return 0;
}

