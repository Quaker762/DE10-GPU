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
 * Author: Jesse Buhagiar
 * Date: 4/4/2020
 */
#include "GL/gl.h"
#include "assertions.h"
#include "glcontext.h"
#include "log.hpp"

void glMatrixMode(GLenum mode)
{
    ASSERT(mode == GL_MODELVIEW || mode == GL_PROJECTION);
    g_gl_state->curr_matrix_mode = mode;
}

/*
 * Push the current matrix (based on the current matrix mode)
 * to its' corresponding matrix stack in the current OpenGL
 * state context
 */
void glPushMatrix()
{
#ifdef DEBUG
    log(LogLevel::INFO, "glPushMatrix(): Pushing matrix to the matrix stack (matrix_mode = 0x%x)\n", g_gl_state->curr_matrix_mode);
#endif

    switch(g_gl_state->curr_matrix_mode)
    {
    case GL_PROJECTION:
        g_gl_state->projection_matrix_stack.push(g_gl_state->projection_matrix);
        break;
    case GL_MODELVIEW:
        g_gl_state->model_view_matrix_stack.push(g_gl_state->model_view_matrix);
        break;
    default:
        log(LogLevel::ERROR, "glPushMatrix(): Attempt to push matrix with invalid matrix mode, 0x%x\n", g_gl_state->curr_matrix_mode);
        break;
    }
}

/*
 * Pop a matrix from the corresponding matrix stack into the
 * corresponding matrix in the state based on the current
 * matrix mode
 */
void glPopMatrix()
{
#ifdef DEBUG
    log(LogLevel::INFO, "glPopMatrix(): Popping matrix from matrix stack (matrix_mode = 0x%x)\n", g_gl_state->curr_matrix_mode);
#endif

    // TODO: Make sure stack::top() doesn't cause any  nasty issues if it's empty (that could result in a lockup/hang)
    switch(g_gl_state->curr_matrix_mode)
    {
    case GL_PROJECTION:
        g_gl_state->projection_matrix = g_gl_state->projection_matrix_stack.top();
        g_gl_state->projection_matrix_stack.pop();
        break;
    case GL_MODELVIEW:
        g_gl_state->model_view_matrix = g_gl_state->model_view_matrix_stack.top();
        g_gl_state->model_view_matrix_stack.pop();
        break;
    default:
        log(LogLevel::ERROR, "glPopMatrix(): Attempt to pop matrix with invalid matrix mode, 0x%x\n", g_gl_state->curr_matrix_mode);
        break;
    }
}

void glLoadIdentity()
{
    if(g_gl_state->curr_matrix_mode == GL_PROJECTION)
        g_gl_state->projection_matrix.load_identity();
    else if(g_gl_state->curr_matrix_mode == GL_MODELVIEW)
        g_gl_state->model_view_matrix.load_identity();
    else
        ASSERT_NOT_REACHED;
}

/**
 * Create a viewing frustum (a.k.a a "Perspective Matrix") in the current matrix. This
 * is usually done to the projection matrix. The current matrix is then multiplied
 * by this viewing frustum matrix.
 *
 * https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glFrustum.xml
 *
 *
 * TODO: We need to check for some values that could result in a division by zero
 * or some other fuckery that will fuck with the driver here!
 */
void glFrustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble nearVal, GLdouble farVal)
{
    Mat4 frustum;
    GLdouble a;
    GLdouble b;
    GLdouble c;
    GLdouble d;

    // Let's do some math!
    a = (right + left) / (right - left);
    b = (top + bottom) / (top - bottom);
    c = -((farVal + nearVal) / (farVal - nearVal));
    d = -((2 * (farVal * nearVal)) / (farVal - nearVal));

    frustum(0, 0, ((2 * nearVal) / (right - left)));
    frustum(1, 1, ((2 * nearVal) / (top - bottom)));
    frustum(2, 0, a);
    frustum(2, 1, b);
    frustum(2, 2, c);
    frustum(2, 3, -1);
    frustum(3, 2, d);
    frustum(3, 3, 0);
    // Phew

    if(g_gl_state->curr_matrix_mode == GL_PROJECTION)
    {
        g_gl_state->projection_matrix = g_gl_state->projection_matrix * frustum;
    }
    else if(g_gl_state->curr_matrix_mode == GL_MODELVIEW)
    {
#ifdef DEBUG
        log(LogLevel::WARN, "glFrustum(): frustum created with curr_matrix_mode == GL_MODELVIEW!!!\n");
#endif
        g_gl_state->projection_matrix = g_gl_state->model_view_matrix * frustum;
    }
}