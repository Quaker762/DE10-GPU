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

enum class RegisterOffset : uint16_t
{
    VERTEX_A = 0x00,
    VERTEX_B = 0x08,
    VERTEX_C = 0x10,
    BACK_COLOUR = 0x18,
    CONTROL_STATUS = 0x20
};

typedef struct
{
    float x, y, z, w;
    // float r = 255.0f, g = 255.0f, b = 255.0f;
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

int rush3d_card_init();
void rush3d_shutdown();
void rush3d_register_write(RegisterOffset offset, uint32_t data);
uint32_t rush3d_register_read(RegisterOffset offset);
