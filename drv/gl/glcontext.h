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
 *
 * Describes the current OpenGL rendering context (and it's state).
 *
 * This is used by the driver to know what state the OpenGL renderer is in (i.e
 * the matrix mode, the matrix stack") as well as any other "state" that the
 * driver needs to know about. This state is _global_, meaning the struct is
 * defined.
 *
 * Provides function prototypes for a small subset of the OpenGL 1 fixed
 * function pipeline, as well as providing typedefs.
 *
 * Author: Jesse Buhagiar
 * Date: 4/4/2020
 */
#pragma once

#include "GL/gl.h"
#include "glstruct.h"
#include "math/mat4.h"

#include <stack>

struct GLContext
{
    GLenum curr_draw_mode;
    GLenum curr_matrix_mode;
    Mat4 projection_matrix;
    Mat4 model_view_matrix;

    std::stack<Mat4> projection_matrix_stack;
    std::stack<Mat4> model_view_matrix_stack;

    color_t clear_color = { 0.0f, 0.0f, 0.0f, 0.0f };
    color_t curr_vertex_color = { 255.0f, 255.0f, 255.0f, 255.0f };
};

extern GLContext* g_gl_state;
extern Mat4 g_curr_matrix;