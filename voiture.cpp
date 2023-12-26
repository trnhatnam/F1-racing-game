#include "voiture.hpp"

Voiture::Voiture(float x, float y, float speed, float maxSpeed, const sf::Texture& texture)
    : _speed(speed), _maxSpeed(maxSpeed) {
    // mise en place de la texture
    this->sprite.setTexture(texture);
    // positionnement de la voiture
    this->sprite.setPosition(x, y);
    // mise a l'echelle du sprite de la voiture
    this->sprite.setScale(1.5f,1.5f);
}

void Voiture::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= this->getTransform();
    // dessine le sprite de la voiture avec les transformations appliquées
    target.draw(this->sprite, states);
}

float Voiture::getX() const {
    return this->sprite.getPosition().x;
}

float Voiture::getY() const {
    return this->sprite.getPosition().y;
}

float Voiture::getSpeed() const {
    return this->_speed;
}

float Voiture::getMaxSpeed() const {
    return this->_maxSpeed;
}

void Voiture::move(float offsetX, float offsetY) {
    this->sprite.move(offsetX, offsetY);
}

void Voiture::startSpeedUp() {
    this->_speed += 5.0;
}

void Voiture::SpeedUp() {
    this->_speed += 0.01;
    if (this->_speed > this->_maxSpeed)
        this->_speed = this->_maxSpeed;
}