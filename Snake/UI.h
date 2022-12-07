#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

//Kirajzolja az 5 legmagasabb pontszamot es ele hogy top scores
void scoreRajzol(SDL_Color feher, SDL_Color piros, SDL_Renderer *ren, TTF_Font *font);
//kirajzolja a menut, itt van meghivva a scoreRajzol fv is
int menu(SDL_Renderer *ren, TTF_Font *font);





#endif // UI_H_INCLUDED
