#ifndef MOZGAS_H_INCLUDED
#define MOZGAS_H_INCLUDED

//Vektor definialt valtozo
typedef struct iranyvektor
{
    int x;
    int y;
} Vektor;
//A player input alapjan visszaad egy vektorerteket
Vektor irany(Vektor vektor, SDL_Event event, int player);

#endif // MOZGAS_H_INCLUDED
