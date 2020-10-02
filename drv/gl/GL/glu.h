/**
 * Rush3D MiniGLU driver
 *
 * Provides a few utility functions found in the GL Utility Library (GLU)
 *
 * Copyright (c) 2020, Jesse Buhagiar, Jack Allan and Matthew Atkin
 * All rights reserved.
 * Unauthorized copying or reproduction of this project and the files contained within
 * is strictly prohibited.
 *
 * Author: Jesse Buhagiar
 * Date: 1/10/2020
 */
#pragma once

#include "GL/GL.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GLAPI
    #define GLAPI extern
#endif

GLAPI void gluLookAt(GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ, GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat upX, GLfloat upY, GLfloat upZ);

#ifdef __cplusplus
}
#endif