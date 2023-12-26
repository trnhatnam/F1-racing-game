#pragma once
#include <SFML/Graphics.hpp>
#include "obstacle.hh"

class Voiture : public Obstacle{
private:
    float _speed;
    float _maxSpeed;

public:
    Voiture(float x, float y, float speed, float maxSpeed, const sf::Texture& texture);

    float getSpeed() const;
    float getX() const;
    float getY() const;
    float getMaxSpeed() const;

    void startSpeedUp();
    void SpeedUp();
};