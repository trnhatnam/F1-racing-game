#pragma once
#include <SFML/Graphics.hpp>
class ElementDeJeu: public sf::Sprite{
    protected:
        int resistance;
        float vitesseRelative; // ce sera par rapport à la voiture du joueur
};