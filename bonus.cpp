#include "bonus.hh"

// les bonus sont générés de façon randomisé
Bonus::Bonus(){
    if (!areTexturesInitialized){
        for (int i=0; i<4; i++)
        {
            textures.push_back(sf::Texture());
        }
        if (!textures[0].loadFromFile("assets/heart.png", sf::IntRect(0, 0, 64, 64)) ||
            !textures[1].loadFromFile("assets/fuel.png", sf::IntRect(0, 0, 64, 64)) ||
            !textures[2].loadFromFile("assets/boost.png", sf::IntRect(0, 0, 64, 64)) ||
            !textures[3].loadFromFile("assets/vide.png", sf::IntRect(0, 0, 64, 64)))
            std::cout << "Erreur chargement des textures des bonus" << std::endl;
        areTexturesInitialized  = true;
    }
    switch (rand() % 3){
        case 0: 
            _typeBonus = 0; _valeur = 1; setTexture(textures[0]); break;
        case 1:
            _typeBonus = 1; _valeur = 10; setTexture(textures[1]); break;
        case 2:
            _typeBonus = 2; _valeur = 10; setTexture(textures[2]);
    }
}

int Bonus::getTypeBonus()
{
    return _typeBonus;
}

float Bonus::getValue()
{
    return _valeur;
}

bool Bonus::isUsed()
{
    return _used;
}

void Bonus::getUsed()
{
    setTexture(textures[3]);
    _used = true;
}