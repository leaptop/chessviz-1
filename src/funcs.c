#include "funcs.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct log {
    char line[16];
    struct log *next;
} log_t;

log_t *log_head;
log_t *log_curr;

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
        printf("%d. %s\n", i, log_tmp->line);
        log_tmp = log_tmp->next;
        i++;
    }
}

int GetLine(char *buff, size_t sz) {
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

void ExitProgram(char *msg,int code) {
    printf("%s\n",msg);
    exit(code);
}
