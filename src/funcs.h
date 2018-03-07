#ifndef CHESSVIZ_FUNCS_H_
#define CHESSVIZ_FUNCS_H_

#include <stdlib.h>
#include <stdio.h>

extern int file_mode;
extern FILE *infile,*outfile;

int OpenFile(char*);
void CloseFile();
void InitLog();
void ClearLog();
void AddLog(char*);
void PrintLog();
void GetLine(char*,size_t);
void ExitProgram(char*, int);

#endif //CHESSVIZ_FUNCS_H_
