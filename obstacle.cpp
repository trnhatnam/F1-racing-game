#include "obstacle.hh"

Obstacle::Obstacle()
{
    if (!isTexturesInitialized)
    {
        for (int i=0; i<5; i++){
            texturesObstacles.push_back(sf::Texture());
        }
        if (!texturesObstacles[0].loadFromFile("assets/tree.png", sf::IntRect(0, 0, 64, 64)) ||
            !texturesObstacles[1].loadFromFile("assets/barrier.png", sf::IntRect(0, 0, 64, 64)) ||
            !texturesObstacles[2].loadFromFile("assets/pompe2.png", sf::IntRect(0, 0, 64, 64)) ||
            !texturesObstacles[3].loadFromFile("assets/pompe3.png", sf::IntRect(0, 0, 64, 64)) ||
            !texturesObstacles[4].loadFromFile("assets/pompe4.png", sf::IntRect(0, 0, 64, 64)))
            printf("Erreur chargement des textures d'obstacles");
        isTexturesInitialized = true;
    }
    setTexture(texturesObstacles[rand() % 5]);
    vitesseRelative = 0;
    // initialiser résistance et tout aléatoirement pour que ça soit plus fun
}