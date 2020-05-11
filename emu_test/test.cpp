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
    glFrustum(xmin, xmax, ymin, ymax, 4, 4096);

    GLfloat z = -7.0f;
    glViewport(0, 0, VIDEO_WIDTH, VIDEO_HEIGHT);
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                running = false;
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glBegin(GL_TRIANGLES);

        // Triangle 1
        glVertex3f(-2.0f, 1.0f, z);  // Bottom left corner
        glVertex3f(-4.0f, -1.0f, z); // Top left corner (the origin)
        glVertex3f(2.0f, 1.0f, z);   // Bottom right corner

        // Triangle 2
        /**
        glVertex3f(-1.0f, -1.0f, -0.01f); // Top left corner (the origin)
        glVertex3f(-1.0f, 1.0f, -0.01f);  // Bottom left corner
        glVertex3f(1.0f, 1.0f, -0.01f);   // Bottom right corner
        **/
        glEnd();

        z += 0.001f;
        printf("%.6f\n", z);

        g_card.flip(); // THIS SHOULD BE A REGISTER WRITE!
        SDL_UpdateWindowSurface(const_cast<SDL_Window*>(g_card.monitor()));
    }

    return 0;
}