#include <SFML/Graphics.hpp>
#include "tilemap.hh"
#include "voiture.hpp"
#include <chrono>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>

int main()
{
    // on crée la fenêtre
    sf::RenderWindow window(sf::VideoMode(960, 960), "Tilemap");
    window.setFramerateLimit(30);
    window.setVerticalSyncEnabled(false);

    // on définit le niveau à l'aide de numéro de tuiles
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


    // on crée la tilemap avec le niveau précédemment défini
    // pour simuler une tilemap infini, on crée 2 tilemap
    TileMap map;
    TileMap map2;
    TileMap map3;
    sf::View view = window.getView();
    map.setPosition(0.f, 0.f);
    map2.setPosition(0.f, -960.f);
    map3.setPosition(0.f, -960.f*2);

    if (!map.load("tileset.png", sf::Vector2u(64, 64), level, 15, 15))
        return -1;

    if (!map2.load("tileset.png", sf::Vector2u(64, 64), level, 15, 15))
        return -1;

    if (!map3.load("tileset.png", sf::Vector2u(64, 64), level, 15, 15))
        return -1;

    Voiture voiture(432.5,600,0,50);

    // Sprite de la voiture
    sf::Sprite voitureSprite;
    sf::Texture textureVoiture;
    if (!textureVoiture.loadFromFile("assets/voiture.png", sf::IntRect(0, 0, 64, 64)))
        return -1;
    voitureSprite.setTexture(textureVoiture);
    voitureSprite.setScale(1.5f,1.5f);
    voitureSprite.setPosition(sf::Vector2f(voiture.getX(), voiture.getY()));
    float vitesse = voiture.getSpeed();

    bool leftPressed = false;
    bool rightPressed = false;
    bool enterPressed = false;

    // Limite maximale et minimale pour le déplacement horizontal de la voiture
    const float minX = 256.f; // Limite minimale sur l'axe x (4e colonne)
    const float maxX = 576.f; // Limite maximale sur l'axe x (9e colonne)

    // selection de la police d'écriture
    sf::Font font;
    if (!font.loadFromFile("fonts/chrono_pixel/nuvel.ttf")) {
        std::cerr << "Erreur pour la police" << std::endl;
    }

    // commande de mesure du temps du dernier déplacement
    std::chrono::steady_clock::time_point lastMoveTime = std::chrono::steady_clock::now();

    // Affichage du chronomètre
    sf::Text chronoText;
    chronoText.setFont(font);
    chronoText.setCharacterSize(24);
    chronoText.setFillColor(sf::Color::Black);
    chronoText.setPosition(32.f, 10.f); // Position du chronomètre en haut à gauche
    chronoText.setScale(2.f,2.f);

    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    float initialMapPositionY = 0.f; // Position verticale initiale de la map
    float distanceParcourue = 0.f;

    // Affichage de la distance parcourue
    sf::Text distanceText;
    distanceText.setFont(font);
    distanceText.setCharacterSize(18);
    distanceText.setFillColor(sf::Color::White);
    distanceText.setPosition(416.f, 700.f); // Position du texte de la distance
    distanceText.setScale(2.f,2.f);

    sf::Text vitesseText;
    vitesseText.setFont(font);
    vitesseText.setCharacterSize(24);
    vitesseText.setFillColor(sf::Color::Black);
    vitesseText.setPosition(32.f, 150.f); // Position pour afficher la vitesse
    vitesseText.setScale(1.5f,1.5f);

    // on fait tourner la boucle principale
    while (window.isOpen())
    {
        // on gère les évènements
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            enterPressed = true;
            if(vitesse == 0)
                voiture.startSpeedUp();
            vitesse = voiture.getSpeed();

        if (enterPressed){

            // Déplacement de la map
            if (map.getPosition().y > initialMapPositionY) { 
                distanceParcourue += map.getPosition().y - initialMapPositionY;
                initialMapPositionY = map.getPosition().y;
            }
            else if (map.getPosition().y < initialMapPositionY) {
                distanceParcourue += initialMapPositionY - map.getPosition().y;
                initialMapPositionY = map.getPosition().y;
            }

            // Conversion du déplacement en mètres
            float distanceParcourueMetres = distanceParcourue / (64.f / 1.5f);

            // Affichage de la distance parcourue arrondie à une précision de 0.2f
            std::ostringstream stream;

            // Ligne fixant la précision de la distance à deux décimales
            stream << std::fixed << std::setprecision(2) << distanceParcourueMetres;
            std::string distanceStr = stream.str();

            distanceText.setString(distanceStr + " m");

            // Vitesse de la voiture
            std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
            std::chrono::milliseconds elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime);

            int totalSeconds = static_cast<int>(elapsedTime.count() / 1000); // Convertir en secondes
            int minutes = totalSeconds / 60;                                 // Initialisation des minutes
            int seconds = totalSeconds % 60;                                 // Initialisation des secondes
            int milliseconds = static_cast<int>(elapsedTime.count() % 1000); // Récupération des millisecondes

            std::string minutesStr = (minutes < 10) ? "0" + std::to_string(minutes) : std::to_string(minutes);
            std::string secondsStr = (seconds < 10) ? "0" + std::to_string(seconds) : std::to_string(seconds);

            // Affichage du chronomètre
            std::string timeStr = minutesStr + " : " +
                                secondsStr + " : " +
                                std::to_string(milliseconds);

            chronoText.setString(timeStr);

            

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

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            // Déplacement vers la gauche
                if (voiture.getX() > minX) // Vérification limite gauche
                {
                    if (!leftPressed){
                        // déplacement d'une tuile vers la gauche du véhicule
                        voiture.move(-64.f);
                        voitureSprite.move(-64.f, 0.f);
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
                            voiture.move(-64.f);
                            voitureSprite.move(-64.f, 0.f);
                            // on met à jour le temps du dernier déplacement
                            lastMoveTime = std::chrono::steady_clock::now();
                        }
                    }
                }
            } else {
                leftPressed = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                // Déplacement vers la droite
                
                // Vérification limite droite
                if (voiture.getX() < maxX)
                {
                    if (!rightPressed){
                        // déplacement d'une tuile vers la droite du véhicule
                        voiture.move(64.f);
                        voitureSprite.move(64.f, 0.f);
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
                        if (voiture.getX() < maxX)
                        {
                            // déplacement d'une tuile vers la droite du véhicule
                            voiture.move(64.f);
                            voitureSprite.move(64.f, 0.f);
                            // on met à jour le temps du dernier déplacement
                            lastMoveTime = std::chrono::steady_clock::now(); 
                        }
                    }
                }
            } else {
                // déplacement interdit
                rightPressed = false;
            }



            // Calcul de la vitesse
            float tempsSeconde = elapsedTime.count() / 1000.f; // Convertir le temps en secondes
            float vitesseMS = distanceParcourueMetres / tempsSeconde;
            float vitesse_KmH = vitesseMS * 3.6f; // Convertir en km/h

            // Affichage de la vitesse
            std::ostringstream stream_speed;
            stream_speed << std::fixed << std::setprecision(2) << vitesse_KmH;
            std::string vitesseStr = stream_speed.str();

            vitesseText.setString(vitesseStr + " Km/h");
        }
        // on dessine le niveau
        window.clear();
        window.setView(view);
        window.draw(map);
        window.draw(map2);
        window.draw(map3);
        window.draw(voitureSprite);
        window.draw(chronoText);
        window.draw(distanceText);
        window.draw(vitesseText);
        window.display();
    }

    return 0;
}
