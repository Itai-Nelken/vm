# vm
A Virtual Machine with a custom instruction set.

## Building
### Assembler
```shell
cd assembler
make
```
executable is called `vas`.

### VM
```shell
cd VM
make
```
executable is called `vm`.

## TODO
- [x] Write the actual VM
   * [x] Use a dynamic array for storing the program (instead of the currently used linked list) that way we can use the `pc` register to actually point to the index of an instruction in the program.
- [ ] Create syntax highlighting for:
   * [x] VIM
   * [ ] VSCode
   * [ ] Sublime Text
- [ ] Fix register highlighting for vim syntax highlighting.

## Syntax highlighing
- **VIM**
    * files in syntax/VIM
    * instructions, number, and comments work fine.
    * registers stay white, I don't know how to fix that.
- **VSCode**
    * No official extension yet.
    * [This](https://marketplace.visualstudio.com/items?itemName=dan-c-underwood.arm) one for ARM assembly works fine for now.
- **Sublime Text**
    * No official extension yet.

## Instruction table
| NAME | OPCODE | USAGE | DESCRIPTION |
| :---: | :---: | :---: | :---: |
| PUSH | 0 | `PUSH <value>` | Push <value> to the stack. |
| POP | 1 | `POP` | Pop the stack head. |
| PEEK | 2 | `PEEK` | Print the stack head. |
| ADD | 3 | `ADD` | Pop 2 values from the stack, add them, and push the result. |
| SUB | 4 | `SUB` | Pop 2 values from the stack, substract the LAST PUSHED from the FIRST PUSHED, and push the result. (`PUSH 5, PUSH 2, SUB` == 5 - 2) |
| MUL | 5 | `MUL` | Pop 2 values from the stack, multiply them, and push the result. |
| DIV | 6 | `DIV` | Pop 2 values from the stack, divide the FIRST PUSHED by the LAST PUSHED, and push the result. (`PUSH 4, PUSH 2, DIV` == 4 / 2) |
| SET | 7 | `SET <register> <value>` | Set `<register>` to `<value>`. |
| PSET | 8 | `PSET <register>` | Pop the stack head and store the value in `<register>` |
| GET | 9 | `GET <register>` | Push the value of `<register>` to the stack. |
| JMP | 10 | `JMP <pc value>` | Jump to the instruction in `<pc value>`. |
| JEQ | 11 | `JEQ <pc value>` | Pop 2 values of the stack, compare them, and jump to `<pc value>` if they are equal. |
| JNE | 12 | `JNE <pc value>` | Pop 2 values of the stack, compare them, and jump to `<pc value>` if they are NOT equal. |
| JLT | 13 | `JLT <pc value>` | Pop 2 values of the stack, compare them, and jump to `<pc value>` if the FIRST value pushed to the stack is SMALLER than the second. |
| JGT | 14 | `JGT <pc value>` | Pop 2 values of the stack, compare them, and jump to `<pc value>` if the FIRST value pushed to the stack is LARGER than the second. |
| MOV | 15 | `MOV <reg1> <reg2>` | Move the value in `<reg2>` to `<reg1>`. |
| NOP | 16 | `NOP` | Do nothing. |
| HLT | 17 | `HLT` | End the program. |

## Registers
| NAME | number | DESCRIPTION |
| :--: | :----: | :---------: |
| `A` | 0 | General purpose register. |
| `B` | 1 | General purpose register. |
| `C` | 2 | General purpose register. |
| `D` | 3 | General purpose register. |
| `E` | 4 | General purpose register. |
| `F` | 5 | General purpose register. |
| `SP` | 6 | Stack Pointer (points to the stack head). |
| `PC` | 7 | Program Counter/Instruction Pointer (Points to the instruction to execute in the program). |

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

## Examples
**For other examples, see the `examples/` folder.**
### (5 + 2) * (2 + 5)
```asm
push 5
push 2
add ; add pops 2 values off the stack, adds them, and pushes the reuslt
pset Ra ; pset pops 1 value of the stack and stores it in the specified register

push 2
push 5
add
; The result is already on the stack, so no need to save it.

get Ra ; get pushes the vallue in the specified register and pushes it to the stack
mul

peek ; peek simply prints the stack head
pop ; pop isn't necessary here as its the end of the program
```
### count to 10
```asm
set Ra 0 ; set Ra to 0, this isn't neccesary as all registers are zeroed at VM start 

; increment Ra
get Ra
push 1
add
peek ; print the incremented value
pset Ra

; jump back to the 'increment Ra' part if the value in Ra doesn't equal 10
get Ra
push 5
jne 1
hlt ; isn't neccesary, prints 'program halted'
```
