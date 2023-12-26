#include "jeu.hpp"


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

void Jeu::move(float offsetY)
{
    if (map1.getPosition().y >= 960.f)
        map1.setPosition(0.f, -960.f + (map1.getPosition().y - 960.f));
    if (map2.getPosition().y >= 960.f)
        map2.setPosition(0.f, -960.f + (map2.getPosition().y - 960.f));
    if (map3.getPosition().y >= 960.f)
        map3.setPosition(0.f, -960.f + (map3.getPosition().y - 960.f));
    
    map1.move(0.f,offsetY);
    map2.move(0.f,offsetY);
    map3.move(0.f,offsetY);

    for (auto& obs : vect_obstacles)
        obs.move(0.f, offsetY);
}
void Jeu::spawn_obstacle()
{
    Obstacle obs;
    obs.setPosition(sf::Vector2f(320.f + (rand()%5)*64.f, -64.f));
    vect_obstacles.push_back(obs);
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

void Jeu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(map1);
    target.draw(map2);
    target.draw(map3);
    for (auto obs : vect_obstacles)
        target.draw(obs);
}

float Jeu::getPositionMap1(){
    return map1.getPosition().y;
}

void Jeu::checkCollision(Voiture &v)
{
    for (auto& obs : vect_obstacles)
        v.collision(obs);
}