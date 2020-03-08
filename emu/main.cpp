/**
 * 
 */
#include "rush3d/card.h"

#include <SDL2/SDL.h>
#include <cstdio>

static Rush3D* s_card;

int main(int, char**)
{
    SDL_Init(SDL_INIT_VIDEO);

    s_card = new Rush3D();

    // SDL shit
    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        s_card->write_register(RegisterOffsets::DBGR, 0xff);
        s_card->write_register(RegisterOffsets::DBGR, 0xff);
        s_card->write_register(RegisterOffsets::DBGR, 0xff);
        s_card->send_command(Commands::COMMAND_CLEAR);

        s_card->flip();
        SDL_UpdateWindowSurface(const_cast<SDL_Window*>(s_card->monitor()));
    }

    return 0;
}