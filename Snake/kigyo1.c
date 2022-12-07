#include "debugmalloc.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#define UNIT_SIZE 25
#define START_SIZE 5
#define WINDOW_HEIGHT 750
#define WINDOW_WIDTH 1025


#include "kigyo1.h"


int random(int min, int max)
{
    return rand() % (max - min) + min;
}
void kigyoFelszabadit(Kigyoelem *eleje)
{
    Kigyoelem *mozgo = eleje;
    while(mozgo != NULL)
    {
        Kigyoelem *kov = mozgo->kov;
        free(mozgo);
        mozgo = kov;
    }
}

Kigyoelem *vezer(Kigyoelem *eleje)
{
    Kigyoelem *mozgo = eleje;

    while(mozgo->kov != NULL)
    {
        mozgo = mozgo->kov;
    }
    eleje = mozgo;

    return eleje;
}

Kigyoelem *kigyoEpites(Kigyoelem *eleje, int Player)
{
    Kigyoelem *uj;
    int meret = 0;
    uj = (Kigyoelem*) malloc(sizeof(Kigyoelem));
    Kigyoelem *mozgo = eleje;
    while(mozgo != NULL)
    {
        meret++;
        mozgo = mozgo->kov;
    }
    if(eleje == NULL){
        if(Player == 1)
        {
            uj->unit.y = ((WINDOW_HEIGHT) / (UNIT_SIZE * 2)) * UNIT_SIZE;
            uj->unit.x = (WINDOW_WIDTH) / 2 + UNIT_SIZE / 2 + 1;
            uj->unit.w = UNIT_SIZE;
            uj->unit.h = UNIT_SIZE;
            eleje = uj;
            eleje->kov = NULL;
        }
        else{
            uj->unit.y = ((WINDOW_HEIGHT) / (UNIT_SIZE * 2)) * UNIT_SIZE;
            uj->unit.x = (WINDOW_WIDTH) / 2 + UNIT_SIZE / 2 - 3 * UNIT_SIZE + 1;
            uj->unit.w = UNIT_SIZE;
            uj->unit.h = UNIT_SIZE;
            eleje = uj;
            eleje->kov = NULL;
        }
    }

    else if (meret < START_SIZE){
        uj->kov = eleje;
        uj->unit.x = uj->kov->unit.x;

        uj->unit.y = uj->kov->unit.y + UNIT_SIZE;
        uj->unit.w = UNIT_SIZE;
        uj->unit.h = UNIT_SIZE;

    }
    else{

        uj->kov = eleje;

        uj->unit.w = UNIT_SIZE;
        uj->unit.h = UNIT_SIZE;
        uj->unit.x = uj->kov->unit.x;
        uj->unit.y = uj->kov->unit.y;
        meret = 0;
        mozgo = uj;
        while(mozgo != NULL)
        {
            meret++;
            mozgo = mozgo->kov;
        }
    }
    return uj;
}
start(SDL_Rect *keret, SDL_Rect *food)
{
    for(int i = 0; i < 4; i++)
    {
        switch(i)
        {
        case 0:
            keret[i].w = WINDOW_WIDTH;
            keret[i].h = UNIT_SIZE;
            keret[i].x = 0;
            keret[i].y = 0;
            break;
        case 1:
            keret[i].w = UNIT_SIZE;
            keret[i].h = WINDOW_HEIGHT;
            keret[i].x = 0;
            keret[i].y = 0;
            break;
        case 2:
            keret[i].w = WINDOW_WIDTH;
            keret[i].h = UNIT_SIZE;
            keret[i].x = 0;
            keret[i].y = WINDOW_HEIGHT - UNIT_SIZE;;
            break;
        case 3:
            keret[i].w = UNIT_SIZE;
            keret[i].h = WINDOW_HEIGHT;
            keret[i].x = WINDOW_WIDTH - UNIT_SIZE;
            keret[i].y = 0;
            break;
        }
    }
    food->w = UNIT_SIZE;
    food->h = UNIT_SIZE;
    food->x = random(1, WINDOW_WIDTH/UNIT_SIZE - 1) * UNIT_SIZE;
    food->y = random(1, WINDOW_HEIGHT/UNIT_SIZE - 1) * UNIT_SIZE;


}
Kigyoelem *Lanceleje(Kigyoelem *eleje, int player)
{
    for(int i = 0; i < START_SIZE; i++)
    {
        eleje = kigyoEpites(eleje, player);
    }
    return eleje;
}
Kigyoelem *utkozes(bool *dead, SDL_Rect *food, Kigyoelem *elso, Kigyoelem **eleje, double *speed, int *score)
{
    double speedI = *speed;
    int scoreT = *score;

    Kigyoelem *elejeI = *eleje;
    //eledellel való ütközés
    if(elso->unit.x == food->x && elso->unit.y == food->y)
    {

        //random függvény használatával új poyíciót ad meg az eledelnek
        food->x = random(1, WINDOW_WIDTH/UNIT_SIZE - 1) * UNIT_SIZE;
        food->y = random(1, WINDOW_HEIGHT/UNIT_SIZE - 1) * UNIT_SIZE;

        elejeI = kigyoEpites(*eleje, 1);
        elso = vezer(*eleje);
        speedI += 0.25;

        scoreT++;
        *score = scoreT;
    }
    *speed = speedI;
    //A kígyú saját magával való ütközése
    Kigyoelem *mozgo = elejeI;
    while(mozgo->kov != elso)
    {
        if(mozgo->unit.x == elso->unit.x && mozgo->unit.y == elso->unit.y)
        {
            *dead = true;
        }
        mozgo = mozgo->kov;
    }
    *eleje = elejeI;
    return elso;
}
Kigyoelem *utkozesMulti(bool *dead, SDL_Rect *food, Kigyoelem *elso, Kigyoelem **eleje, int player, Kigyoelem *masik)
{
    Kigyoelem *elejeI = *eleje;
    //eledellel való ütközés
    if(elso->unit.x == food->x && elso->unit.y == food->y)
    {

        //random függvény használatával új poyíciót ad meg az eledelnek
        food->x = random(1, WINDOW_WIDTH/UNIT_SIZE - 1) * UNIT_SIZE;
        food->y = random(1, WINDOW_HEIGHT/UNIT_SIZE - 1) * UNIT_SIZE;

        elejeI = kigyoEpites(*eleje, player);
        elso = vezer(*eleje);
    }
    //A kígyú saját magával való ütközése
    Kigyoelem *mozgo = elejeI;
    while(mozgo->kov != elso)
    {
        if(mozgo->unit.x == elso->unit.x && mozgo->unit.y == elso->unit.y)
        {
            *dead = true;
        }
        mozgo = mozgo->kov;
    }
    mozgo = masik;
    while(mozgo->kov != NULL)
    {
        if(mozgo->unit.x == elso->unit.x && mozgo->unit.y == elso->unit.y)
        {
            *dead = true;
        }
        mozgo = mozgo->kov;
    }
    if(elso->unit.x > WINDOW_WIDTH - UNIT_SIZE * 2 || elso->unit.x < UNIT_SIZE || elso->unit.y > WINDOW_HEIGHT - UNIT_SIZE * 2 || elso->unit.y < UNIT_SIZE)
    {
        *dead = true;
    }
    *eleje = elejeI;
    return elso;
}
