#pragma once
#include "tilemap.hh"
#include <SFML/Graphics.hpp>
#include "elementDeJeu.hh"
#include "obstacle.hh"
#include "voiture.hpp"
#include "bonus.hh"
#include <string>
#include <vector>
using namespace std;

class Jeu: public sf::Drawable, public sf::Transformable // moteur de jeu
{
    public:
    // lié aux évenments en jeu
        Jeu(int* level);
        void spawn_obstacle();
        void spawn_bonus();
        void clear();
        bool checkCollisionObs(Voiture &v);
        bool checkCollisionBonus(Voiture &v);
    
    // fonction de transformation
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void move(float offsetY);
    
    // getter
        float getPositionMap1();

    private:
        // pour simuler une map infinie, on crée 3 tilemap et on les fait défiler façon tapis roulant
        
        int* _level;
        TileMap map1;
        TileMap map2;  
        TileMap map3;

        // les vecteurs d'obstacles et bonus
        vector<Obstacle> vect_obstacles;
        vector<Bonus> vect_bonus;
        vector<Voiture> vect_voiture; // ce sont les voitures obstacles à l'utilisateur
};