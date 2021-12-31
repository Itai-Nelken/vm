#ifndef TABLE_H
#define TABLE_H

#include <stddef.h> // for size_t
#include "common.h"

// change to change value type
// also change tablePrintData()
typedef int Data;

/***
 * Print the table data type correctly.
 * @param d The value to print.
 ***/
void tablePrintData(Data d);

typedef struct item {
    char *key;
    Data value;
    struct item *next;
} Item;

typedef struct table {
	Item **data;
	size_t size, used, colisions;
} Table;

/***
 * Create a new table with initial size 'TABLE_DEFAULT_SIZE'.
 * @return A pointer to a new initialized heap allocated table.
 ***/
Table *newTable();

/***
 * Free a table.
 * @param t A table to free. NULL will be assigned to it.
 ***/
void freeTable(Table *t);

/***
 * Insert a key-value pair into a table.
 * @param t An initialized table.
 * @param key The key (a string).
 * @param value The value (check what Data is typedef'd to).
 ***/
void tableInsert(Table *t, const char *key, Data value);

/***
 * Return the value of a key in a table.
 * @param t An initialized table.
 * @param key The key to lookup its value.
 * @return The value.
 ***/
Data tableLookup(Table *t, const char *key);

/***
 * Delete an entry in a table.
 * @param t An initialized table.
 * @param key The key to delete it and its value.
 ***/
void tableDelete(Table *t, const char *key);

/***
 * Print the contents of a table.
 * @param t An initialized table.
 ***/
void tableDump(Table *t);

#endif // TABLE_H
