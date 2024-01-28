#pragma once
#include <SFML/Graphics.hpp>
#include "obstacle.hh"
#include "bonus.hh"
#include <chrono>
#include "time.h"

class Voiture : public Obstacle{
private:
    // Attributs de la classe Voiture
    float _speed;           // Vitesse actuelle (de la voiture)
    float _maxSpeed;        // Vitesse Max (de la voiture)
    float _fuel;            // Carburant actuel
    float _maxFuel;         // Carburant Max
    float _hp;              // Points de vie 
    float _maxHp;           // Max points de vie
    bool _user;             // Booléen pour déterminer la voiture du joueur
public:
    // Constructeur de la classe voiture
    Voiture(float x, float y, float speed, float maxSpeed, float fuel, float maxFuel, float hp, float maxHp, bool user);
    friend Voiture& operator+=(Voiture& v, float offsetY);

    // Méthodes de la classe voiture
    float getSpeed() const;
    float getX() const;
    float getY() const;
    float getMaxSpeed() const;
    float getfuel() const;
    float getMaxFuel() const;
    float getHp() const;
    float getMaxHp() const;
    int getValue() const;
    bool getUser() const;

    bool collision(Obstacle& obs);
    bool collision(Bonus& bonus);

    //void startspeedUp();
    void speedUp();
    void useFuel();
    void move_left(float minX, bool& leftPressed, std::chrono::steady_clock::time_point& lastMoveTime);
    void move_right(float maxX, bool& rightPressed, std::chrono::steady_clock::time_point& lastMoveTime);
};