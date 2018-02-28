#include "board.h"

#include <stdlib.h>
#include <stdio.h>

const int kBoardWidth = 8;
const int kBoardHeight = 8;

char** board;

void InitBoard(){
    int i,j;
    board = (char**)malloc(kBoardHeight * sizeof(char*));
    for (i = 0; i < kBoardHeight; i++) {
        board[i] = (char*)malloc(kBoardWidth * sizeof(char));
        for (j = 0; j < kBoardWidth; j++) {
            board[i][j] = ' ';
        }
    }
    FillBoard();
}

void FillBoard(){
    int i;
    for (i = 0; i < kBoardWidth; i++){
        board[i][1] = 'P';
        board[i][6] = 'p';
    }
    board[0][0] = 'R';
    board[1][0] = 'N';
    board[2][0] = 'B';
    board[3][0] = 'K';
    board[4][0] = 'Q';
    board[5][0] = 'B';
    board[6][0] = 'N';
    board[7][0] = 'R';
    board[0][7] = 'r';
    board[1][7] = 'n';
    board[2][7] = 'b';
    board[3][7] = 'k';
    board[4][7] = 'q';
    board[5][7] = 'b';
    board[6][7] = 'n';
    board[7][7] = 'r';
}

void ClearBoard(){
    int i;
    for (i = 0; i < kBoardHeight; i++) {
        free(board[i]);
    }
    free(board);
    board = NULL;
}

void PrintBoard(){
    int i,j;
    for (i = -1; i < kBoardHeight; i++) {
        for (j = -1; j < kBoardWidth; j++) {
            if (j < 0 && i < 0) {
                printf("   ");
            } else  if (j < 0) {
                printf("%d |",i + 1);
            } else if (i < 0) {
                printf(" %c  ",'A' + j);
            } else {
                printf(" %c |",board[j][i]);
            }
        }
        printf("\n  ");
        printf("---------------------------------\n");
    }
}
