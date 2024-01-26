#include "bonus.hh"

// les bonus sont générés de façon randomisé
Bonus::Bonus(){
    if (!areTexturesInitialized){
        tileset.loadFromFile("assets/bonusTileset.png");
        areTexturesInitialized  = true;
    }

    setTexture(tileset);
    switch (rand() % 3){
        case 0: 
            _typeBonus = 0; _valeur = 1; ; setTextureRect(sf::IntRect(64, 0, 64, 64)); break;
        case 1:
            _typeBonus = 1; _valeur = 5; setTextureRect(sf::IntRect(128, 0, 64, 64)); break;
        case 2:
            _typeBonus = 2; _valeur = 5; setTextureRect(sf::IntRect(0, 0, 64, 64));
    }
}

int Bonus::getTypeBonus() const
{
    return _typeBonus;
}

int Bonus::getValue() const
{
    return _valeur;
}

bool Bonus::isUsed()
{
    return _used;
}

void Bonus::getUsed()
{
    setTextureRect(sf::IntRect(192, 0, 64, 64));
    _used = true;
}