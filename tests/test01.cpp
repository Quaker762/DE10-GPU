/**
 * test01.cpp
 * 
 * Draws a red triangle on a black background to the screen
 */
#include <stdio.h>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define VIDEO_WIDTH 800
#define VIDEO_HEIGHT 600

static SDL_Window* _initSDL(int width, int height)
{
    SDL_Window* hwnd = nullptr;
    SDL_GLContext gl_ctxt = nullptr;

    hwnd = SDL_CreateWindow(__FILE__, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    
    if(!hwnd)
        return NULL;

    gl_ctxt = SDL_GL_CreateContext(hwnd); // Attach GL Context to the created window
    return hwnd;
}

int main(int, char**)
{
    SDL_Window* hwnd = _initSDL(VIDEO_WIDTH, VIDEO_HEIGHT);
    SDL_Event event;
    bool running = true;

    if(hwnd == NULL)
    {
        printf("failed to create OpenGL window!\n");
        return 1;
    }

    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

    GLfloat aspect = (GLfloat)VIDEO_WIDTH / (GLfloat)VIDEO_HEIGHT; // Compute aspect ratio of window
    glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
    glLoadIdentity(); // Reset
    gluPerspective(45.0f, aspect, 0.1f, 100.0f); // Perspective projection: fovy, aspect, near, far
    glPointSize(5.0f);
    glViewport(0, 0, VIDEO_WIDTH, VIDEO_HEIGHT);

    GLfloat rot = 0.0f;
    while(running)
    {
        rot += 0.2f;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                running = false;
        }

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -5.0f);

        glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 0.0f); // Top left corner (the origin)
        glVertex3f(-1.0f, 1.0f, 0.0f); // Bottom left corner
        glVertex3f(1.0f, 1.0f, 0.0f); // Bottom right corner
        glEnd();

        SDL_GL_SwapWindow(hwnd);
    }

    return 0;
}