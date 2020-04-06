/**
 *  Rush3D MiniGL driver
 *
 *  Provides function prototypes for a small subset of the OpenGL 1 fixed
 *  function pipeline, as well as providing typedefs.
 *
 *  Copyright 2020 Jesse Buhagiar, Matthew Atkin and Jack Allan
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GLAPI
    #define GLAPI extern
#endif

// OpenGL related `defines`
#define GL_TRUE  1
#define GL_FALSE 0

#define GL_MODELVIEW  0x0050
#define GL_PROJECTION 0x0051

#define GL_TRIANGLES 0x0100
#define GL_QUADS     0x0101

#define GL_COLOR_BUFFER_BIT 0x0200

//
// OpenGL typedefs
//
// Defines types used by all OpenGL applications
// https://www.khronos.org/opengl/wiki/OpenGL_Type
typedef char GLchar;
typedef unsigned char GLuchar;
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

#ifdef __cplusplus
}
#endif