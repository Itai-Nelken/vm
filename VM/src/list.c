#include <stdio.h>
#include <stdlib.h>
#include "list.h"

static void opcpy(struct operation *dest, struct operation *src) {
    dest->instruction=src->instruction;
    dest->arg1=src->arg1;
    dest->arg2=src->arg2;
}

void listInsert(programNode **head, struct operation *op) {
    programNode *current=NULL, *new;
    if(*head==NULL) {
        new=malloc(sizeof(programNode));
        opcpy(&(new->op), op);
        new->next=NULL;
        *head=new;
    } else {
        current=*head;
        while(current->next!=NULL) {
            current=current->next;
        }
        new=malloc(sizeof(programNode));
        opcpy(&(new->op), op);
        new->next=NULL;
        current->next=new;
    }
}

void listDestroy(programNode *head) {
    programNode *current;
    do {
        current=head;
        head=head->next;
        free(current);
    } while(head!=NULL);
}

void listDump(programNode *head) {
    while(head!=NULL) {
        printf("%d %d %d\n", head->op.instruction, head->op.arg1, head->op.arg2);
        head=head->next;
    }
}
