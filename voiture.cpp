#include "voiture.hpp"
#include <iostream> 
#include <cmath>

Voiture::Voiture(float x, float y, float speed, float maxSpeed, const sf::Texture& texture)
    : _speed(speed), _maxSpeed(maxSpeed) {
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
void Voiture::startSpeedUp() {
    _speed += 10.0;
}

void Voiture::SpeedUp() {
    _speed += 0.05;
    if (_speed > _maxSpeed)
        _speed = _maxSpeed;
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