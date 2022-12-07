#include "debugmalloc.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include "SDL.h"
#include "mozgas.h"
#include "kigyo1.h"
#include "UI.h"
#include "Single.h"

//kígyó mozgásához szükséges vektor, megadja melyik irányba menjen
int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Renderer *ren;
    bool single = false, multi = false, exit = false;
    //inicializálja az sdlt
    sdlInit(&window, &ren);
    //elkészíti a textúrát
    SDL_Texture *unit1T = IMG_LoadTexture(ren, "unit1.jpg");
    SDL_Texture *unit2T = IMG_LoadTexture(ren, "unit2.jpg");
    SDL_Texture *keretT = IMG_LoadTexture(ren, "keret.jpg");
    SDL_Texture *foodT = IMG_LoadTexture(ren, "food.png");
    TTF_Init();
    TTF_Font *font;
    font = TTF_OpenFont("FFFFORWA.TTF", 70);
    SDL_Color feher = {255,255,255};
    SDL_Color piros = {255,0,0};

    time_t t;
    srand((unsigned) time(&t));
    while(!exit)
    {
        int menuResponse = menu(ren, font);
        switch(menuResponse)
        {
        case 0:
            single = true;
            exit = false;
            multi = false;
            break;
        case 1:
            multi = true;
            exit = false;
            single = false;
            break;
        case 2:
            exit = true;
            break;
        }
        if(single && !exit)
        {
            SinglePlayer(ren, unit1T, feher, font, foodT, keretT);
        }
        else if(multi && !exit)
        {
            Multiplayer(ren, unit1T, feher, piros, font, foodT, keretT, unit2T);
        }
        SDL_RenderClear(ren);
        SDL_Delay(500);
    }

    return 0;
}
