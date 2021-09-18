#include <stdio.h>
#include "common.h"
#include "emu.h"

int program[] = {
	SET, A, 5,
	SET, B, 6,
	GET, A,
	GET, B,
	ADD,
	PEEK,
	PUSH, 9,
	ADD,
	PEEK,
	POP,
	END
}; // output: 11\n20

int main(void) {
	//run(program);
	run_from_file("test.vm");
	return 0;
}
