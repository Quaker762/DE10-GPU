/*
 * Copyright (c) 2020, Jesse Buhagiar, Jack Allan and Matthew Atkin
 * All rights reserved.
 * Unauthorized copying or reproduction of this project and the files contained within
 * is strictly prohibited.
 *
 * Author: Jesse Buhagiar
 * Date: 16/5/2020
 *
 */
#include "gl.h"
#include "glcontext.h"

#include <algorithm>

void glColor3f(GLfloat r, GLfloat g, GLfloat b)
{
    g_gl_state->curr_vertex_color.r = std::clamp(r, 0.0f, 255.0f);
    g_gl_state->curr_vertex_color.g = std::clamp(g, 0.0f, 255.0f);
    g_gl_state->curr_vertex_color.b = std::clamp(b, 0.0f, 255.0f);
    g_gl_state->curr_vertex_color.a = 255.0f;
}