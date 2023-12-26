#include "voiture.hpp"
#include <iostream> 
#include <cmath>

Voiture::Voiture(float x, float y, float speed, float maxSpeed, float actualOil, float maxOil, const sf::Texture& texture)
    : _speed(speed), _maxSpeed(maxSpeed), _actualOil(actualOil), _maxOil(maxOil) {
    // mise en place de la texture
    this->setTexture(texture);
    // positionnement de la voiture
    this->setPosition(x, y);
    // mise a l'echelle du sprite de la voiture
    //this->setScale(1.5f,1.5f);
}

float Voiture::getX() const {
    return this->getPosition().x;
}

float Voiture::getY() const {
    return this->getPosition().y;
}

float Voiture::getSpeed() const {
    return _speed;
}

float Voiture::getMaxSpeed() const {
    return _maxSpeed;
}

float Voiture::getActualOil() const {
    return _actualOil;
}

float Voiture::getMaxOil() const {
    return _maxOil;
}

void Voiture::startSpeedUp() {
    _speed += 5.0;
}

void Voiture::SpeedUp() {
    if (_actualOil > 0.0){
        _speed += 0.01;
        if (_speed > _maxSpeed)
            _speed = _maxSpeed;
    } else {
        _speed -= 0.01*sqrt(_speed*0.5);
        if (_speed < 0.0001)
            _speed = 0.0;
    }
}

void Voiture::UseOfOil() {
    if (_speed > 0.0){
        _actualOil -= 0.01*sqrt(_speed);
        if (_actualOil < 0.0)
            _actualOil = 0.0;
    } else {
        _actualOil -= 0.5;
    }
}

void Voiture::collision(Obstacle& obs)
{
    if (obs.getPosition().x == getPosition().x && 
        obs.getPosition().y < getPosition().y &&
        obs.getPosition().y + 32.f > getPosition().y)
        {
            if (_speed > 5)
                _speed = sqrt(_speed);
            else
                _speed = 0;
        }
        
}