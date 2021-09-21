TODO
====

- [x] scanner/lexical scanner/lexical analyzer/lexer.
- [ ] Parser.
    - [ ] Change register syntax to `r<reg>`.
    - [ ] Change register exists test to parser from scanner.
    - [ ] parser accepts `set add 5`, `set 4 5`, `mov set get` and `mov 5 6` but it shouldn't.
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
