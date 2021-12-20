#include <stdio.h>
#include "common.h"
#include "disassembler.h"

int main(void) {
	printf("%s\n", instr2str(0x16));
	return 0;
}

