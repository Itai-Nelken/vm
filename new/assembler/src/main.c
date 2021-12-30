#include <stdio.h>

#include "table.h"
int main(void) {
	Table *t = newTable(2);
	tableInsert(t, "Itai", 16);
	tableInsert(t, "Shahar", 13);
	tableInsert(t, "Netanel", 10);
	tableDump(t);
	freeTable(t);
	//printf("Hello, World!\n");
	return 0;
}

