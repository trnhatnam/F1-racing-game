#include "voiture.hpp"

Voiture::Voiture(float x, float y, float speed, float maxSpeed, const sf::Texture& texture)
    : _speed(speed), _maxSpeed(maxSpeed) {
    // mise en place de la texture
    sprite.setTexture(texture);
    // positionnement de la voiture
    sprite.setPosition(x, y);
    // mise a l'echelle du sprite de la voiture
    sprite.setScale(1.5f,1.5f);
}

void Voiture::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    // dessine le sprite de la voiture avec les transformations appliquées
    target.draw(sprite, states);
}

float Voiture::getX() const {
    return sprite.getPosition().x;
}

float Voiture::getY() const {
    return sprite.getPosition().y;
}

float Voiture::getSpeed() const {
    return _speed;
}

float Voiture::getMaxSpeed() const {
    return _maxSpeed;
}

void Voiture::move(float offsetX, float offsetY) {
    sprite.move(offsetX, offsetY);
}

void Voiture::startSpeedUp() {
    _speed += 5.0;
}

void Voiture::SpeedUp() {
    _speed += 0.01;
    if (_speed > _maxSpeed)
        _speed = _maxSpeed;
}