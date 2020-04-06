/**
 * Debug Assertion macros to aid in debugging.
 *
 *
 * Copyright (c) 2020, Jesse Buhagiar, Jack Allan and Matthew Atkin
 * All rights reserved.
 * Unauthorized copying or reproduction of this project and the files contained within
 * is strictly prohibited.
 *
 * Author: Jesse Buhagiar
 * Date: 4/4/2020
 */
#pragma once

#include <cassert>

#ifdef DEBUG
    #define ASSERT(expr)       assert(expr)
    #define ASSERT_NOT_REACHED assert(false)
#else
    #define ASSERT(expr)
    #define ASSERT_NOT_REACHED
#endif