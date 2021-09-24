#ifndef LIST_H
#define LIST_H
#include "common.h"

typedef struct prog_node {
    struct operation op;
    struct prog_node *next;
} programNode;

/******
 * Push a node to a linked list. if head is NULL, create a new list.
 * 
 * @param head A pointer to a programNode pointer that points to the first item in the list or is NULL if there is no list.
 * @param op A pointer to a struct operation that will be copied to the new node.
 ******/
void listInsert(programNode **head, struct operation *op);

/******
 * Destroy a list.
 * 
 * @param head The head of the list to destroy.
 ******/
void listDestroy(programNode *head);

/******
 * Print the contents of all the nodes in a list.
 * 
 * @param head The head of the list to dump.
 ******/
void listDump(programNode *head);


#endif // LIST_H
