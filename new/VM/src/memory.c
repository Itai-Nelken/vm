#include <stdlib.h>
#include "common.h"
#include "memory.h"

void *allocm(size_t size) {
    void *result = malloc(size);
    if(result == NULL) {
        LOGFATAL(1, "allocm(%lu): malloc() failed!", size);
    }
    return result;
}

void *reallocm(void *ptr, size_t size) {
    void *result = realloc(ptr, size);
    if(result == NULL) {
        LOGFATAL(1, "reallocm(%p, %lu): realloc() failed!", ptr, size);
    }
    return result;
}

void freem(void *ptr) {
    free(ptr);
}
