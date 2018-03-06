#ifndef CHESSVIZ_FUNCS_H_
#define CHESSVIZ_FUNCS_H_

#include <stdlib.h>

void InitLog();
void ClearLog();
void AddLog(char*);
void PrintLog();
int GetLine(char*, size_t);
void ExitProgram(char*, int);

#endif //CHESSVIZ_FUNCS_H_
