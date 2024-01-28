#pragma once
#include <string>
#include <vector>
#include "elementDeJeu.hh"
using namespace std;

class Bonus: public ElementDeJeu{
    private: 
        int _valeur;        // Valeur (apport) du bonus
        int _typeBonus;     // Type de bonus
        bool _used;         // Etat du bonus
        inline static bool areTexturesInitialized;
        inline static sf::Texture tileset;
    public:
        // Méthodes de la classe Bonus
        int getValue() const;
        bool isUsed();
        void getUsed();
        int getTypeBonus() const;

        // Constructeur de la classe Bonus
        Bonus();
};