/**
 *  This file is part of Rush3D.
 *  Copyright (c) 2020 Jack Allan, Matthew Atkin and Jesse Buhagiar
 *
 *  Rush3D is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Rush3D is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Rush3D.  If not, see <https://www.gnu.org/licenses/>.
 *
 *  Author: Jesse Buhagiar
 *  Date: 23/9/2020
 */
#include "fixed.h"

int32_t f32_to_fx32(float value)
{
    int32_t ret = 0;

    __asm__("vmov.32 s0, %0"
            :            // Output Operands
            : "r"(value) // Input Operands
            : "s0");     // Clobbered Registers
    __asm__("vcvt.S32.F32 s0, s0, 20");
    __asm__("vmov %0, s0"
            : "=r"(ret) // Output Operands
            :           // Input Operands
            :);         // Clobbered Registers

    return ret;
}

uint32_t f32_to_ufx32(float value)
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
