#include <SFML/Graphics.hpp>
#include "tilemap.hh"
#include "jeu.hpp"
#include "voiture.hpp"
#include "AffichageDonnees.hh"
#include "FeuDepart.hh"
#include <chrono>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <time.h>

int main()
{
    // on crée la fenêtre
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(960, 960), "Tilemap");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
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

    // création de l'objet voiture
    Voiture voiture(320, 600, 0, 50, 20, 20, 3, 3,true);

    // initialisation des données de position et d'état
    float vitesse = 0.0f;
    float carburant = 0.f;
    const float minX = 256.f;
    const float maxX = 640.f;
    bool leftPressed = false;
    bool rightPressed = false;
    bool enterPressed = false;
    std::chrono::steady_clock::time_point lastMoveTime = std::chrono::steady_clock::now();

    // gestion des collisions
    bool invincible = false;
    bool inbuffable = false;
    sf::Clock timer_invicible;
    sf::Clock timer_nonbuffable;
    sf::Clock clockObs;
    sf::Clock clockBon;

    AffichageDonnees affichage(voiture);
    FeuDepart feu;

    bool fauxDepart = false; // Indicateur pour le faux départ
    sf::Clock fauxDepartClock; // Chronomètre pour le faux départ
    bool enteringRace = false; // Indique si le joueur a appuyé sur Enter pour démarrer la course

    sf::Clock reactedTime; // Chronomètre de temps de réaction
    reactedTime.restart();
    float first_time = 0.0;
    float second_time = 0.0;
    int firstLoop = 0;

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();

        // Gestion du faux départ
        feu.gestionFeu(feu, fauxDepart, enteringRace, firstLoop, first_time, fauxDepartClock, reactedTime);

        if (!enteringRace) {
            if (feu.isReady() && feu.getCurrentState() == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                second_time = reactedTime.getElapsedTime().asSeconds();
                enterPressed = true;
                enteringRace = true;
                if (vitesse == 0)
                    // demarrage de la voiture
                    voiture.startspeedUp();
                // initialisation du déplacement
                vitesse = voiture.getSpeed();
                carburant = voiture.getfuel();

                // demarrage du chronomètre
                affichage.startChrono();
            }
        }
        else { 
        if (enterPressed){
            feu.hideFeuSprite();
            if (vitesse > 7)
            {
                if (clockObs.getElapsedTime().asSeconds() > 1/vitesse + 2.f)
                {
                    jeu.spawn_obstacle();
                    clockObs.restart();
                }
                if (clockBon.getElapsedTime().asSeconds() > 1/vitesse + 6.f)
                {
                    
                    jeu.spawn_bonus();
                    clockBon.restart();
                }
            }
    
            jeu.clear();
            vitesse = voiture.getSpeed();
            carburant = voiture.getfuel();
            voiture.speedUp();
            voiture.useFuel();
            jeu.move(vitesse);

            // gestion obstacle
            if (!invincible)
                if (jeu.checkCollisionObs(voiture)){
                    invincible = true;
                    timer_invicible.restart();
                }
            if (timer_invicible.getElapsedTime().asSeconds() > 3.f)
                invincible = false;

            // gestion bonus
            if (!inbuffable)
                if (jeu.checkCollisionBonus(voiture)){
                    inbuffable = true;
                    timer_nonbuffable.restart();
                }
            if (timer_nonbuffable.getElapsedTime().asSeconds() > 3.f)
                inbuffable = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                voiture.move_left(minX,leftPressed,lastMoveTime);
            else
                leftPressed = false;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                voiture.move_right(maxX,rightPressed,lastMoveTime);
            else
                rightPressed = false;

            affichage.updateChronoDistance(jeu.getPositionMap1()); // mise à jour des données de chrono, distance et vitesse
            }
        }
        // on dessine le niveau
        window.clear();
        window.draw(jeu);
        window.draw(voiture);
        window.draw(affichage); // affichage du chrono, de la distance et de la vitesse, vie
        affichage.drawSpeedometer(window); // affichage de la jauge de vitesse
        affichage.drawOilLevelBar(window); // affichage de la jauge de carburant
        if(enteringRace)
            affichage.ReactedTime(window,first_time,second_time);
        

 
        if (voiture.getHp() == 0 || (vitesse < 3 && vitesse > 0.001))
        {
            feu.hideFeuSprite();
            enterPressed = false;
            affichage.gameOverNotice(window);
        }

        feu.draw(window);
        window.display();
        }
    

    return 0;
}