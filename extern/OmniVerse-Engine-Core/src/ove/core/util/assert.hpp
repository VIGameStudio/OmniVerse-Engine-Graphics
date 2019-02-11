#pragma once

#define DEBUG_ASSERT 1

#if DEBUG_ASSERT
#include <signal.h>
#define ASSERT(expr) \
    if (!(expr))     \
        raise(SIGTRAP);
#else
#define ASSERT(expr)
#endif
