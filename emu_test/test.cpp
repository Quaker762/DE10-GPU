/**
 * test00.cpp
 *
 * Clears the screen colour to red
 */
#include "gl.h"

#include <stdio.h>

#define VIDEO_WIDTH  800
#define VIDEO_HEIGHT 600

extern Rush3D g_card;

#define NUM_CUBE_VERTICES 108

static const GLfloat g_vertex_buffer_data[] = { -1.0f, -1.0f, -1.0f,                      // triangle 1 : begin
                                                -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  // triangle 1 : end
                                                1.0f,  1.0f,  -1.0f,                      // triangle 2 : begin
                                                -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, // triangle 2 : end
                                                1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f, 1.0f, -1.0f, 1.0f,
                                                -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  1.0f, -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f, 1.0f,  1.0f,
                                                1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  1.0f,  1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f, -1.0f, 1.0f };

void draw_cube()
{
    for(int i = 0; i < NUM_CUBE_VERTICES; i += 9)
    {
        glBegin(GL_TRIANGLES);
        glVertex3f(g_vertex_buffer_data[i], g_vertex_buffer_data[i + 1], g_vertex_buffer_data[i + 2]);
        glVertex3f(g_vertex_buffer_data[i + 3], g_vertex_buffer_data[i + 4], g_vertex_buffer_data[i + 5]);
        glVertex3f(g_vertex_buffer_data[i + 6], g_vertex_buffer_data[i + 7], g_vertex_buffer_data[i + 8]);
        glEnd();
    }
}

int main(int, char**)
{
    SDL_Event event;
    bool running = true;

    printf("%s\n", glGetString(GL_VENDOR));

    GLfloat aspect = (GLfloat)VIDEO_WIDTH / (GLfloat)VIDEO_HEIGHT; // Compute aspect ratio of window
    glMatrixMode(GL_PROJECTION);                                   // To operate on the Projection matrix
    glLoadIdentity();                                              // Reset
                                                                   // Let's work out the view frustum (this is ripped from Quake, cheers John)
    GLdouble xmin, xmax, ymin, ymax;
    ymax = 4.0f * tan(60.0f * M_PI / 360.0);
    ymin = -ymax;
    xmin = ymin * aspect;
    xmax = ymax * aspect;
    glFrustum(xmin, xmax, ymin, ymax, 4, 10);

    GLfloat z = -9.0f;
    GLfloat x_inc = 0.0f;
    GLfloat angle = 0.0f;
    glViewport(0, 0, VIDEO_WIDTH, VIDEO_HEIGHT);
    while(running)
    {
        angle -= 0.1f;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                running = false;
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, 0.0f);
        glRotatef(angle, 0.0f, 1.0f, 1.0f);
        glTranslatef(0.0f, 0.0f, z);
        draw_cube();

        g_card.flip(); // THIS SHOULD BE A REGISTER WRITE!
        SDL_UpdateWindowSurface(const_cast<SDL_Window*>(g_card.monitor()));
    }

    return 0;
}