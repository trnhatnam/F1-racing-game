#include "voiture.hpp"

Voiture::Voiture(float x, float y, float speed, float maxSpeed, const sf::Texture& texture)
    : _speed(speed), _maxSpeed(maxSpeed) {
    // mise en place de la texture
    this->setTexture(texture);
    // positionnement de la voiture
    this->setPosition(x, y);
    // mise a l'echelle du sprite de la voiture
    this->setScale(1.5f,1.5f);
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
    _speed += 5.0;
}

void Voiture::SpeedUp() {
    _speed += 0.01;
    if (_speed > _maxSpeed)
        _speed = _maxSpeed;
}