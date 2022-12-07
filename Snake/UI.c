#include "debugmalloc.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#define WINDOW_HEIGHT 750
#define WINDOW_WIDTH 1025

#include "UI.h"
#include "Single.h"

void scoreRajzol(SDL_Color feher, SDL_Color piros, SDL_Renderer *ren, TTF_Font *font)
{
    int size = 0;
    int *scores = NULL;
    scores = getscores(&size);
    SDL_Surface *elemek[5];
    SDL_Texture *elemekT[5];
    SDL_Rect elemRect[5];
    if(size > 5)    size = 5;
    size++;
    for(int i = 0; i < size; i++)
    {
        char *szoveg = NULL;

        if(i != 0)
        {
            int szamlalo = scores[i - 1];
            int jegy = 0;
            if(szamlalo != 0)
            {
                while(szamlalo > 0)
                {
                    jegy++;
                    szamlalo /= 10;
                }
            }else{
                jegy = 1;
            }

            szoveg = (char*)malloc((jegy + 1) * sizeof(char));
            sprintf(szoveg, "%d", scores[i - 1]);
            elemek[i] = TTF_RenderText_Solid(font, szoveg, feher);
        }
        else
        {
            elemek[i] = TTF_RenderText_Solid(font, "Top Scores:", piros);

        }
        elemekT[i] = SDL_CreateTextureFromSurface(ren, elemek[i]);
        SDL_FreeSurface(elemek[i]);
        elemRect[i].w = elemek[i]->clip_rect.w / 2;
        elemRect[i].h = elemek[i]->clip_rect.h / 2;
        elemRect[i].x = WINDOW_WIDTH / 2 - elemRect[i].w / 2 + 350;
        elemRect[i].y = WINDOW_HEIGHT / 2 - 180 + i * 80;
        SDL_RenderCopy(ren, elemekT[i], NULL, &elemRect[i]);
        SDL_DestroyTexture(elemekT[i]);
        free(szoveg);
    }
    free(scores);

}

int menu(SDL_Renderer *ren, TTF_Font *font)
{
    char *menupontok[3] = {"Singleplayer", "2 Player Mode", "Exit"};
    SDL_Surface *elemek[3];
    SDL_Texture *elemekT[3];
    SDL_Rect elemRect[3];
    SDL_Color feher = {255,255,255}, selected = {200,200,200}, piros = {255,0,0};
    bool selectedB[3] = {false,false,false};
    int mouseX, mouseY;


    for(int i = 0; i <3; i++)
    {
        elemek[i] = TTF_RenderText_Solid(font, menupontok[i], feher);
        elemekT[i] = SDL_CreateTextureFromSurface(ren, elemek[i]);
        elemRect[i].w = elemek[i]->clip_rect.w;
        elemRect[i].h = elemek[i]->clip_rect.h;
        elemRect[i].x = WINDOW_WIDTH / 2 - elemRect[i].w / 2 - 140;
        elemRect[i].y = WINDOW_HEIGHT / 2 - 180 + i * 180;
    }

    scoreRajzol(feher, piros, ren, font);
    while(true)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                return 2;
            case SDL_MOUSEMOTION:
                mouseX = event.motion.x;
                mouseY = event.motion.y;
                for(int i = 0; i < 3; i++)
                {
                    if(mouseX >= elemRect[i].x && mouseX <= elemRect[i].x + elemRect[i].w && mouseY >= elemRect[i].y && mouseY <= elemRect[i].y + elemRect[i].h)
                    {
                        if(!selectedB[i])
                        {
                            SDL_RenderClear(ren);
                            scoreRajzol(feher, piros, ren, font);
                            selectedB[i] = true;
                            SDL_FreeSurface(elemek[i]);
                            SDL_DestroyTexture(elemekT[i]);
                            elemek[i] = TTF_RenderText_Solid(font, menupontok[i], selected);
                            elemekT[i] = SDL_CreateTextureFromSurface(ren, elemek[i]);
                        }
                    }
                    else
                    {
                        if(selectedB[i])
                        {
                            SDL_RenderClear(ren);
                            scoreRajzol(feher, piros, ren, font);
                            selectedB[i] = false;
                            SDL_FreeSurface(elemek[i]);
                            SDL_DestroyTexture(elemekT[i]);
                            elemek[i] = TTF_RenderText_Solid(font, menupontok[i], feher);
                            elemekT[i] = SDL_CreateTextureFromSurface(ren, elemek[i]);
                        }
                    }
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                for(int i = 0; i < 3; i++)
                {

                    if(mouseX >= elemRect[i].x && mouseX <= elemRect[i].x + elemRect[i].w && mouseY >= elemRect[i].y && mouseY <= elemRect[i].y + elemRect[i].h)
                    {
                        for(int j = 0; j < 3; j++)
                        {
                            SDL_FreeSurface(elemek[j]);
                            SDL_DestroyTexture(elemekT[j]);
                        }
                        return i;
                    }
                }
            }
            break;
        }
        SDL_Delay(1000/60);
        for(int i = 0; i < 3; i++)
        {
            SDL_RenderCopy(ren, elemekT[i], NULL, elemRect + i);
        }

        SDL_RenderPresent(ren);
    }
}



