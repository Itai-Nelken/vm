# vm
A Virtual Machine with a custom instruction set.

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


### Example: (5 + 2) * (2 + 5)
```asm
push 5
push 2
add
pset Ra

push 2
push 5
add
; The result is already on the stack, so no need to save it.

get Ra
mul

peek
pop ; pop isn't necessary here as its the end of the program
```
