#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class ElementDeJeu: public sf::Sprite
{
    public:
        // pour les bonus, valeur = bonus sur la voiture
        // pour les obstacles, valeur = dégats si on tape dessus
        virtual int getValue() const = 0;
};
