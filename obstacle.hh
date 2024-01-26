#pragma once
#include "elementDeJeu.hh"
#include <vector>
using namespace std;

class Obstacle: public ElementDeJeu{
    public:
        Obstacle();
        int getValue() const;
    private:
        inline static bool areTexturesInitialized;
        inline static sf::Texture tileset;
    protected:
        int valeur;
};
