/**
 * test00.cpp
 *
 * Clears the screen colour to red
 */
#include <gl.h>
#include <r3d/rush3d.h>
#include <iostream>
#include <sys/neutrino.h>
#include <cstdlib>
#include <cmath>

#define VIDEO_WIDTH 640
#define VIDEO_HEIGHT 480

int main(int, char**)
{
	ThreadCtl(_NTO_TCTL_IO, NULL); // Should the driver do this?!
	rush3d_card_init();

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


    return 0;
}
