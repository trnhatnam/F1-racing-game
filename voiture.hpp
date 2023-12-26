#pragma once
#include <SFML/Graphics.hpp>
#include "obstacle.hh"

class Voiture : public Obstacle{
private:
    float _maxSpeed;
    float _speed;
    float _actualOil;
    float _maxOil;
public:
    Voiture(float x, float y, float speed, float maxSpeed, float actualOil, float maxOil, const sf::Texture& texture);

    float getSpeed() const;
    float getX() const;
    float getY() const;
    float getMaxSpeed() const;
    float getActualOil() const;
    float getMaxOil() const;

    void collision(Obstacle& obs);

    void startSpeedUp();
    void SpeedUp();
    void UseOfOil();
};