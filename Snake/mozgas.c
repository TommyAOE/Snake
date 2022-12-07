#include "debugmalloc.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>

#include "mozgas.h"

Vektor irany(Vektor vektor, SDL_Event event, int player)
{
    if(player == 1)
    {
        switch(event.key.keysym.scancode)
        {
        case SDL_SCANCODE_UP:
            if(vektor.y != 1)
            {
                vektor.x = 0;
                vektor.y = -1;
            }
            break;
        case SDL_SCANCODE_DOWN:
            if(vektor.y != -1)
            {
                vektor.x = 0;
                vektor.y = 1;
            }
            break;
        case SDL_SCANCODE_LEFT:
            if(vektor.x != 1)
            {
                vektor.x = -1;
                vektor.y = 0;
            }
            break;
        case SDL_SCANCODE_RIGHT:
            if(vektor.x != -1)
            {
                vektor.x = 1;
                vektor.y = 0;
            }
            break;
        }
    }
    else
    {
        switch(event.key.keysym.scancode)
        {
        case SDL_SCANCODE_W:
            if(vektor.y != 1)
            {
                vektor.x = 0;
                vektor.y = -1;
            }
            break;
        case SDL_SCANCODE_S:
            if(vektor.y != -1)
            {
                vektor.x = 0;
                vektor.y = 1;
            }
            break;
        case SDL_SCANCODE_A:
            if(vektor.x != 1)
            {
                vektor.x = -1;
                vektor.y = 0;
            }
            break;
        case SDL_SCANCODE_D:
            if(vektor.x != -1)
            {
                vektor.x = 1;
                vektor.y = 0;
            }
            break;
        }
    }


    return vektor;
}
