#pragma once
#include <string>
#include <vector>
#include "elementDeJeu.hh"
using namespace std;

class Bonus: public ElementDeJeu{
    private: 
        int _valeur;
        int _typeBonus;
        bool _used;
        inline static bool areTexturesInitialized;
        inline static sf::Texture tileset;
    public:
        int getValue() const;
        bool isUsed();
        void getUsed();
        int getTypeBonus() const;
        Bonus();
};