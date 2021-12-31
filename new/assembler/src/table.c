#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "common.h"
#include "../include/memory.h"
#include "table.h"

#define TABLE_INITIAL_SIZE 8

void tablePrintData(Data d) {
    printf("%d", d);
}

Table *newTable() {
	Table *t = allocm(sizeof(*t));
	t->size = TABLE_INITIAL_SIZE;
	t->used = 0;
    t->colisions = 0;
	t->data = allocm(sizeof(Item*) * TABLE_INITIAL_SIZE);
	for(size_t i = 0; i < TABLE_INITIAL_SIZE; ++i) {
		t->data[i] = NULL;
	}
	return t;
}

void freeTable(Table *t) {
    for(size_t i = 0; i < t->size; ++i) {
        if(t->data[i] != NULL) {
            if(t->data[i]->next != NULL) {
                Item *current = t->data[i], *previous = NULL;
                while(current != NULL) {
                    previous = current;

                    freem(current->key);
                    freem(current);

                    current = previous->next;
                }
            } else {
                freem(t->data[i]->key);
                freem(t->data[i]);
            }
        }
    }
	freem(t->data);
	freem(t);
	t = NULL;
}

/*
unsigned hash(const char *key) {
        unsigned hash = 0;
        for(size_t i = 0; i < strlen(key); ++i) {
                hash += key[i];
                hash *= key[i];
        }
        return hash;
}
*/

// FNV-la hashing algorithm
static unsigned hash(const char *key) {
    unsigned hash = 2166136261u;
    for(int i = 0; i < (int)strlen(key); ++i) {
        hash ^= (uint8_t)key[i];
        hash *= 16777619;
    }
    return hash;
}

static void grow(Table *t) {
        Item *old = allocm(sizeof(Item) * (t->used + t->colisions));
        int idx = 0;
        for(size_t i = 0; i < t->size; ++i) {
            if(t->data[i] == NULL)
                continue;
            Item *current = t->data[i], *tmp = NULL;
            while(current != NULL) {
                old[idx].key = allocm(sizeof(char) * strlen(current->key));
                strcpy(old[idx].key, current->key);
                old[idx++].value = current->value;
                tmp = current->next;
                tableDelete(t, current->key);
                current = tmp;
            }
        }
        t->size *= 2;
        t->data = reallocm(t->data, sizeof(Item*) * t->size);
        for(int i = 0; i < idx; ++i) {
            tableInsert(t, old[i].key, old[i].value);
            freem(old[i].key);
        }

        freem(old);
}

void tableInsert(Table *t, const char *key, Data value) {
	if(t->used == t->size) { // not t.size-1 because Table::used is one-indexed
		printf("table is full!\n");
        grow(t);
		return;
	}
    unsigned index = hash(key) % t->size;
    Item *n = allocm(sizeof(*n));
    n->key = allocm(sizeof(char) * strlen(key));
    strcpy(n->key, key);
    n->value = value;
    n->next = t->data[index];
    if(t->data[index] == NULL) {
        t->used++;
    } else {
        t->colisions++;
    }
    t->data[index] = n;
}

void tableDelete(Table *t, const char *key) {
    unsigned index = hash(key) % t->size;
    Item *current = t->data[index], *previous = NULL;
    while(current != NULL && strcmp(current->key, key)) {
        previous = current;
        current = current->next;
    }
    if(current == NULL) {
        printf("No value for key '%s'!\n", key);
        return;
    }
    if(previous == NULL) {
        // we are at the head of the linked list
        t->data[index] = current->next;
    } else {
        previous->next = current->next;
    }
    freem(current->key);
    freem(current);
    if(t->data[index] == NULL) {
        t->used--;
    } else {
        t->colisions--;
    }
}

int tableLookup(Table *t, const char *key) {
    unsigned index = hash(key) % t->size;
    Item *current = t->data[index];
    while(current != NULL && strcmp(current->key, key)) {
        current = current->next;
    }
    if(current != NULL) {
        return current->value;
    }
    return -1; // not the best value as it is a valid value.
}

void tableDump(Table *t) {
    int emptyCount = 0;
    printf("== dump ==\n\x1b[1msize: %lu\nused: %lu\ncolisions: %lu\x1b[0m\n", t->size, t->used, t->colisions);
    if(t->used == 0 && t->colisions == 0) {
	    printf("[EMPTY]\n");
	    return;
	}
	for(size_t i = 0; i < t->size; ++i) {
        if(t->data[i] != NULL) {
            if(emptyCount > 0) {
                printf("<%d empty>\n", emptyCount);
                emptyCount = 0;
            }
            printf("[%lu]: (%s, ", i, t->data[i]->key);
            tablePrintData(t->data[i]->value);
            printf(")\n");
            if(t->data[i]->next != NULL) {
                Item *current = t->data[i]->next;
                while(current != NULL) {
                    printf("\t- (%s, ", current->key);
                    tablePrintData(current->value);
                    printf(")\n");
                    current = current->next;
                }
            }
        } else {
            emptyCount++;
        }
    }
    if(emptyCount > 0) {
        printf("<%d empty>\n", emptyCount);
    }
}
