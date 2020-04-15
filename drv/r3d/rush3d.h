/**
 *
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    float x, y, z;
    float r, g, b;
    float u, v;
} R3DVertex;

typedef struct
{
    R3DVertex a, b, c;
} R3DTriangle;

#ifdef __cplusplus
}
#endif