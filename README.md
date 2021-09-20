# vm
A Virtual Machine with a custom instruction set.

## Build
1. Clone this repository.
2. Open terminal in the repo's folder.
3. Run `make`
### Installation
In the repo's folder run `sudo make install`.
### Uninstallation
In the repo's folder run `sudo make uninstall`.

## VM usage
`$ vm [-h|-d <vm binary>] <vm binary>`<br>
**ARGUMENTS:**<br>
`-d|--disassemble` - Dissasemble a "vm binary", the output is printed to `stdout`.<br>
`-h|--help` - print help.

## Assembler (`vas`) usage
`$ vas <infile> [-o <output file>|-h]`<br>
**ARGUMENTS:**<br>
`-o <output file>` - Name of the output file. Default is `as.out.vm`.<br>
`-h` - Print help.

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
| JMP | a | `JMP <instruction index>` | Jump to the instruction `<instruction index>`. see "`JMP` example" bellow. |
| MOV | b | `MOV <reg1> <reg2>` | Move the value in `<reg2>` to `<reg1>`. |
| NOP | c | `NOP` | Do nothing. |
| HLT | d | `HLT` | End the program. |
| END | e | `END` | Has to be at the end of every program. |

## Registers
| NAME | number | DESCRIPTION |
| :--: | :----: | :---------: |
| `A` | 0 | General purpose register. |
| `B` | 1 | General purpose register. |
| `C` | 2 | General purpose register. |
| `D` | 3 | General purpose register. |
| `E` | 4 | General purpose register. |
| `F` | 5 | General purpose register. |
| `PC` | 6 |Program Counter/Instruction Pointer (Points to the instruction to execute in the program). |
| `SP` | 7 |Stack Pointer (points to the stack head) |

### `JMP` example
The following program will add 5 and 6, print the result, and jump back to the first instruction (`PUSH 5`, index 0 so `JMP 0`).
Basically an infinite loop that will add 5 and 6 and print the result.
```asm
PUSH 5
PUSH 6
ADD
PEEK
POP
JMP 0
END
```
### 5+6 example
```asm
PUSH 5
PUSH 6
ADD
PEEK
POP
END
```
### Register usage example with (5 + 2) * (2 + 5)
```asm
PUSH 5
PUSH 2
ADD
PSET A

PUSH 2
PUSH 5
ADD
; The result is already on the stack, so no need to save it.

GET A
MUL

PEEK
POP ; pop isn't necessary here as its the end of the program
; you could put END here, if you don't the assembler will do it.
```
