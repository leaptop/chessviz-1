#include "funcs.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE *infile, *outfile;

int file_mode = 0;

typedef struct log {
    char line[16];
    struct log *next;
} log_t;

log_t *log_head;
log_t *log_curr;

int OpenFile(char *path) {
    infile = fopen(path,"r");
    outfile = fopen("./output.txt","w");
    return (infile != NULL && outfile != NULL);
}

void CloseFile() {
    fclose(infile);
    fclose(outfile);
}

void InitLog() {
    log_head = malloc(sizeof(log_t));
    if (log_head == NULL) ExitProgram("Failed to allocate memory.",1);
    log_curr = log_head;
}

void ClearLog() {
    log_curr = log_head;
    log_t *log_tmp = log_curr->next;
    while (log_tmp != NULL) {
        free(log_curr);
        log_curr = NULL;
        log_curr = log_tmp;
        log_tmp = log_tmp->next;
    }
}

void AddLog(char *msg) {
    log_t *log_next;
    strcpy(log_curr->line,msg);
    log_next = malloc(sizeof(log_t));
    if (log_next == NULL) ExitProgram("Failed to allocate memory.",2);
    log_curr->next = log_next;
    log_curr = log_curr->next;
}

void PrintLog() {
    int i = 1;
    log_t *log_tmp = log_head;
    while (log_tmp->next != NULL) {
        fprintf(outfile,"%d. %s\n", i, log_tmp->line);
        log_tmp = log_tmp->next;
        i++;
    }
}

void GetLineFile(char *str, size_t sz) {
    int i;
    fgets(str,sz,infile);
    for (i=0; i<strlen(str); i++) {
        if (str[i]=='\n') {
            str[i]='\0';
            break;
        }
    }
}

int GetLineStd(char *buff, size_t sz) {
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

void GetLine(char *str, size_t sz) {
    if (file_mode) {
        if (feof(infile)) {
            ExitProgram("Unexpected end of file.",3);
        } else {
            GetLineFile(str,sz);
        }
    } else {
        while (GetLineStd(str,sz)) {}
    }
}

void ExitProgram(char *msg,int code) {
    printf("%s\n",msg);
    exit(code);
}
