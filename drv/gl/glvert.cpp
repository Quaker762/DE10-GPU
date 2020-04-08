/*
 * Copyright (c) 2020, Jesse Buhagiar, Jack Allan and Matthew Atkin
 * All rights reserved.
 * Unauthorized copying or reproduction of this project and the files contained within
 * is strictly prohibited.
 *
 * Author: Jesse Buhagiar
 * Date: 8/4/2020
 *
 */
#include "assert.h"
#include "gl.h"
#include "glcontext.h"

void glBegin(GLenum mode)
{
    ASSERT(mode == GL_TRIANGLES || mode == GL_QUADS);
    g_gl_state->curr_draw_mode = mode;
}