/**
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

#include <cstdint>

#define VERTEX_A       0x00
#define VERTEX_B       0x08
#define VERTEX_C       0x10
#define COLOR_A        0x18
#define COLOR_B        0x20
#define COLOR_C        0x28
#define BACK_COLOR     0x30
#define CONTROL_STATUS 0x38
#define WIN_SIZE       0x40

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
}
