#pragma once

#include <cassert>

#ifdef DEBUG
    #define ASSERT(expr)       assert(expr)
    #define ASSERT_NOT_REACHED assert(false)
#else
    #define ASSERT(expr)
    #define ASSERT_NOT_REACHED
#endif