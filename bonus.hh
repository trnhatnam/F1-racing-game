#pragma once
#include <string>
#include <vector>
#include "elementDeJeu.hh"
using namespace std;

class Bonus: public ElementDeJeu{
    private: 
        float _valeur;
        int _typeBonus;
        bool _used;
        inline static bool areTexturesInitialized;
        inline static vector<sf::Texture> textures;
    public:
        float getValue();
        bool isUsed();
        void getUsed();
        int getTypeBonus();
        Bonus();
};