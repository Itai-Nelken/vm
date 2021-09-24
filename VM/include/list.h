#ifndef LIST_H
#define LIST_H
#include "common.h"

typedef struct prog_node {
    struct operation op;
    struct prog_node *next;
} programNode;

void listInsert(programNode **head, struct operation *op);
void listDestroy(programNode *head);
void listDump(programNode *head);


#endif // LIST_H
