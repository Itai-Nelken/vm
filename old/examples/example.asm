; Simple program for vm to execute (5+5)*(5+5)
push 5
push 5
add
pset Ra

push 5
push 5
add ; the result is already in the stack, so there is no need to store it.

get Ra
mul

peek
pop ; pop isn't necessary here as this is the end of the program.
