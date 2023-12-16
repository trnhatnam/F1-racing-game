#include "jeu.hpp"
#include "obstacle.hh"
Jeu::Jeu(int* level):_level(level)
{
    if (!map1.load("tileset.png", sf::Vector2u(64, 64), level, 15, 15) ||
        !map2.load("tileset.png", sf::Vector2u(64, 64), level, 15, 15) ||
        !map3.load("tileset.png", sf::Vector2u(64, 64), level, 15, 15))
        printf("Erreur initialisation des maps\n");
    
    map1.setPosition(0.f, 0.f);
    map2.setPosition(0.f, -960.f);
    map3.setPosition(0.f, -960.f*2);
}

void Jeu::defiler(double vitesse)
{
    if (map1.getPosition().y >= 960.f)
        map1.setPosition(0.f, -960.f + (map1.getPosition().y - 960.f));
    if (map2.getPosition().y >= 960.f)
        map2.setPosition(0.f, -960.f + (map2.getPosition().y - 960.f));
    if (map3.getPosition().y >= 960.f)
        map3.setPosition(0.f, -960.f + (map3.getPosition().y - 960.f));
    
    map1.move(0.f,vitesse);
    map2.move(0.f,vitesse);
    map3.move(0.f,vitesse);

    for (auto& obs : vect_obstacles)
        obs.move(0.f, vitesse);
}
void Jeu::spawn_obstacle(sf::Texture& texture)
{
    Obstacle arbre;
    if (!texture.loadFromFile("assets/tree.png", sf::IntRect(0, 0, 64, 64)))
        printf("Problème de rendement d'un obstacle\n");
    arbre.setTexture(texture);
    arbre.setPosition(sf::Vector2f(320.f + (rand()%5)*64.f, -64.f));
    vect_obstacles.push_back(arbre);
}

void Jeu::clear()
{
    for (auto iter = vect_obstacles.begin(); iter != vect_obstacles.end(); ) {
        if (iter->getPosition().y > 960.f)
            iter = vect_obstacles.erase(iter);
        else
            ++iter;
    }
}

void Jeu::drawIn(sf::RenderWindow& window)
{
    window.draw(map1);
    window.draw(map2);
    window.draw(map3);
    for (auto obs : vect_obstacles)
        window.draw(obs);
}