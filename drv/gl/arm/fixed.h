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
 *  Floating to fixed point assembly stub. This is done via the `vcvt` instruction:
 *  https://developer.arm.com/documentation/dui0489/i/neon-and-vfp-programming/vcvt--between-floating-point-and-fixed-point-
 *
 *  Author: Jesse Buhagiar
 *  Date: 23/9/2020
 */
#pragma once

#include <cstdint>

extern "C" {
int32_t f32_to_fx32(float value);
uint32_t f32_to_ufx32(float value);
}
