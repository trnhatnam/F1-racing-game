#pragma once
#include <SFML/Graphics.hpp>
class ElementDeJeu: public sf::Sprite{
    protected:
        int _longueur;
        int _largeur;
        int _resistance;
        float _x;
        float _y;
};