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
#include "GL/gl.h"
#include "glcontext.h"

#include <algorithm>

#if(__cplusplus <= 201402L)
static float clamp(GLfloat variable, GLfloat min, GLfloat max)
{
    return std::min(max, std::max(variable, min));
}

void glColor3f(GLfloat r, GLfloat g, GLfloat b)
{
    g_gl_state->curr_vertex_color.r = clamp(r, 0.0f, 255.0f);
    g_gl_state->curr_vertex_color.g = clamp(g, 0.0f, 255.0f);
    g_gl_state->curr_vertex_color.b = clamp(b, 0.0f, 255.0f);
    g_gl_state->curr_vertex_color.a = 255.0f;
}
#elif(__cplusplus == 201703L)
void glColor3f(GLfloat r, GLfloat g, GLfloat b)
{
    g_gl_state->curr_vertex_color.r = std::clamp(r, 0.0f, 255.0f);
    g_gl_state->curr_vertex_color.g = std::clamp(g, 0.0f, 255.0f);
    g_gl_state->curr_vertex_color.b = std::clamp(b, 0.0f, 255.0f);
    g_gl_state->curr_vertex_color.a = 255.0f;
}
#else
    #error "Could not determine c++ version in glcolor.cpp (for missing std::clamp)"
#endif