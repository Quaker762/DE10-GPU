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
#include "assertions.h"
#include "gl.h"
#include "glcontext.h"
#include "log.hpp"
#include "math/vec4.h"
#include "r3d/rush3d.h"

#include <algorithm>
#include <vector>

// static std::list<R3D_Triangle> triangle_list;
static std::vector<R3DVertex> vertex_list;

void glBegin(GLenum mode)
{
    ASSERT(mode == GL_TRIANGLES || mode == GL_QUADS);
    g_gl_state->curr_draw_mode = mode;
}

static bool compare_y_values(const R3DVertex& a, const R3DVertex& b)
{
    return a.y < b.y;
}

void glEnd()
{
    // At this point, the user has effectively specified that they are done with defining the geometry
    // of what they want to draw. We now need to do a few things (https://www.khronos.org/opengl/wiki/Rendering_Pipeline_Overview):
    //
    // 1.   Transform all of the vertices in the current vertex list into eye space by mulitplying the model-view matrix
    // 2.   Transform all of the vertices from eye space into clip space by multiplying by the projection matrix
    // 3.   If culling is enabled, we cull the desired faces (https://learnopengl.com/Advanced-OpenGL/Face-culling)
    // 4.   Each element of the vertex is then divided by w to bring the positions into NDC (Normalized Device Coordinates)
    // 5.   The vertices are sorted (for the rasteriser, how are we doing this? 3Dfx did this top to bottom in terms of vertex y co-ordinates)
    // 6.   The vertices are then sent off to the rasteriser and drawn to the screen

#ifdef USE_SIM
    float scr_width = static_cast<float>(g_card.read_register(RegisterOffsets::fbWIDTH));
    float scr_height = static_cast<float>(g_card.read_register(RegisterOffsets::fbHEIGHT));
#endif

    for(size_t i = 0; i < vertex_list.size(); i++)
    {
        R3DVertex& vertex = vertex_list.at(i);
        Vec4 vec({ vertex.x, vertex.y, vertex.z, 1.0f });

        // First multiply the vertex by the MODELVIEW matrix and then the PROJECTION matrix
        vec = vec * g_gl_state->model_view_matrix;
        vec = vec * g_gl_state->projection_matrix;

        if(vec.w() != 0.0f)
        {
            vec.x(vec.x() / vec.w());
            vec.y(vec.y() / vec.w());
            vec.z(vec.z() / vec.w());
        }

        // https://www.khronos.org/registry/OpenGL-Refpages/es2.0/xhtml/glViewport.xml
        vertex.x = (vec.x() + 1.0f) * (scr_width / 2.0f) + 0.0f; // TODO: 0.0f should be something!?
        vertex.y = scr_height - ((vec.y() + 1.0f) * (scr_height / 2.0f) + 0.0f);
        vertex.z = vec.z();
    }

    // Now we sort the vertices by their y values. A is the vertex that has the least y value,
    // B is the middle and C is the bottom.
    std::sort(vertex_list.begin(), vertex_list.end(), compare_y_values);

    if(g_gl_state->curr_draw_mode == GL_TRIANGLES)
    {
        ASSERT((vertex_list.size() % 3) == 0);
        for(size_t i = 0; i < vertex_list.size(); i += 3)
        {
            R3DVertex a = vertex_list.at(i);
            R3DVertex b = vertex_list.at(i + 1);
            R3DVertex c = vertex_list.at(i + 2);

#ifdef USE_SIM
            // std::printf("GL_PROJECTION\n");
            // g_gl_state->projection_matrix.print();
            // std::printf("\nGL_MODELVIEW\n");
            // g_gl_state->model_view_matrix.print();
            // ASSERT_NOT_REACHED;
            // We should probably wait here too
            g_card.write_register(RegisterOffsets::vertexAx, a.x);
            g_card.write_register(RegisterOffsets::vertexAy, a.y);
            g_card.write_register(RegisterOffsets::vertexBx, b.x);
            g_card.write_register(RegisterOffsets::vertexBy, b.y);
            g_card.write_register(RegisterOffsets::vertexCx, c.x);
            g_card.write_register(RegisterOffsets::vertexCy, c.y);
            g_card.write_register(RegisterOffsets::cmdTriangle, 1);
#endif
        }

        // We probably need to wait for the card to finish drawing here before we clear
        vertex_list.clear();
    }
    else
    {
        ASSERT_NOT_REACHED; // Crash for now!
    }
}

void glColor3f(GLfloat r, GLfloat g, GLfloat b)
{
    g_gl_state->curr_vertex_color.r = std::clamp(r, 0.0f, 255.0f);
    g_gl_state->curr_vertex_color.g = std::clamp(g, 0.0f, 255.0f);
    g_gl_state->curr_vertex_color.b = std::clamp(b, 0.0f, 255.0f);
    g_gl_state->curr_vertex_color.a = 255.0f;
}

void glVertex3f(GLfloat x, GLfloat y, GLfloat z)
{
    R3DVertex vertex;

    vertex.x = x;
    vertex.y = y;
    vertex.z = z;
    vertex.r = g_gl_state->curr_vertex_color.r;
    vertex.g = g_gl_state->curr_vertex_color.g;
    vertex.b = g_gl_state->curr_vertex_color.b;

    vertex_list.push_back(vertex);
}