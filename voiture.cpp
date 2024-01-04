#include "voiture.hpp"
#include <iostream> 
#include <cmath>

Voiture::Voiture(float x, float y, float speed, float maxSpeed, float fuel, float maxFuel, float hp, float maxHp)
    : _speed(speed), _maxSpeed(maxSpeed), _fuel(fuel), _maxFuel(maxFuel), _hp(hp), _maxHp(maxHp) {

    if(!carTexture.loadFromFile("assets/voiture.png")){
        std::cerr << "Erreur lors du chargement de l'image de la voiture" << std::endl;
        EXIT_FAILURE;
    }
    setTexture(carTexture);
    setPosition(x, y);
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

float Voiture::getfuel() const {
    return _fuel;
}

float Voiture::getMaxFuel() const {
    return _maxFuel;
}

float Voiture::getHp() const {
    return _hp;
}

float Voiture::getMaxHp() const {
    return _maxHp;
}

void Voiture::startspeedUp() {
    _speed += 5.0;
}

void Voiture::speedUp() {
    if (_fuel > 0.0){
        _speed += 0.01;
        if (_speed > _maxSpeed)
            _speed = _maxSpeed;
    } else { // perte de vitese due au manque de carburant
        _speed -= 0.01*sqrt(_speed*0.5);
        if (_speed < 0.0001)
            _speed = 0.0;
    }
}

void Voiture::useFuel() {
    if (_speed == 0.0) {
        _fuel -= 0.5;
    } else {
        float consumptionRate = 0.005 * sqrt(_speed);
        _fuel -= consumptionRate;
    }
    if (_fuel < 0.0) {
        _fuel = 0.0;
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
            int typeBonus = bon.getTypeBonus();
            float valeur = bon.getValue();
            if (typeBonus == 0 && _hp < _maxHp)
                _hp += valeur;
            if (typeBonus == 1)
                _fuel += (_fuel + valeur >= _maxFuel) ? (_maxFuel - _fuel) : valeur;
            if (typeBonus == 2)
                _speed += (_speed + valeur >= _maxSpeed) ? (_maxSpeed - _speed) : valeur;
            bon.getUsed();
        }
    return false;
}