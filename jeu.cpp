#include "jeu.hpp"

Jeu::Jeu(int* level):_level(level)
{
    for (int i=0; i<3; i++)
    {
        TileMap map;
        map.load("assets/tileset.png", sf::Vector2u(64, 64), level, 15, 15);
        map.setPosition(0.f,i*960.f);
        maps.push_back(map);
    }
}

void Jeu::move(float offsetY)
{
    for (auto& map : maps)
    {
        if (map.getPosition().y >= 960.f)
            map.setPosition(0.f, -960.f + (map.getPosition().y - 960.f));
        map.move(0.f,offsetY);
    }

    for (auto& obs : vect_obstacles)
        obs.move(0.f, offsetY);

    for (auto& bon : vect_bonus)
        bon.move(0.f, offsetY);

    for (auto& v : vect_voiture) // ce sont les autres voitures
    {
        v.speedUp();
        v.move(0.f, offsetY - v.getSpeed());
    }
}
void Jeu::spawn_obstacle()
{
    if (rand() % 6 >= 3)
    {
        Voiture v(320 + (rand()%5)*64.f, -64, 0, 50, 20, 20, 3, 3, false);
        v += 5.f;
        v.setColor(sf::Color(255, 255, 200));
        vect_voiture.push_back(v);
    }
    else
    {
        Obstacle obs;
        obs.setPosition(sf::Vector2f(320.f + (rand()%5)*64.f, -64.f));
        vect_obstacles.push_back(obs);
    }
}

void Jeu::spawn_bonus()
{
    Bonus bon;
    bon.setPosition(sf::Vector2f(320.f + (rand()%5)*64.f, -64.f));
    vect_bonus.push_back(bon);
}

void Jeu::clear()
{
    for (auto iter = vect_obstacles.begin(); iter != vect_obstacles.end(); ) {
        if (iter->getPosition().y > 960.f) // obstacles hors de la map
            iter = vect_obstacles.erase(iter);
        else
            ++iter;
    }

    for (auto iter = vect_bonus.begin(); iter != vect_bonus.end(); ) {
        if (iter->getPosition().y > 960.f || iter->isUsed()) // bonus hors de la map
            iter = vect_bonus.erase(iter);
        else
            ++iter;
    }

    for (auto iter = vect_voiture.begin(); iter != vect_voiture.end(); ) {
        if (iter->getPosition().y > 960.f || iter->getPosition().y < -360.f) // voitures hors de la map
            iter = vect_voiture.erase(iter);
        else
            ++iter;
    }
}

void Jeu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    for (auto& map : maps)
        target.draw(map);
    for (auto& bon : vect_bonus)
        target.draw(bon);
    for (auto& obs : vect_obstacles)
        target.draw(obs);
    for (auto& v : vect_voiture)
        target.draw(v);
}

float Jeu::getPositionMap1(){
    return maps[0].getPosition().y;
}

bool Jeu::checkCollisionObs(Voiture &v)
{
    for (auto& obs : vect_obstacles)
        if (v.collision(obs))
            return true;
    for (auto& voi : vect_voiture)
        if (v.collision(voi))
            return true;
    return false;
}

bool Jeu::checkCollisionBonus(Voiture &v)
{
    for (auto& bonus : vect_bonus)
        if (v.collision(bonus))
            return true;
    return false;
}