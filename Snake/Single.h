#ifndef SINGLE_H_INCLUDED
#define SINGLE_H_INCLUDED

//A single player fofuggvenye
void SinglePlayer(SDL_Renderer *ren, SDL_Texture *unitT, SDL_Color feher, TTF_Font *font, SDL_Texture *foodT, SDL_Texture *keretT);
//Rendezi a tombot amit megkap
int *scoreSort(int *scores, int size);
//Beolvassa a pontokat a Scores.txt-bol
int *getscores(int *sizeT);
//Kiirja a pontokat a Scorest.txtbe
void writeScores(int *scores, int size);



#endif // SINGLE_H_INCLUDED
