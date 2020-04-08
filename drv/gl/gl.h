/**
 * Rush3D MiniGL driver
 *
 * Provides function prototypes for a small subset of the OpenGL 1 fixed
 * function pipeline, as well as providing typedefs.
 *
 * Copyright (c) 2020, Jesse Buhagiar, Jack Allan and Matthew Atkin
 * All rights reserved.
 * Unauthorized copying or reproduction of this project and the files contained within
 * is strictly prohibited.
 *
 * Author: Jesse Buhagiar
 * Date: 4/4/2020
 */
#pragma once

// Comment this shit out for the actual board!
#define USE_SIM
#ifdef USE_SIM
    #include "../../emu/rush3d/card.h"
extern Rush3D g_card;
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GLAPI
    #define GLAPI extern
#endif

// OpenGL related `defines`
#define GL_TRUE  1
#define GL_FALSE 0

// Matrix Modes
#define GL_MODELVIEW  0x0050
#define GL_PROJECTION 0x0051

// glBegin/glEnd primitive types
#define GL_TRIANGLES 0x0000
#define GL_QUADS     0x0001

// Buffer bits
#define GL_COLOR_BUFFER_BIT 0x0200

// Utility
#define GL_VENDOR   0x1F00
#define GL_RENDERER 0x1F01
#define GL_VERSION  0x1F02

//
// OpenGL typedefs
//
// Defines types used by all OpenGL applications
// https://www.khronos.org/opengl/wiki/OpenGL_Type
typedef char GLchar;
typedef unsigned char GLuchar;
typedef unsigned char GLubyte;
typedef short GLshort;
typedef unsigned short GLushort;
typedef int GLint;
typedef unsigned int GLuint;
typedef int GLfixed;
typedef long long GLint64;
typedef unsigned long long GLuint64;
typedef unsigned long GLsizei;
typedef void GLvoid;
typedef float GLfloat;
typedef float GLclampf;
typedef unsigned int GLenum;
typedef unsigned int GLbitfield;

GLAPI void glClear(GLbitfield mask);
GLAPI void glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
GLAPI GLubyte* glGetString(GLenum name);
GLAPI void glMatrixMode(GLenum mode);
GLAPI void glPushMatrix();
GLAPI void glPopMatrix();

#ifdef __cplusplus
}
#endif