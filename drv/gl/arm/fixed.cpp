/**
 * Copyright (c) 2020, Jesse Buhagiar, Jack Allan and Matthew Atkin
 * All rights reserved.
 * Unauthorized copying or reproduction of this project and the files contained within
 * is strictly prohibited.
 *
 * Author: Jesse Buhagiar
 * Date: 23/9/2020
 */
#include "fixed.h"

inline int32_t f32_to_fx32(float value)
{
    uint32_t ret = 0;

    __asm__("vmov.32 s0, %0"
            :            // Output Operands
            : "r"(value) // Input Operands
            : "s0");     // Clobbered Registers
    __asm__("vcvt.U32.F32 s0, s0, 20");
    __asm__("vmov %0, s0"
            : "=r"(ret) // Output Operands
            :           // Input Operands
            :);         // Clobbered Registers
}

inline uint32_t f32_to_ufx32(float value)
{
    uint32_t ret = 0;

    __asm__("vmov.32 s0, %0"
            :            // Output Operands
            : "r"(value) // Input Operands
            : "s0");     // Clobbered Registers
    __asm__("vcvt.U32.F32 s0, s0, 20");
    __asm__("vmov %0, s0"
            : "=r"(ret) // Output Operands
            :           // Input Operands
            :);         // Clobbered Registers

    return ret;
}