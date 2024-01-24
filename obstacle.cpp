#include "obstacle.hh"

Obstacle::Obstacle()
{
    if (!areTexturesInitialized)
    {
        tileset.loadFromFile("assets/obsTileset.png");
        areTexturesInitialized = true;
    }
    setTexture(tileset);
    setTextureRect(sf::IntRect((rand() % 3)*64, 0, 64,64));
}