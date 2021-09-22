TODO
====

- [x] scanner/lexical scanner/lexical analyzer/lexer.
- [ ] Parser.
    - [x] Change register syntax to `r<reg>`.
    - [x] Change register exists test to parser from scanner.
    - [x] parser accepts `set add 5`, `set 4 5`, `mov set get` and `mov 5 6` but it shouldn't.
- [ ] Codegen.

binary format
-------------
**SYMOBLS:**<br>
`START`: 0xFFFF (-1)<br>
`END`: 0xFEFF (-2)

**INSTRUCTION FORMAT:**<br>
| instruction | operand 1 | operand 2 |
| :---------: | :-------: | :-------: |
|   2 bytes   |  4 bytes  |  4 bytes  |

Internally the opcode + operands is a `struct`:
```c
struct operation {
    short instruction;
    int arg1, arg2;
};
```

C program to write the following program:
```asm
push 5
push 6
add
peek
```
```c
#include <stdio.h>

#define S_START -1
#define S_END -2

enum {
    PUSH,
    POP,
    PEEK,
    ADD
}; // all the instructions we need, of course there are more.

struct operation {
    short instruction;
    int arg1, arg2;
};

int main(void) {
    struct operation op;
    FILE *out=fopen("program.vm", "w");
    if(!out) return 1; // return 1 if failed to open file.

    op.instruction=S_START;
    op.arg1=0;
    op.arg2=0;
    fwrite(&op, sizeof(op), 1, out);

    op.instruction=PUSH;
    op.arg1=5;
    fwrite(&op, sizeof(op), 1, out);

    op.arg1=6;
    fwrite(&op, sizeof(op), 1, out);
    op.arg1=0;

    op.instruction=ADD;
    fwrite(&op, sizeof(op), 1, out);

    op.instruction=PEEK;
    fwrite(&op, sizeof(op), 1, out);

    op.instruction=S_END;
    fwrite(&op, sizeof(op), 1, out);

    fclose(out);
    return 0;
}
```
