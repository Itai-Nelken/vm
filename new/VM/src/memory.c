#include <stdlib.h>
#include "common.h"
#include "memory.h"

void *allocm(size_t size) {
    void *result = malloc(size);
    if(result == NULL) {
        LOGFATAL(1, "malloc(%lu) failed!", size);
    }
    return result;
}

void *reallocm(void *ptr, size_t size) {
    void *result = realloc(ptr, size);
    if(result == NULL) {
        LOGFATAL(1, "realloc(%p, %lu) failed!", ptr, size);
    }
    return result;
}

void freem(void *ptr) {
    free(ptr);
}
