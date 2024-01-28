#include "obstacle.hh"

// Constructeur de la classe Obstacle pour les obstacles fixes
Obstacle::Obstacle():valeur(1)
{
    // Chargement des images d'obstacles
    if (!areTexturesInitialized)
    {
        tileset.loadFromFile("assets/obsTileset.png");
        areTexturesInitialized = true;
    }
    setTexture(tileset);
    setTextureRect(sf::IntRect((rand() % 3)*64, 0, 64,64));
}

// Fonction accesseur de valeur de l'obstacle
int Obstacle::getValue() const
{
    return valeur;
}