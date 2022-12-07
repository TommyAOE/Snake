#include "debugmalloc.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#define WINDOW_HEIGHT 750
#define WINDOW_WIDTH 1025

void sdlInit(SDL_Window **window, SDL_Renderer **ren)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Nem indult el az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *windowI = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if(window == NULL)
    {
        printf("Nem hozhato letre az ablak: %s", SDL_GetError);
        exit(1);
    }
    SDL_Renderer *renI = SDL_CreateRenderer(windowI, -1, SDL_RENDERER_SOFTWARE);
    if(ren == NULL)
    {
        printf("Nem sikerult letrehozni a renderert: %s", SDL_GetError);
        exit(1);
    }
    SDL_RenderClear(renI);

    *window = windowI;
    *ren = renI;
}
