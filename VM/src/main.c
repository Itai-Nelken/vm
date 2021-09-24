#include <stdio.h>
#include "common.h"
#include "vm.h"
#include "list.h"

int main(void) {
    VM *vm=vmInit();
    loadBinary("in.vm", &(vm->progHead));
    listDump(vm->progHead);
    vmDestroy(vm);
    return 0;
}

