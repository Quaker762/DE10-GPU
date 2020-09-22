/**
 * Copyright (c) 2020, Jesse Buhagiar, Jack Allan and Matthew Atkin
 * All rights reserved.
 * Unauthorized copying or reproduction of this project and the files contained within
 * is strictly prohibited.
 *
 * Floating to fixed point assembly stub. This is done via the `vcvt` instruction:
 * https://developer.arm.com/documentation/dui0489/i/neon-and-vfp-programming/vcvt--between-floating-point-and-fixed-point-
 *
 * Author: Jesse Buhagiar
 * Date: 23/9/2020
 */
#pragma once

#include <cstdint>

int16_t f32_to_fx16(float value) __attribute__((always_inline));
int32_t f32_to_fx32(float value) __attribute__((always_inline));
uint16_t f32_to_ufx16(float value) __attribute__((always_inline));
uint32_t f32_to_ufx32(float value) __attribute__((always_inline));