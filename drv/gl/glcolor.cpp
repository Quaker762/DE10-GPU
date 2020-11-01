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