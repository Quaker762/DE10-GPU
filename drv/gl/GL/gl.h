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
 * Provides function prototypes for a small subset of the OpenGL 1 fixed
 * function pipeline, as well as providing typedefs.
 *
 * Author: Jesse Buhagiar
 * Date: 4/4/2020
 */
#pragma once

// Comment this shit out for the actual board!
//#define USE_SIM
#ifdef USE_SIM
    #include "../chipsim/rush3d/card.h"
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
#define GL_TRIANGLES      0x0100
#define GL_QUADS          0x0101
#define GL_TRIANGLE_FAN   0x0102
#define GL_TRIANGLE_STRIP 0x0103
#define GL_POLYGON        0x0104

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
typedef double GLdouble;
typedef unsigned int GLenum;
typedef unsigned int GLbitfield;

GLAPI void glBegin(GLenum mode);
GLAPI void glClear(GLbitfield mask);
GLAPI void glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
GLAPI void glColor3f(GLfloat r, GLfloat g, GLfloat b);
GLAPI void glEnd();
GLAPI void glFrustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble nearVal, GLdouble farVal);
GLAPI GLubyte* glGetString(GLenum name);
GLAPI void glLoadIdentity();
GLAPI void glMatrixMode(GLenum mode);
GLAPI void glPushMatrix();
GLAPI void glPopMatrix();
GLAPI void glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
GLAPI void glTranslatef(GLfloat x, GLfloat y, GLfloat z);
GLAPI void glVertex3f(GLfloat x, GLfloat y, GLfloat z);
GLAPI void glViewport(GLint x, GLint y, GLsizei width, GLsizei height);

#ifdef __cplusplus
}
#endif