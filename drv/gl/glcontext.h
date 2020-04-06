/**
 *  Describes the current OpenGL rendering context (and it's state).
 *
 *  This is used by the driver to know what state the OpenGL renderer is in (i.e
 *  the matrix mode, the matrix stack") as well as any other "state" that the
 *  driver needs to know about. This state is _global_, meaning the struct is
 *  defined.
 *
 *
 *
 */
#pragma once

#include "gl.h"
#include "glstruct.h"
#include "math/mat3.h"
#include "math/mat4.h"

#include <stack>

struct GLContext
{
    GLenum curr_draw_mode;
    GLenum curr_matrix_mode;
    Mat4 projection_matrix;
    Mat4 model_view_matrix;

    color_t clear_color;
};

extern GLContext g_gl_state;
extern Mat4 g_curr_matrix;