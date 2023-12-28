#include <SFML/Graphics.hpp>
#include "tilemap.hh"
#include "jeu.hpp"
#include "voiture.hpp"
#include "AffichageDonnees.hh"
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
    sf::Clock clock;
    sf::Texture textureVoiture;
    if (!textureVoiture.loadFromFile("assets/voiture.png", sf::IntRect(0, 0, 64, 64)))
        return -1;
    // création de l'objet voiture
    Voiture voiture(320, 600, 0, 50, 20, 20, 5, 5, textureVoiture);

    // création de l'objet point de vie
    sf::Texture textureHp;
    if (!textureHp.loadFromFile("assets/Hp_logo.png", sf::IntRect(0, 0, 64, 64)))
        return -1;
    sf::Sprite IconHp(textureHp);

    // initialisation des données de position et d'état
    float vitesse = 0.0f;
    float carburant = 0.f;
    const float minX = 256.f;
    const float maxX = 576.f;
    bool leftPressed = false;
    bool rightPressed = false;
    bool enterPressed = false;
    std::chrono::steady_clock::time_point lastMoveTime = std::chrono::steady_clock::now();

    AffichageDonnees affichage;
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            enterPressed = true;
            if (vitesse == 0)
                // demarrage de la voiture
                voiture.startSpeedUp();
            // initialisation du déplacement
            vitesse = voiture.getSpeed();
            carburant = voiture.getActualOil();

            // demarrage du chronomètre
            affichage.startChrono();
        }

        if (enterPressed){
            if (clock.getElapsedTime().asSeconds() > 3.f && vitesse > 5)
            {
                jeu.spawn_obstacle();
                clock.restart();
            }

            jeu.clear();
            vitesse = voiture.getSpeed();
            carburant = voiture.getActualOil();
            voiture.SpeedUp();
            voiture.UseOfOil();
            jeu.move(vitesse);
            jeu.checkCollision(voiture);


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                if (voiture.getX() > minX){
                        if (!leftPressed){
                            // déplacement d'une tuile vers la gauche du véhicule
                            voiture.move(-64.f,0.f);
                            // déplacement autorisé
                            leftPressed = true;
                            // mise à jour le temps du dernier déplacement
                            lastMoveTime = std::chrono::steady_clock::now();
                        }
                
                        std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
                        std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastMoveTime);

                        // on attend un quart de seconde (0.25 s) avant chaque déplacement
                        if (duration.count() >= 250) {
                            if (voiture.getX() > minX) {
                                // déplacement d'une tuile vers la gauche du véhicule
                                voiture.move(-64.f,0.f);
                                // on met à jour le temps du dernier déplacement
                                lastMoveTime = std::chrono::steady_clock::now();
                            }
                        }
                    }
                } else {
                    // déplacement interdit
                    leftPressed = false;
                }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                if (voiture.getX() < maxX){
                        if (!rightPressed){
                            // déplacement d'une tuile vers la droite du véhicule
                            voiture.move(64.f,0.f);
                            // déplacement autorisé
                            rightPressed = true;
                            // mise à jour le temps du dernier déplacement
                            lastMoveTime = std::chrono::steady_clock::now(); 
                        }

                        std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
                        std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastMoveTime);

                        // on attend un quart de seconde (0.25 s) avant chaque déplacement
                        if (duration.count() >= 250){
                            // Vérification limite droite
                            if (voiture.getX() < maxX){
                                // déplacement d'une tuile vers la droite du véhicule
                                voiture.move(64.f,0.f);
                                // on met à jour le temps du dernier déplacement
                                lastMoveTime = std::chrono::steady_clock::now(); 
                            }
                        }
                    }
                } else {
                    // déplacement interdit
                    rightPressed = false;
            }
            affichage.updateChronoDistance(jeu.getPositionMap1(), voiture.getSpeed()); // mise à jour des données de chrono, distance et vitesse
        }
        // on dessine le niveau
        window.clear();
        window.draw(jeu);
        window.draw(voiture);
        affichage.drawHpDot(window,voiture.getHp(),IconHp);
        affichage.drawSpeedometer(window,vitesse,voiture.getMaxSpeed()); // affichage de la jauge de vitesse
        affichage.drawOilLevelBar(window,carburant,voiture.getMaxOil()); // affichage de la jauge de carburant
        affichage.draw(window); // affichage du chrono, de la distance et de la vitesse
        window.display();
    
    }

    return 0;
}