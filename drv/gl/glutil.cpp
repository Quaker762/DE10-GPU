/**
 *  Definition of Utility OpenGL pipeline functions, such as `glClear()`
 */
#include "assert.h"
#include "gl.h"
#include "glcontext.h"

void glClear(GLbitfield mask)
{
    if(mask & GL_COLOR_BUFFER_BIT)
    {
        // TODO: Send card clear command here based on glClearColor
    }
    else
    {
        // set gl error here!?
    }
}

void glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
    g_gl_state.clear_color.r = red;
    g_gl_state.clear_color.g = green;
    g_gl_state.clear_color.b = blue;
    g_gl_state.clear_color.a = alpha;
}