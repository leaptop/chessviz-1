#ifndef CHESSVIZ_BOARD_H_
#define CHESSVIZ_BOARD_H_

char** board;

void InitBoard();
void FillBoard();
void ClearBoard();
void PrintBoard(int);
int InBounds(char, char, char);
int CheckSyntax(char*, int, int);
int MakeMove(char*, int, int);
int MakeKill(char*, int, int);
int Castling(int, int);
int MakeTurn();

#endif //CHESSVIZ_BOARD_H_
