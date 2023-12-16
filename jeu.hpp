#pragma once
#include "tilemap.hh"
#include <SFML/Graphics.hpp>
#include "elementDeJeu.hh"
#include <string>
#include <vector>
using namespace std;

class Jeu
{
    public:
        Jeu(int* level);
        void defiler(double vitesse);
        void spawn_obstacle(sf::Texture& arbre);
        void spawn_bonus();
        void clear();
        void drawIn(sf::RenderWindow& window);
        TileMap& getMap1(){return map1;};
        TileMap& getMap2(){return map2;};
        TileMap& getMap3(){return map3;};

    private:
        // pour simuler une map infinie, on crée 3 tilemap et on les fait défiler façon tapis roulant
        int* _level;
        TileMap map1;
        TileMap map2;  
        TileMap map3;
        vector<ElementDeJeu> vect_obstacles;
        vector<ElementDeJeu> vect_bonus;    
};