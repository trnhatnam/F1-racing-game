#include "voiture.hpp"
#include <iostream> 
#include <cmath>

Voiture::Voiture(float x, float y, float speed, float maxSpeed, float currentOil, float maxOil, float hp, float maxHp, const sf::Texture& texture)
    : _speed(speed), _maxSpeed(maxSpeed), _currentOil(currentOil), _maxOil(maxOil), _hp(hp), _maxHp(maxHp) {
    // mise en place de la texture
    this->setTexture(texture);
    // positionnement de la voiture
    this->setPosition(x, y);
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

float Voiture::getcurrentOil() const {
    return _currentOil;
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
    if (_currentOil > 0.0){
        _speed += 0.01;
        if (_speed > _maxSpeed)
            _speed = _maxSpeed;
    } else { // perte de vitese due au manque de carburant
        _speed -= 0.01*sqrt(_speed*0.5);
        if (_speed < 0.0001)
            _speed = 0.0;
    }
}

void Voiture::UseOfOil() {
    if (_speed == 0.0) {
        _currentOil -= 0.5;
    } else {
        float consumptionRate = 0.001 * sqrt(_speed);
        _currentOil -= consumptionRate;
    }
    if (_currentOil < 0.0) {
        _currentOil = 0.0;
    }
}

bool Voiture::collision(Obstacle& obs)
{
    // La voiture collide avec un obstacle
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

bool Voiture::collision(Bonus& bon)
{
    // La voiture collide avec un bonus
    if (bon.getPosition().x == getPosition().x && 
        bon.getPosition().y < getPosition().y &&
        bon.getPosition().y + 32.f > getPosition().y)
        {
            std::string typeBonus = bon.getTypeBonus();
            float valeur = bon.getValue();
            if (typeBonus == "life" && _hp < _maxHp)
                _hp += valeur;
            if (typeBonus == "oil")
                _currentOil += (_currentOil + valeur >= _maxOil) ? (_maxOil - _currentOil) : valeur;
            if (typeBonus == "boost")
                _speed += (_speed + valeur >= _maxSpeed) ? (_maxSpeed - _speed) : valeur;
        }
    return false;
}