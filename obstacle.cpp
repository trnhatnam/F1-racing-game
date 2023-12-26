#include "obstacle.hh"

void Obstacle::collision(Obstacle& v)
{

}

Obstacle::Obstacle()
{
    if (!isTexturesInitialized)
    {
        for (int i=0; i<2; i++){
            texturesObstacles.push_back(sf::Texture());
        }
        if (!texturesObstacles[0].loadFromFile("assets/tree.png", sf::IntRect(0, 0, 64, 64)) ||
            !texturesObstacles[1].loadFromFile("assets/barrier.png", sf::IntRect(0, 0, 64, 64)))
            printf("Erreur chargement des textures d'obstacles");
        isTexturesInitialized = true;
    }
    this->setTexture(texturesObstacles[rand() % 2]);
    vitesseRelative = 0;
    // initialiser résistance et tout aléatoirement pour que ça soit plus fun
}