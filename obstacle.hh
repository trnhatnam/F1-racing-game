#pragma once
#include "elementDeJeu.hh"
#include <vector>
using namespace std;

class Obstacle: public ElementDeJeu{
    public:
        Obstacle();
    private:
        inline static bool isTexturesInitialized;
        inline static vector<sf::Texture> texturesObstacles;
        
};
