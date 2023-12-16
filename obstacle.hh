#pragma once
#include "elementDeJeu.hh"
#include "voiture.hpp"

class Obstacle: public ElementDeJeu{
    public:
        void collision(Voiture v);
};

void Obstacle::collision(Voiture v)
{
    printf("poof\n");
}