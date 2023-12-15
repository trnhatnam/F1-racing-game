#include "voiture.hpp"

Voiture::Voiture(float x, float y, float speed, float maxSpeed) : _x(x), _y(y), _speed(speed), _maxSpeed(maxSpeed) {}

float Voiture::getX() const {
    return _x;
}

float Voiture::getY() const {
    return _y;
}

float Voiture::getSpeed() const {
    return _speed;
}

float Voiture::getMaxSpeed() const {
    return _maxSpeed;
}

void Voiture::move(float sideStep) {
    _x += sideStep;
}

void Voiture::startSpeedUp() {
    _speed += 5.0;
}

void Voiture::SpeedUp(){
    _speed += 0.01;
    if(_speed > _maxSpeed)
        _speed = _maxSpeed;
}