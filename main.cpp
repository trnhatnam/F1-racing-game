#include <SFML/Graphics.hpp>
#include "tilemap.hh"
#include "jeu.hpp"
#include <stdlib.h>
#include <time.h>

int main()
{
    // on crée la fenêtre
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(960, 960), "Tilemap");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);
    // on définit le niveau à l'aide de numéro de tuiles
    int level[] =
    {
        2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
        2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
        2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
        2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
        2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
        2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
        2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
        2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
        2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
        2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
        2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
        2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
        2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
        2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
        2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
    };

    // on crée la tilemap avec le niveau précédemment défini
    // pour simuler une tilemap infini, on crée 3 tilemap
    Jeu jeu(level); 

    // sprite
    sf::Sprite voiture;
    sf::Texture textureVoiture;
    if (!textureVoiture.loadFromFile("assets/voiture.png", sf::IntRect(0, 0, 64, 64)))
        return -1;
    voiture.setTexture(textureVoiture);
    voiture.setPosition(sf::Vector2f(320.f, 600.f));
    float vitesse = 10.f;

    sf::Clock clock;
    bool tree = true;
    sf::Texture arbre;
    
    // on fait tourner la boucle principale
    while (window.isOpen())
    {
        // on gère les évènements
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        
        if (clock.getElapsedTime().asSeconds() > 5.f)
        {
            jeu.spawn_obstacle(arbre);
            clock.restart();
        }

        jeu.clear();
        jeu.defiler(vitesse);
        

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            voiture.move(-3.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            voiture.move(3.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();

        // on dessine le niveau
        window.clear();
        jeu.drawIn(window);
        window.draw(voiture);
        window.display();
    }

    return 0;
}