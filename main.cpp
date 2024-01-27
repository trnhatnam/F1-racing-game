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
#include <map>
#include <string>
using namespace std;

int main()
{
    // --- on crée la fenêtre ---
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(960, 960), "Jeu de course F1");
    window.setFramerateLimit(30);
    window.setVerticalSyncEnabled(true);
    // --- on définit le niveau à l'aide de numéro de tuiles ----
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

    // --- création de l'objet voiture de l'utilisateur ----
    Voiture voiture(320, 600, 0, 50, 20, 20, 3, 3,true);

    // --- initialisation des données de position et d'état ---
    map<string, bool> keyboardTracker{{"leftPressed",false}, {"rightPressed",false}, {"enterPressed",false}};
    float vitesse = 0.0f;
    float carburant = 0.f;
    const float minX = 256.f;
    const float maxX = 640.f;
    std::chrono::steady_clock::time_point lastMoveTime = std::chrono::steady_clock::now();

    // --- gestion des collisions ----
    bool invincible = false;
    bool inbuffable = false;
    map<string, sf::Clock> timerTracker{{"timer_invincible", sf::Clock()}, {"timer_nonbuffable", sf::Clock()},
                                        {"timer_no_obstacles", sf::Clock()}, {"timer_no_buff", sf::Clock()}};

    // --- attachage du tableau de bord à la voiture ----
    AffichageDonnees affichage(voiture);

    // --- gestion des feux ----
    FeuDepart feu;

    sf::Clock fauxDepartClock; // Chronomètre pour le faux départ
    sf::Clock reactedTime; // Chronomètre de temps de réaction
    reactedTime.restart();

    bool fauxDepart = false; // Indicateur pour le faux départ
    bool enteringRace = false; // Indique si le joueur a appuyé sur Enter pour démarrer la course

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
                keyboardTracker["enterPressed"] = true;
                enteringRace = true;
                if (vitesse == 0)
                    // demarrage de la voiture
                    voiture += 5.f;
                // initialisation du déplacement
                vitesse = voiture.getSpeed();
                carburant = voiture.getfuel();

                // demarrage du chronomètre
                affichage.startChrono();
            }
        }
        else { 
        if (keyboardTracker["enterPressed"]){
            feu.hideFeuSprite();
            if (vitesse > 5)
            {
                // plus la voiture va vite, plus les élements de jeu apparaissent vite
                if (timerTracker["timer_no_obstacles"].getElapsedTime().asSeconds() > 50/(vitesse)) 
                {
                    jeu.spawn_obstacle();
                    timerTracker["timer_no_obstacles"].restart();
                }
                if (timerTracker["timer_no_buff"].getElapsedTime().asSeconds() > 75/(vitesse))
                {
                    
                    jeu.spawn_bonus();
                    timerTracker["timer_no_buff"].restart();
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
                    timerTracker["timer_invincible"].restart();
                }
            if (timerTracker["timer_invincible"].getElapsedTime().asSeconds() > 3.f)
                invincible = false;

            // gestion bonus
            if (!inbuffable)
                if (jeu.checkCollisionBonus(voiture)){
                    inbuffable = true;
                    timerTracker["timer_nonbuffable"].restart();
                }
            if (timerTracker["timer_nonbuffable"].getElapsedTime().asSeconds() > 3.f)
                inbuffable = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                voiture.move_left(minX,keyboardTracker["leftPressed"],lastMoveTime);
            else
                keyboardTracker["leftPressed"] = false;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                voiture.move_right(maxX,keyboardTracker["rightPressed"],lastMoveTime);
            else
                keyboardTracker["rightPressed"] = false;

            affichage += jeu.getPositionMap1(); // mise à jour des données de chrono, distance et vitesse
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
        
        if (voiture.getHp() == 0 || (vitesse < 3 && vitesse > 0))
        {
            feu.hideFeuSprite();
            keyboardTracker["enterPressed"] = false;
            affichage.gameOverNotice(window);
        }

        feu.draw(window);
        window.display();
        }
    

    return 0;
}