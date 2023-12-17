#pragma once
#include "elementDeJeu.hh"
#include "voiture.hpp"
#include <vector>
using namespace std;

class Obstacle: public ElementDeJeu{
    public:
        Obstacle();
        void collision(Voiture v);
    private:
        inline static bool isTexturesInitialized;
        inline static vector<sf::Texture> texturesObstacles;
};
