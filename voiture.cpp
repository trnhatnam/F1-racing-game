#include "voiture.hpp"
#include <iostream> 
#include <cmath>

Voiture::Voiture(float x, float y, float speed, float maxSpeed, float fuel, float maxFuel, float hp, float maxHp, bool user)
    : _speed(speed), _maxSpeed(maxSpeed), _fuel(fuel), _maxFuel(maxFuel), _hp(hp), _maxHp(maxHp), _user(user) {

    // les textures sont déjà initalisées car le constructeur par défaut d'obstacle est appelé
    if(user){
        setTextureRect(sf::IntRect(192,0,64,64)); 
        setPosition(x, y);
        valeur = 0;
    } else {
        setTextureRect(sf::IntRect(256+64*(rand()%4),0,64,64)); 
        setPosition(x, y);
        valeur = 2;
    }
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

// void Voiture::startspeedUp() {
//     _speed += 5.0;
// }

void Voiture::speedUp() {
    if (_fuel > 0.0 && getPosition().x >= 320 && getPosition().x <= 576){ 
        _speed += 0.01*((10/_speed) + 1);
        if (_speed > _maxSpeed)
            _speed = _maxSpeed;
    } else { // perte de vitese due au manque de carburant ou lorsque la voitrue est sur la piste de sable
        _speed -= 0.01*sqrt(_speed*0.5);
        if (_speed < 0.0001)
            _speed = 0.0;
    }
}

void Voiture::useFuel() {
    if (_speed == 0.0) {
        _fuel -= 0.5;
    } else {
        float consumptionRate = 1e-3 * _speed;
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
        obs.getPosition().y + 48.f > getPosition().y)
        {
            _hp -= obs.getValue();
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
        bon.getPosition().y + 48.f > getPosition().y)
        {
            int typeBonus = bon.getTypeBonus();
            int valeur = bon.getValue();
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

// Fonction de déplacement à Gauche
void Voiture::move_left(float minX, bool& leftPressed, std::chrono::steady_clock::time_point& lastMoveTime) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (this->getX() > minX) {
            if (!leftPressed) {
                // déplacement d'une tuile vers la gauche du véhicule
                this->move(-64.f, 0.f);
                // déplacement autorisé
                leftPressed = true;
                // mise à jour le temps du dernier déplacement
                lastMoveTime = std::chrono::steady_clock::now();
            }

            std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
            std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastMoveTime);

            // on attend un quart de seconde (0.25 s) avant chaque déplacement
            if (duration.count() >= 250 && this->getX() > minX) {
                // déplacement d'une tuile vers la gauche du véhicule
                this->move(-64.f, 0.f);
                // mise à jour le temps du dernier déplacement
                lastMoveTime = std::chrono::steady_clock::now();
            }
        }
    }
}

void Voiture::move_right(float maxX, bool& rightPressed, std::chrono::steady_clock::time_point& lastMoveTime) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (this->getX() < maxX) {
            if (!rightPressed) {
                // déplacement d'une tuile vers la droite du véhicule
                this->move(64.f, 0.f);
                // déplacement autorisé
                rightPressed = true;
                // mise à jour le temps du dernier déplacement
                lastMoveTime = std::chrono::steady_clock::now();
            }

            std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
            std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastMoveTime);

            // on attend un quart de seconde (0.25 s) avant chaque déplacement
            if (duration.count() >= 250 && this->getX() < maxX) {
                // déplacement d'une tuile vers la droite du véhicule
                this->move(64.f, 0.f);
                // mise à jour le temps du dernier déplacement
                lastMoveTime = std::chrono::steady_clock::now();
            }
        }
    }
}

int Voiture::getValue() const
{
    return valeur;
}


Voiture& operator+=(Voiture& v, float offsetY)
{
    v._speed += offsetY;
    return v;
}