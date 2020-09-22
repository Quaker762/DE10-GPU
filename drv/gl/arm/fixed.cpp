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

inline int16_t f32_to_fx16(float value)
{
    register int16_t ret;

    __asm__("vldr.32 s0, =%0" : : "r"(value) : "s0");
    __asm__("vcvt.S16.F32 s0, s0, 16");
    __asm__("vmov %0, s0" : "=r"(ret)::);
    return ret;
}

inline int32_t f32_to_fx32(float value)
{
    register int16_t ret;

    __asm__("vldr.32 s0, =%0" : : "r"(value) : "s0");
    __asm__("vcvt.S32.F32 s0, s0, 32");
    __asm__("vmov %0, s0" : "=r"(ret)::);
    return ret;
}

inline uint16_t f32_to_ufx16(float value)
{
    register int16_t ret;

    __asm__("vldr.32 s0, =%0" : : "r"(value) : "s0");
    __asm__("vcvt.U16.F32 s0, s0, 16");
    __asm__("vmov %0, s0" : "=r"(ret) : : "r1");
    return ret;
}

inline uint32_t f32_to_ufx32(float value)
{
    register int16_t ret;

    __asm__("vldr.32 s0, =%0" : : "r"(value) : "s0");
    __asm__("vcvt.U32.F32 s0, s0, 16");
    __asm__("vmov %0, s0" : "=r"(ret) : : "r1");
    return ret;
}