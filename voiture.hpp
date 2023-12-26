#pragma once
#include <SFML/Graphics.hpp>
#include "obstacle.hh"

class Voiture : public Obstacle{
private:
    float _maxSpeed;
    float _speed;
public:
    Voiture(float x, float y, float speed, float maxSpeed, const sf::Texture& texture);

    float getSpeed() const;
    float getX() const;
    float getY() const;
    float getMaxSpeed() const;

    void collision(Obstacle& obs);

    void startSpeedUp();
    void SpeedUp();
};