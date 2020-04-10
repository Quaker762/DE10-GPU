/*
 * Copyright (c) 2020, Jesse Buhagiar, Jack Allan and Matthew Atkin
 * All rights reserved.
 * Unauthorized copying or reproduction of this project and the files contained within
 * is strictly prohibited.
 *
 * Author: Jesse Buhagiar
 * Date: 4/4/2020
 */
#include "assert.h"
#include "gl.h"
#include "glcontext.h"
#include "log.hpp"

#include <cmath>
#include <string>

static const std::string s_vendor = "SOCFX Interactive"; // Ha ha ha. Change this when we have a name lmfao
static const std::string s_renderer = "Rush3D Cyclone V Graphics Accelerator";
static const std::string s_version = "OpenGL 1.2 SOCFX Interactive";

void glClear(GLbitfield mask)
{
    if(mask & GL_COLOR_BUFFER_BIT)
    {
        uint8_t r = floor(g_gl_state->clear_color.r * 255.0);
        uint8_t g = floor(g_gl_state->clear_color.g * 255.0);
        uint8_t b = floor(g_gl_state->clear_color.b * 255.0);

#ifdef USE_SIM
        g_card.write_register(RegisterOffsets::fbCOLOR, (r << 16) | (g << 8) | b);
        g_card.write_register(RegisterOffsets::fbFILL, 1); // Execute fill command
#endif
    }
    else
    {
        // set gl error here!?
    }
}

void glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
    g_gl_state->clear_color.r = red;
    g_gl_state->clear_color.g = green;
    g_gl_state->clear_color.b = blue;
    g_gl_state->clear_color.a = alpha;
}

GLubyte* glGetString(GLenum name)
{
    switch(name)
    {
    case GL_VENDOR:
        return reinterpret_cast<GLubyte*>(const_cast<char*>(s_vendor.c_str()));
    case GL_RENDERER:
        return reinterpret_cast<GLubyte*>(const_cast<char*>(s_renderer.c_str()));
    case GL_VERSION:
        return reinterpret_cast<GLubyte*>(const_cast<char*>(s_version.c_str()));
    default:
#ifdef DEBUG
        log(LogLevel::WARN, "glGetString(): Unknown enum name!\n");
#endif
        break;
    }

    // TODO: Set glError to GL_INVALID_ENUM here
    return 0;
}