/**
 * test00.cpp
 * 
 * Clears the screen colour to red
 */
#include <stdio.h>
#include <SDL2/SDL.h>
#include <GL/gl.h>

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

    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                running = false;
        }

        glViewport(0, 0, VIDEO_WIDTH, VIDEO_HEIGHT);
        glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(hwnd);
    }

    return 0;
}