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
#include "Single.h"
#include "kigyo1.h"
#include "UI.h"

int *scoreSort(int *scores, int size)
{
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(scores[i] > scores[j])
            {
                int temp = scores[j];
                scores[j] = scores[i];
                scores[i] = temp;
            }
        }
    }
    return scores;
}
int *getscores(int *sizeT)
{
    FILE *fp = fopen("Scores.txt", "r");
    int size = 0;
    int *scores = NULL;
    int current = 0;
    while(!feof(fp))
    {
        fscanf(fp, "%d", &current);
        size++;
        scores = (int*)realloc(scores, size * sizeof(int));
        scores[size - 1] = current;
    }

    *sizeT = size - 1;
    fclose(fp);
    return scores;
}

void writeScores(int *scores, int size)
{
    FILE *fp = fopen("Scores.txt", "wt");

    for(int i = 0; i < size; i++)
    {
        fprintf(fp, "%d\n", scores[i]);
    }
    fclose(fp);
}

void SinglePlayer(SDL_Renderer *ren, SDL_Texture *unitT, SDL_Color feher, TTF_Font *font, SDL_Texture *foodT, SDL_Texture *keretT)
{
        int score = 0;
        Vektor vektor = {0, -1};
        Kigyoelem *eleje = NULL;
        double speed = 8;
        SDL_Rect keret[4];
        SDL_Rect food;
        bool dead = false;
        SDL_Rect scoreRect;
        SDL_Texture *scoreT;
        //előkészíti a pályát az alapvető objektumokkal(keret, kígyó, eledel)
        eleje = Lanceleje(eleje, 1);
        start(keret, &food);
        Kigyoelem *elso = NULL;
        elso = vezer(eleje);

        //A játék alapvető ciklusa, itt a zárójelben egyben a kerettel való ütközést is figyeljük
        while(elso->unit.x <= WINDOW_WIDTH - UNIT_SIZE * 2 && elso->unit.x >= UNIT_SIZE && elso->unit.y <= WINDOW_HEIGHT - UNIT_SIZE * 2 && elso->unit.y >= UNIT_SIZE)
        {
            SDL_Surface *scoreS;
            SDL_RenderClear(ren);

            SDL_Event event;
            while(SDL_PollEvent(&event))
            {
                if(event.type == SDL_KEYDOWN)
                {
                    //irány megadása
                    vektor = irany(vektor, event, 1);
                }
                if(event.type == SDL_QUIT)
                    SDL_Quit();
            }
            elso = utkozes(&dead, &food, elso, &eleje, &speed, &score);

            //A kígyú mozgása

            Kigyoelem *mozgoelem = eleje;
            while(mozgoelem != elso)
            {
                mozgoelem->unit.x = mozgoelem->kov->unit.x;
                mozgoelem->unit.y = mozgoelem->kov->unit.y;
                mozgoelem = mozgoelem->kov;
            }
            elso->unit.x += vektor.x * UNIT_SIZE;
            elso->unit.y += vektor.y * UNIT_SIZE;

            //A renderelés és delay így a játék 15 fpsel fut


            Kigyoelem *mozgo = eleje;

            SDL_RenderCopy(ren, foodT, NULL, &food);
            while(mozgo != NULL)
            {
                SDL_RenderCopy(ren, unitT, NULL, mozgo);
                mozgo = mozgo->kov;
            }
            for(int i = 0; i < 4; i++)
            {
                SDL_RenderCopy(ren, keretT, NULL, keret + i);
            }
            int szamlalo = score;
            int jegy = 0;
            while(szamlalo != 0)
            {
                jegy++;
                szamlalo /= 10;
            }
            char *scoreText = NULL;
            if(score == 0)
            {
                scoreText = (char*)malloc( 2 * sizeof(char));
            }
            else
            {
                scoreText = (char*)malloc((jegy + 1) * sizeof(char));
            }
            sprintf(scoreText, "%d", score);
            scoreS = TTF_RenderText_Solid(font, scoreText, feher);
            free(scoreText);
            scoreT = SDL_CreateTextureFromSurface(ren, scoreS);
            SDL_FreeSurface(scoreS);
            SDL_SetTextureAlphaMod(scoreT, 120);

            scoreRect.w = scoreS->clip_rect.w;

            scoreRect.h = scoreS->clip_rect.h;
            scoreRect.x = WINDOW_WIDTH / 2 - scoreRect.w / 2;

            scoreRect.y = 50;

            if(dead)
                break;
            SDL_RenderCopy(ren, scoreT, NULL, &scoreRect);
            SDL_DestroyTexture(scoreT);
            SDL_RenderPresent(ren);
            SDL_Delay(1000/speed);

        }

        int size = 0;
        int *scores = NULL;
        scores = getscores(&size);
        if(size - 1 < 10 )
        {
            size++;
            scores = (int*)realloc(scores, size * sizeof(int));
            scores[size - 1] = score;
            scores = scoreSort(scores, size);
            writeScores(scores, size);
        }
        else
        {

            if(score > scores[size - 1] )
            {
                scores[size-1] = score;
                scoreSort(scores, size);
                writeScores(scores, size);
            }
        }
        kigyoFelszabadit(eleje);
        free(scores);
}
