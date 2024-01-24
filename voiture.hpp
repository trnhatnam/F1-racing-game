#pragma once
#include <SFML/Graphics.hpp>
#include "obstacle.hh"
#include "bonus.hh"
#include <chrono>
#include "time.h"

class Voiture : public Obstacle{
private:
    float _maxSpeed;
    float _speed;
    float _fuel;
    float _maxFuel;
    float _hp;
    float _maxHp;
public:
    Voiture(float x, float y, float speed, float maxSpeed, float fuel, float maxFuel, float hp, float maxHp);

    float getSpeed() const;
    float getX() const;
    float getY() const;
    float getMaxSpeed() const;
    float getfuel() const;
    float getMaxFuel() const;
    float getHp() const;
    float getMaxHp() const;

    bool collision(Obstacle& obs);
    bool collision(Bonus& bonus);

    void startspeedUp();
    void speedUp();
    void useFuel();
    void move_left(float minX, bool& leftPressed, std::chrono::steady_clock::time_point& lastMoveTime);
    void move_right(float maxX, bool& rightPressed, std::chrono::steady_clock::time_point& lastMoveTime);
};