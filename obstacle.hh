#pragma once
#include "elementDeJeu.hh"
#include <vector>
using namespace std;

class Obstacle: public ElementDeJeu{
    public:
        Obstacle();
    private:
        inline static bool areTexturesInitialized;
        inline static sf::Texture tileset;
};
