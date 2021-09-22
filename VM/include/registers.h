#ifndef REGISTERS_H
#define REGISTERS_H

typedef struct registers_context {
    int A, B, C, D, E, F, SP, PC;
} REGScontext;

/******
 * Initialize a registers context.
 * 
 * @return A pointer to a heap allocated registers context. you can free it with registersDestroy();
 ******/
REGScontext *registersInit();

/******
 * Destroy an initialized registers context.
 * 
 * @param c An initialized registers context to destroy.
 ******/
void registersDestroy(REGScontext *c);

/******
 * Set the value of a register to data.
 * 
 * @param c An initialized registers context.
 * @param r The register to set.
 * @param data The value to set the register to.
 * 
 * @return 0: success, -1: failure.
 ******/
int registersSet(REGScontext *c, Register r, int data);

/******
 * Get the value in a register.
 * 
 * @param c An initialized registers context.
 * @param r The register.
 * 
 * @return The value in th register or -1 on failure (-1 might be returned on success if it's the value that was in the register).
 ******/
int registersGet(REGScontext *c, Register r);

#endif // REGISTERS_H
