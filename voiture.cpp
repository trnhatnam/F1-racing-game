#include "voiture.hpp"
#include <iostream> 
#include <cmath>

Voiture::Voiture(float x, float y, float speed, float maxSpeed, float actualOil, float maxOil, float hp, float maxHp, const sf::Texture& texture)
    : _speed(speed), _maxSpeed(maxSpeed), _actualOil(actualOil), _maxOil(maxOil), _hp(hp), _maxHp(maxHp) {
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

float Voiture::getHp() const {
    return _hp;
}

float Voiture::getMaxHp() const {
    return _maxHp;
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
    if (_speed == 0.0) {
        _actualOil -= 0.5;
    } else {
        float consumptionRate = 0.01 * sqrt(_speed);
        _actualOil -= consumptionRate;
    }
    if (_actualOil < 0.0) {
        _actualOil = 0.0;
    }
}

bool Voiture::collision(Obstacle& obs)
{
    if (obs.getPosition().x == getPosition().x && 
        obs.getPosition().y < getPosition().y &&
        obs.getPosition().y + 32.f > getPosition().y)
        {
            _hp--;
            if (_hp < 0)
                _hp = 0;
            if (_speed > 5)
                _speed = sqrt(_speed);
            else
                _speed = 0;
            return true;
        }
    return false;
}