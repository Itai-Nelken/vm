#include <stdio.h>
#include "Vm.h"

#include "OpCodes.h"
int main(void) {
    Vm vm;
    vmInit(&vm);

    vmExecute(&vm);
    printf("stack top: %d\n", vm.stack[vm.regs.sp - 1]);

    vmFree(&vm);
    return 0;
}
