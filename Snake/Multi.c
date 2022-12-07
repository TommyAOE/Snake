#include "debugmalloc.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#define UNIT_SIZE 25
#define WINDOW_HEIGHT 750
#define WINDOW_WIDTH 1025

#include "mozgas.h"
#include "Multi.h"
#include "kigyo1.h"

void Multiplayer(SDL_Renderer *ren, SDL_Texture *unit1T, SDL_Color feher, SDL_Color piros, TTF_Font *font, SDL_Texture *foodT, SDL_Texture *keretT, SDL_Texture *unit2T)
{

        Vektor vektor1 = {0, -1};
        Vektor vektor2 = {0, -1};
        Kigyoelem *eleje1 = NULL;
        Kigyoelem *eleje2 = NULL;
        double speed = 10;
        SDL_Rect keret[4];
        SDL_Rect food;
        bool dead1 = false, dead2 = false;
        //előkészíti a pályát az alapvető objektumokkal(keret, kígyó, eledel)
        eleje1 = Lanceleje(eleje1, 1);
        eleje2 = Lanceleje(eleje2, 2);
        start(keret, &food);
        Kigyoelem *elso1 = NULL;
        Kigyoelem *elso2 = NULL;
        elso1 = vezer(eleje1);
        elso2 = vezer(eleje2);


        //A játék alapvető ciklusa, itt a zárójelben egyben a kerettel való ütközést is figyeljük
        while(true)
        {
            SDL_Surface *deadTextS;
            SDL_Rect deadtTextR;
            SDL_Texture *deadtTextT;

            SDL_Event event;
            while(SDL_PollEvent(&event))
            {
                if(event.type == SDL_KEYDOWN)
                {
                    //irány megadása
                    vektor1 = irany(vektor1, event, 1);
                    vektor2 = irany(vektor2, event, 2);
                }
                if(event.type == SDL_QUIT)
                    SDL_Quit();
            }
            elso1 = utkozesMulti(&dead1, &food, elso1, &eleje1, 1, eleje2);
            elso2 = utkozesMulti(&dead2, &food, elso2, &eleje2, 2, eleje1);

            //A kígyú mozgása

            Kigyoelem *mozgoelem1 = eleje1;

            while(mozgoelem1 != elso1)
            {
                mozgoelem1->unit.x = mozgoelem1->kov->unit.x;
                mozgoelem1->unit.y = mozgoelem1->kov->unit.y;
                mozgoelem1 = mozgoelem1->kov;
            }
            elso1->unit.x += vektor1.x * UNIT_SIZE;
            elso1->unit.y += vektor1.y * UNIT_SIZE;
            Kigyoelem *mozgoelem2 = eleje2;
            while(mozgoelem2 != elso2)
            {

                mozgoelem2->unit.x = mozgoelem2->kov->unit.x;
                mozgoelem2->unit.y = mozgoelem2->kov->unit.y;
                mozgoelem2 = mozgoelem2->kov;
            }
            elso2->unit.x += vektor2.x * UNIT_SIZE;
            elso2->unit.y += vektor2.y * UNIT_SIZE;
            if(!dead1 && !dead2)
            {
                SDL_RenderClear(ren);
                SDL_RenderCopy(ren, foodT, NULL, &food);
                Kigyoelem *mozgo1 = eleje1;
                Kigyoelem *mozgo2= eleje2;
                while(mozgo1 != NULL)
                {
                    SDL_RenderCopy(ren, unit1T, NULL, mozgo1);
                    mozgo1 = mozgo1->kov;
                }
                while(mozgo2 != NULL)
                {
                    SDL_RenderCopy(ren, unit2T, NULL, mozgo2);
                    mozgo2 = mozgo2->kov;
                }
            }

            //A renderelés és delay így a játék 10 fpsel fut
            for(int i = 0; i < 4; i++)
            {
                SDL_RenderCopy(ren, keretT, NULL, keret + i);
            }
            if(dead1 || dead2)
            {
                if(dead1)
                {
                    deadTextS = TTF_RenderText_Solid(font, "Player 2 Won!", piros);
                }else
                {
                    deadTextS = TTF_RenderText_Solid(font, "Player 1 Won!", feher);
                }
                deadtTextR.w = deadTextS->clip_rect.w;
                deadtTextR.h = deadTextS->clip_rect.h;
                deadtTextR.x = WINDOW_WIDTH / 2 - deadtTextR.w / 2;
                deadtTextR.y = WINDOW_HEIGHT / 2 - deadtTextR.h / 2;
                deadtTextT = SDL_CreateTextureFromSurface(ren, deadTextS);
                SDL_RenderCopy(ren, deadtTextT, NULL, &deadtTextR);
                SDL_DestroyTexture(deadtTextT);
                SDL_FreeSurface(deadTextS);
                SDL_RenderPresent(ren);
                SDL_Delay(1000);
                break;
            }

            SDL_RenderPresent(ren);
            SDL_Delay(1000/speed);

        }
        kigyoFelszabadit(eleje1);
        kigyoFelszabadit(eleje2);
}
