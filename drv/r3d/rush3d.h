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

#define VERTEX_A_L 0x00
#define VERTEX_A_H 0x01

#define VERTEX_B_L 0x02
#define VERTEX_B_H 0x03

#define VERTEX_C_L 0x04
#define VERTEX_C_H 0x05

#define BACK_COLOUR 0x06

#define CONTROL_STATUS_L 0x08
#define CONTROL_STATUS_H 0x09

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
void rush3d_register_write(uint32_t offset, uint32_t data);
uint32_t rush3d_register_read(uint32_t offset);
