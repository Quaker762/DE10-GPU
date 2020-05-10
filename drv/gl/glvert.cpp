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
static std::vector<R3DTriangle> triangle_list;

void glBegin(GLenum mode)
{
    ASSERT(mode == GL_TRIANGLES || mode == GL_QUADS);
    g_gl_state->curr_draw_mode = mode;
}

static bool compare_y_values(const R3DVertex& a, const R3DVertex& b)
{
    return a.y < b.y;
}

enum class Boundary
{
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};

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

    ASSERT(g_gl_state->curr_draw_mode == GL_TRIANGLES); // We only support GL_TRIANGLES at the moment

    // Let's construct some triangles
    if(g_gl_state->curr_draw_mode == GL_TRIANGLES)
    {
        R3DTriangle triangle;
        for(size_t i = 0; i < vertex_list.size(); i += 3)
        {
            triangle.vertices[0] = vertex_list.at(i);
            triangle.vertices[1] = vertex_list.at(i + 1);
            triangle.vertices[2] = vertex_list.at(i + 2);

            triangle_list.push_back(triangle);
        }
    }
    else
    {
        ASSERT_NOT_REACHED; // We only support GL_TRIANGLES at the moment!
    }

    // Now let's transform each triangle and send that to the GPU
    for(size_t i = 0; i < triangle_list.size(); i++)
    {
        R3DTriangle& triangle = triangle_list.at(i);
        R3DVertex& vertexa = triangle.vertices[0];
        R3DVertex& vertexb = triangle.vertices[1];
        R3DVertex& vertexc = triangle.vertices[2];

        Vec4 veca({ vertexa.x, vertexa.y, vertexa.z, 1.0f });
        Vec4 vecb({ vertexb.x, vertexb.y, vertexb.z, 1.0f });
        Vec4 vecc({ vertexc.x, vertexc.y, vertexc.z, 1.0f });

        // First multiply the vertex by the MODELVIEW matrix and then the PROJECTION matrix
        veca = veca * g_gl_state->model_view_matrix;
        veca = veca * g_gl_state->projection_matrix;

        vecb = vecb * g_gl_state->model_view_matrix;
        vecb = vecb * g_gl_state->projection_matrix;

        vecc = vecc * g_gl_state->model_view_matrix;
        vecc = vecc * g_gl_state->projection_matrix;

        // At this point, we're in clip space
        // Here's where we do the clipping. This is a really crude implementation of the
        // https://learnopengl.com/Getting-started/Coordinate-Systems
        // "Note that if only a part of a primitive e.g. a triangle is outside the clipping volume OpenGL
        // will reconstruct the triangle as one or more triangles to fit inside the clipping range. "
        //
        // ALL VERTICES ARE DEFINED IN A CLOCKWISE ORDER
        if(veca.w() != 0.0f)
        {
            // This brings us from clip space to Normalized Device Co-ordinates
            veca.x(veca.x() / veca.w());
            veca.y(veca.y() / veca.w());
            veca.z(veca.z() / veca.w());
        }

        if(vecb.w() != 0.0f)
        {
            // This brings us from clip space to Normalized Device Co-ordinates
            vecb.x(vecb.x() / vecb.w());
            vecb.y(vecb.y() / vecb.w());
            vecb.z(vecb.z() / vecb.w());
        }

        if(vecb.w() != 0.0f)
        {
            // This brings us from clip space to Normalized Device Co-ordinates
            vecc.x(vecc.x() / vecc.w());
            vecc.y(vecc.y() / vecc.w());
            vecc.z(vecc.z() / vecc.w());
        }

        // Perform the viewport transform
        // https://www.khronos.org/registry/OpenGL-Refpages/es2.0/xhtml/glViewport.xml
        vertexa.x = (veca.x() + 1.0f) * (scr_width / 2.0f) + 0.0f; // TODO: 0.0f should be something!?
        vertexa.y = scr_height - ((veca.y() + 1.0f) * (scr_height / 2.0f) + 0.0f);
        vertexa.z = veca.z();

        vertexb.x = (vecb.x() + 1.0f) * (scr_width / 2.0f) + 0.0f; // TODO: 0.0f should be something!?
        vertexb.y = scr_height - ((vecb.y() + 1.0f) * (scr_height / 2.0f) + 0.0f);
        vertexb.z = vecb.z();

        vertexc.x = (vecc.x() + 1.0f) * (scr_width / 2.0f) + 0.0f; // TODO: 0.0f should be something!?
        vertexc.y = scr_height - ((vecc.y() + 1.0f) * (scr_height / 2.0f) + 0.0f);
        vertexc.z = vecc.z();
    }

    if(g_gl_state->curr_draw_mode == GL_TRIANGLES)
    {
        for(size_t i = 0; i < triangle_list.size(); i++)
        {
            std::vector<R3DVertex> sort_vert_list;
            R3DTriangle& triangle = triangle_list.at(i);

            // Now we sort the vertices by their y values. A is the vertex that has the least y value,
            // B is the middle and C is the bottom.
            // These are sorted in groups of 3
            sort_vert_list.push_back(triangle.vertices[0]);
            sort_vert_list.push_back(triangle.vertices[1]);
            sort_vert_list.push_back(triangle.vertices[2]);

            std::sort(sort_vert_list.begin(), sort_vert_list.end(), compare_y_values);

            triangle.vertices[0] = sort_vert_list.at(0);
            triangle.vertices[1] = sort_vert_list.at(1);
            triangle.vertices[2] = sort_vert_list.at(2);

#ifdef USE_SIM
            // std::printf("GL_PROJECTION\n");
            // g_gl_state->projection_matrix.print();
            // std::printf("\nGL_MODELVIEW\n");
            // g_gl_state->model_view_matrix.print();
            // ASSERT_NOT_REACHED;
            // We should probably wait here too
            g_card.write_register(RegisterOffsets::vertexAx, triangle.vertices[0].x);
            g_card.write_register(RegisterOffsets::vertexAy, triangle.vertices[0].y);
            g_card.write_register(RegisterOffsets::vertexBx, triangle.vertices[1].x);
            g_card.write_register(RegisterOffsets::vertexBy, triangle.vertices[1].y);
            g_card.write_register(RegisterOffsets::vertexCx, triangle.vertices[2].x);
            g_card.write_register(RegisterOffsets::vertexCy, triangle.vertices[2].y);
            g_card.write_register(RegisterOffsets::cmdTriangle, 1);
#endif
        }

        // We probably need to wait for the card to finish drawing here before we clear
        triangle_list.clear();
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