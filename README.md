# vm

## Instruction table
| NAME | OPCODE | USAGE | DESCRIPTION |
| :---: | :---: | :---: | :---: |
| PUSH | 0 | `PUSH <value>` | push <value> to the stack. |
| POP | 1 | `POP` | pop the last value from the stack. |
| PEEK | 2 | `PEEK` | print the stack head. |
| ADD | 3 | `ADD` | pop 2 values from the stack, add them, and push the result. |
| SUB | 4 | `SUB` | pop 2 values from the stack, substract the LAST PUSHED from the FIRST PUSHED, and push the result. (`PUSH 5, PUSH 2, SUB` == 5 - 2) |
| MUL | 5 | `MUL` | pop 2 values from the stack, multiply them, and push the result. |
| DIV | 6 | `DIV` | pop 2 values from the stack, divide the FIRST PUSHED by the LAST PUSHED, and push the result. (`PUSH 10, PUSH 2, DIV` == 10 / 2) |
| SET | 7 | `SET <register> <value>` | set `<register>` to `<value>`. |
| GET | 8 | `GET <register>` | push the value of `<register>`. |
| JMP | 9 | `JMP <instruction index>` | jump to the instruction `<instruction index>`. see "`JMP` example" bellow. |
| NOP | a | `NOP` | do nothing. |
| HLT | b | `HLT` | end the program. |
| END | c | `END` | has to be at the end of every program. |

## Registers
| NAME | DESCRIPTION |
| :--: | :---------: |
| `A` | General purpose register. |
| `B` | General purpose register. |
| `C` | General purpose register. |
| `D` | General purpose register. |
| `E` | General purpose register. |
| `F` | General purpose register. |
| `PC` | Program Counter/Instruction Pointer (Points to the instruction to execute in the program). |
| `SP` | Stack Pointer (points to the stack head) |

### `JMP` example
The following program will add 5 and 6, print the result, and jump back to the first instruction (`PUSH 5`, index 0 so `JMP 0`).
So basically an infinite loop that will add 5 and 6 and print the result.
```asm
PUSH 5
PUSH 6
ADD
PEEK
POP
JMP 0
END
```
### 5+6
```asm
PUSH 5
PUSH 6
ADD
PEEK
POP
END
```
### 5+6 with registers
```asm
SET A 5
SET B 6
GET A
GET B
ADD
PEEK
POP
END
```
