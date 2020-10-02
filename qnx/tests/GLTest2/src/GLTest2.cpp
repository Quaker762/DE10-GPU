#include <GL/gl.h>
#include <r3d/rush3d.h>
#include <iostream>
#include <sys/neutrino.h>
#include <cstdlib>
#include <cmath>

#define VIDEO_WIDTH  800
#define VIDEO_HEIGHT 600

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
	ThreadCtl(_NTO_TCTL_IO, NULL); // Should the driver do this?!
	rush3d_card_init();

    bool running = true;

    printf("GL_VENDOR: %s\n", glGetString(GL_VENDOR));
    printf("GL_RENDERER: %s\n", glGetString(GL_RENDERER));
    printf("GL_VERSION: %s\n", glGetString(GL_VERSION));

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
    GLfloat angle = 0.0f;
    GLfloat z = -8.0f;
    while(running)
    {
        angle -= 0.9f;

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, 0.0f);
        glRotatef(angle, 0.0f, 1.0f, 1.0f);
        glTranslatef(0.0f, 0.0f, z);
        draw_cube();

        /** Uncomment me for more cubes!
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, 0.0f);
        glRotatef(angle, 0.0f, 1.0f, 0.0f);
        glTranslatef(-4.0f, 0.0f, -15.0f);
        draw_cube();

        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, 0.0f);
        glRotatef(angle, 1.0f, 1.0f, 0.0f);
        glTranslatef(4.0f, 3.0f, -12.0f);
        draw_cube();
        **/

        rush3d_swap_buffers();
    }

    return 0;
}
