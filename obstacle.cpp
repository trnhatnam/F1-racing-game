#include "obstacle.hh"

Obstacle::Obstacle()
{
    if (!areTexturesInitialized)
    {
        for (int i=0; i<3; i++){
            textures.push_back(sf::Texture());
        }
        if (!textures[0].loadFromFile("assets/tree.png", sf::IntRect(0, 0, 64, 64)) ||
            !textures[1].loadFromFile("assets/barrier.png", sf::IntRect(0, 0, 64, 64)) ||
            !textures[2].loadFromFile("assets/pompe2.png", sf::IntRect(0, 0, 64, 64)))
            std::cout << "Erreur chargement des textures d'obstacles" << std::endl;
        areTexturesInitialized = true;
    }
    setTexture(textures[rand() % 3]);
}