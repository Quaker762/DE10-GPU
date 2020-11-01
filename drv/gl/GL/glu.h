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
 * Rush3D MiniGLU driver
 *
 * Provides a few utility functions found in the GL Utility Library (GLU)
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