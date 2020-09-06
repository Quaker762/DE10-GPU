/**
 *
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    float x, y, z, w;
    //float r = 255.0f, g = 255.0f, b = 255.0f;
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

#ifdef __cplusplus
}
#endif
