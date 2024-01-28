#include "voiture.hpp"
#include <iostream> 
#include <cmath>

// Constructeur de la classe Voiture
Voiture::Voiture(float x, float y, float speed, float maxSpeed, float fuel, float maxFuel, float hp, float maxHp, bool user)
    : _speed(speed), _maxSpeed(maxSpeed), _fuel(fuel), _maxFuel(maxFuel), _hp(hp), _maxHp(maxHp), _user(user) {

    // les textures sont déjà initalisées car le constructeur par défaut d'obstacle est appelé
    if(user){           // Voiture du joueur
        setTextureRect(sf::IntRect(192,0,64,64));   // Texture de la voiture joueur 
        setPosition(x, y);                          // Position de la voiture
        valeur = 0;
    } else {            // Voiture obstacle
        setTextureRect(sf::IntRect(256+64*(rand()%4),0,64,64));     // Texture des voitures obstacles
        setPosition(x, y);                                          // Position de la voiture
        valeur = 2;
    }
}

// Fonction accesseur de position X
float Voiture::getX() const {
    return this->getPosition().x;
}

// Fonction accesseur de position Y
float Voiture::getY() const {
    return this->getPosition().y;
}

// Fonction accesseur de la vitesse actuelle
float Voiture::getSpeed() const {
    return _speed;
}

// Fonction accesseur de la vitesse Max de la voiture
float Voiture::getMaxSpeed() const {
    return _maxSpeed;
}

// Fonction accesseur du carburant actuel
float Voiture::getfuel() const {
    return _fuel;
}

// Fonction accesseur du max de carburant
float Voiture::getMaxFuel() const {
    return _maxFuel;
}

// Fonction accesseur des hp actuels
float Voiture::getHp() const {
    return _hp;
}

// Fonction accesseur du max d'hp
float Voiture::getMaxHp() const {
    return _maxHp;
}

// void Voiture::startspeedUp() {
//     _speed += 5.0;
// }

// Fonction de vitesse de la voiture
void Voiture::speedUp() {
    // Augmentation de la vitesse 
    if (_fuel > 0.0 && getPosition().x >= 320 && getPosition().x <= 576){ 
        _speed += 0.01*((10/_speed) + 1);
        if (_speed > _maxSpeed)     // Vitesse Max de la voiture
            _speed = _maxSpeed;
    } else { // perte de vitese due au manque de carburant ou lorsque la voitrue est sur la piste de sable
        _speed -= 0.01*sqrt(_speed*0.5);
        if (_speed < 0.0001)
            _speed = 0.0;
    }
}

// Fonction de consommation du carburant
void Voiture::useFuel() {
    // Consommation à l'arrêt
    if (_speed == 0.0) {
        _fuel -= 0.5;
    } else {        // Consommation selon la vitesse de la voiture
        float consumptionRate = 1e-3 * _speed;
        _fuel -= consumptionRate;
    }
    if (_fuel < 0.0) {  // Carburant vide
        _fuel = 0.0;
    }
}

// Fonction d'activation de l'obstacle en contact avec la voiture
bool Voiture::collision(Obstacle& obs)
{
    // La voiture collide avec un obstacle
    if (obs.getPosition().x == getPosition().x && 
        obs.getPosition().y < getPosition().y &&
        obs.getPosition().y + 48.f > getPosition().y)
        {
            _hp -= obs.getValue();          // Perte de points de vie
            if (_hp < 0)                    // Seuil de valeur des hp
                _hp = 0;
            if (_speed > 5)                 // Diminution de la vitesse après collision
                _speed = sqrt(_speed);
            else                            // Arrêt de la voiture
                _speed = 0;
            return true;
        }
    return false;
}

// Fonction permettant l'activation des bonus étant en contact avec la voiture
bool Voiture::collision(Bonus& bon)
{
    // La voiture collide avec un bonus
    if (bon.getPosition().x == getPosition().x && 
        bon.getPosition().y < getPosition().y &&
        bon.getPosition().y + 48.f > getPosition().y)
        {
            int typeBonus = bon.getTypeBonus();         // Type de bonus récupéré
            int valeur = bon.getValue();                // Valeur du bonus
            if (typeBonus == 0 && _hp < _maxHp)         // Bonus hp
                _hp += valeur;
            if (typeBonus == 1)                         // Bonus carburant
                _fuel += (_fuel + valeur >= _maxFuel) ? (_maxFuel - _fuel) : valeur;
            if (typeBonus == 2)                         // Bonus vitesse
                _speed += (_speed + valeur >= _maxSpeed) ? (_maxSpeed - _speed) : valeur;
            bon.getUsed();      // Bonus utilsé
        }
    return false;
}

// Fonction de déplacement de la voiture à Gauche
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

// Fonction de dépalcement de la voiture à droite
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

// Fonction accesseur de la valeur
int Voiture::getValue() const
{
    return valeur;
}

// Fonction opérateur pour initialiser la vitesse de la voiture
Voiture& operator+=(Voiture& v, float offsetY)
{
    v._speed += offsetY;
    return v;
}