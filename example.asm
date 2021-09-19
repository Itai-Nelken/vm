; Simple program for vm to execute (5+5)*(5+5)
push 5
push 5
add
pset a

push 5
push 5
add ; the result is already in the stack, so there is no need to store it.

get a
mul

peek
pop ; pop isn't necessary here as this is the end of the program.
; you could put END here if you want, the assembler will do it if you don't.
