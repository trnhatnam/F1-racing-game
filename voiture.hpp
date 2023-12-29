#pragma once
#include <SFML/Graphics.hpp>
#include "obstacle.hh"
#include "bonus.hh"

class Voiture : public Obstacle{
private:
    float _maxSpeed;
    float _speed;
    float _currentOil;
    float _maxOil;
    float _hp;
    float _maxHp;
public:
    Voiture(float x, float y, float speed, float maxSpeed, float currentOil, float maxOil, float hp, float maxHp, const sf::Texture& texture);

    float getSpeed() const;
    float getX() const;
    float getY() const;
    float getMaxSpeed() const;
    float getcurrentOil() const;
    float getMaxOil() const;
    float getHp() const;
    float getMaxHp() const;

    bool collision(Obstacle& obs);
    bool collision(Bonus& bonus);

    void startSpeedUp();
    void SpeedUp();
    void UseOfOil();
};