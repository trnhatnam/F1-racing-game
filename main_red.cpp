#include <SFML/Graphics.hpp>
#include "tilemap.hh"
#include "voiture.hpp"
#include "AffichageDonnees.hh"
#include <chrono>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>

int main() {
    sf::RenderWindow window(sf::VideoMode(960, 960), "Tilemap");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);

    int level[] =
    {
        1,1,1,1,2,3,0,3,0,0,2,1,1,1,1,
        1,1,1,1,2,3,0,3,0,0,2,1,1,1,1,
        1,1,1,1,2,0,3,0,3,0,2,1,1,1,1,
        1,1,1,1,2,0,3,0,3,0,2,1,1,1,1,
        1,1,1,1,2,3,0,3,0,0,2,1,1,1,1,
        1,1,1,1,2,3,0,3,0,0,2,1,1,1,1,
        1,1,1,1,2,0,3,0,3,0,2,1,1,1,1,
        1,1,1,1,2,0,3,0,3,0,2,1,1,1,1,
        1,1,1,1,2,3,0,3,0,0,2,1,1,1,1,
        1,1,1,1,2,3,0,3,0,0,2,1,1,1,1,
        1,1,1,1,2,0,3,0,3,0,2,1,1,1,1,
        1,1,1,1,2,0,3,0,3,0,2,1,1,1,1,
        1,1,1,1,2,3,0,3,0,0,2,1,1,1,1,
        1,1,1,1,2,3,0,3,0,0,2,1,1,1,1,
        1,1,1,1,2,0,3,0,3,0,2,1,1,1,1,
    };

    TileMap map;
    TileMap map2;
    TileMap map3;
    sf::View view = window.getView();
    map.setPosition(0.f, 0.f);
    map2.setPosition(0.f, -960.f);
    map3.setPosition(0.f, -960.f * 2);

    if (!map.load("tileset.png", sf::Vector2u(64, 64), level, 15, 15))
        return -1;

    if (!map2.load("tileset.png", sf::Vector2u(64, 64), level, 15, 15))
        return -1;

    if (!map3.load("tileset.png", sf::Vector2u(64, 64), level, 15, 15))
        return -1;

    sf::Texture textureVoiture;
    if (!textureVoiture.loadFromFile("assets/voiture.png", sf::IntRect(0, 0, 64, 64)))
        return -1;

    // création de l'objet voiture
    Voiture voiture(432.5, 600, 0, 50, textureVoiture);

    // initialisation des données de position et d'état
    float vitesse = 0.0f;
    const float minX = 256.f;
    const float maxX = 576.f;
    bool leftPressed = false;
    bool rightPressed = false;
    bool enterPressed = false;
    std::chrono::steady_clock::time_point lastMoveTime = std::chrono::steady_clock::now();

    // création de l'instance d'affichage des données
    AffichageDonnees affichage;

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
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

            // demarrage du chronomètre
            affichage.startChrono();
        }

        if (enterPressed) {

            if (map.getPosition().y >= 960.f)
                map.setPosition(0.f, -960.f + (map.getPosition().y - 960.f));
            if (map2.getPosition().y >= 960.f)
                map2.setPosition(0.f, -960.f + (map2.getPosition().y - 960.f));
            if (map3.getPosition().y >= 960.f)
                map3.setPosition(0.f, -960.f + (map3.getPosition().y - 960.f));

            vitesse = voiture.getSpeed();
            voiture.SpeedUp();

            map.move(0.f, vitesse);
            map2.move(0.f, vitesse);
            map3.move(0.f, vitesse);

            // Déplacement vers la gauche
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                // Vérification limite gauche
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
            affichage.updateChronoDistance(map.getPosition().y, voiture.getSpeed()); // mise à jour des données de chrono, distance et vitesse
        }

        window.clear();
        window.setView(view);
        window.draw(map);
        window.draw(map2);
        window.draw(map3);
        window.draw(voiture);
        affichage.drawSpeedometer(window,vitesse,voiture.getMaxSpeed()); // affichage de la jauge de vitesse
        affichage.draw(window); // affichage du chrono, de la distance et de la vitesse
        window.display();
    }

    return 0;
}
