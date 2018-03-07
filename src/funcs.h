#ifndef CHESSVIZ_FUNCS_H_
#define CHESSVIZ_FUNCS_H_

#include <stdlib.h>

int OpenFile(char*);
void CloseFile();
void InitLog();
void ClearLog();
void AddLog(char*);
void PrintLog();
void GetLineFile(char*,size_t);
int GetLine(char*, size_t);
void ExitProgram(char*, int);

#endif //CHESSVIZ_FUNCS_H_
