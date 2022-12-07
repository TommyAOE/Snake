#ifndef KIGYO1_H_INCLUDED
#define KIGYO1_H_INCLUDED

//A kigyo lancoltlistaja
typedef struct KigyoElem
{
    SDL_Rect unit;
    struct KigyoElem *kov;
} Kigyoelem;
// Egy random erteket ad vissza 2 szam kozott
int random(int min, int max);
// felszabaditja a kigyo szamara lefoglalt memoriat
void kigyoFelszabadit(Kigyoelem *eleje);
//megadja a fejet a kigyonak
Kigyoelem *vezer(Kigyoelem *eleje);
//Ez epiti fel a kigyot, a Player parameter a pozicio megadasahoz kell
Kigyoelem *kigyoEpites(Kigyoelem *eleje, int Player);
//elokesziti a palyat
void start(SDL_Rect *keret, SDL_Rect *food);
//megadja a lancolt lista elejet
Kigyoelem *Lanceleje(Kigyoelem *eleje, int player);
//Single playerben ez figyeli az utkozest(kigyo, keret, eledel)
Kigyoelem *utkozes(bool *dead, SDL_Rect *food, Kigyoelem *elso, Kigyoelem **eleje, double *speed, int *score);
//2 player modban ez figyeli az utkozest(kigyo1, kigyo2, keret, eledel)
Kigyoelem *utkozesMulti(bool *dead, SDL_Rect *food, Kigyoelem *elso, Kigyoelem **eleje, int player, Kigyoelem *masik);
#endif // KIGYO1_H_INCLUDED
