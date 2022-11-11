#ifndef COMMON_H
#define COMMON_H

#include <assert.h>

#define VERIFY(x) assert(x)

#define UNREACHABLE() assert(0 && "internal error: unreachable state!")

#endif // COMMON_H
