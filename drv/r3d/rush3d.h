/**
 * This file is part of Rush3D.
 * Copyright (c) 2020 Jack Allan, Matthew Atkin and Jesse Buhagiar
 *
 * Rush3D is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Rush3D is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Rush3D.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Author: Jesse Buhagiar
 * Date: 4/4/2020
 */
#pragma once

#include <cstdint>

#define VERTEX_A_REGISTER             0x00
#define VERTEX_B_REGISTER             0x08
#define VERTEX_C_REGISTER             0x10
#define COLOR_A_REGISTER              0x18
#define COLOR_B_REGISTER              0x20
#define COLOR_C_REGISTER              0x28
#define BACK_COLOR_REGISTER           0x30
#define CONTROL_STATUS_REGISTER_WRITE 0x38
#define CONTROL_STATUS_REGISTER_READ  0x40
#define WIN_SIZE_REGISTER             0x48

#define VERTEX_DATA_VALID 0x1
#define CLEAR_FRAMEBUFFER 0x10
#define SWAP_FRAMEBUFFER  0x100

typedef struct
{
    float x, y, z, w;
    float r, g, b;
    float u, v;
} R3DVertex;

typedef struct
{
    R3DVertex vertices[3];
} R3DTriangle;

typedef struct
{
    float x1;
    float y1;
    float x2;
    float y2;
} R3DEdge;

extern "C" {
int rush3d_card_init();
void rush3d_shutdown();
void rush3d_register_write(uint32_t offset, uint64_t data);
uint64_t rush3d_register_read(uint32_t offset);
void rush3d_screenshot();
void rush3d_swap_buffers();
}
