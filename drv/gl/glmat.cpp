/**
 * Copyright (c) 2020, Jesse Buhagiar, Jack Allan and Matthew Atkin
 * All rights reserved.
 * Unauthorized copying or reproduction of this project and the files contained within
 * is strictly prohibited.
 *
 * Author: Jesse Buhagiar
 * Date: 4/4/2020
 */
#include "assertions.h"
#include "gl.h"
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
        g_gl_state->projection_matrix = g_gl_state->model_view_matrix_stack.top();
        g_gl_state->model_view_matrix_stack.pop();
        break;
    default:
        log(LogLevel::ERROR, "glPopMatrix(): Attempt to pop matrix with invalid matrix mode, 0x%x\n", g_gl_state->curr_matrix_mode);
        break;
    }
}