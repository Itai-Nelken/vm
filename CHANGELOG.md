# VM changelog
**DD/MM/YY**

### 18/09/2021
- Initial idea and VM.
- git repo created.
- created README.md and CHAGNELOG.md (this changelog).
- Wrote dissasembler.
- Added command line arguments.

### 19-20/09/2021
- Wrote a very simple assembler.

### 21/09/2021
- Changed binary format to real binary.
- Wrote a new disassembler.
- Started writing a proper assembler.

### 22/09/2021
- Finish the new assembler.
- Start work on the actual VM.

### 23/09/2021
- Improve disassembler: handle failed to open file error and print `R<reg>` instead of `<reg>`.

### 24/09/2021
- VM: implement loading the binary into a linked list (bad idea as I can't iterate over it with the program counter easily).
- Update documentation.

### 27/09/2021
- Assembler: fix incorrect line being printed in syntax error in some cases.
- Update documentation.

### 01/10/2021
- Finished the VM!
- Cleanup a bit
- Fix JMP commands.
- Add example program that prints the multiplication table.
- Added base Makefile.

### 02/10/2021
- Fix typo in VM/src/vm.c

### 03/10/2021
- Fix VIM syntax highlighting
- Clean up syntax/ folder
- Make the disassembler (`vas -d <vm binary>`) print the instruction number in the program before each instruction.

### 08/10/2021
- Add example that prints the first 40 numbers in the fibonacci sequence.

### 15-16/10/2021
- Rewrite the assembler, nothing substantial. just making the code more readable and loading the program into a dynamic array before writing it.

### 24/10/2021
- fix compilation on MacOS.

### 15/11/2021
- Add make VM print debug info (stack and register dump, current instruction) and exit when a runtime error is encountered.

<hr>
