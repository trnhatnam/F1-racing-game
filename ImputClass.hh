#include <SFML/Graphics.hpp>
#include "voiture.hpp"
#include <chrono>
#include <time.h>

// Fonction de déplacement à Gauche
void moveLeft(Voiture& voiture, bool& leftPressed, std::chrono::steady_clock::time_point& lastMoveTime, const float minX) {
    if (voiture.getX() > minX && !leftPressed) {
        // déplacement d'une tuile vers la gauche du véhicule
        voiture.move(-64.f, 0.f);
        // déplacement autorisé
        leftPressed = true;
        // mise à jour le temps du dernier déplacement
        lastMoveTime = std::chrono::steady_clock::now();
    }

    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastMoveTime);

    // on attend un quart de seconde (0.25 s) avant chaque déplacement
    if (duration.count() >= 250 && voiture.getX() > minX) {
        // déplacement d'une tuile vers la gauche du véhicule
        voiture.move(-64.f, 0.f);
        // mise à jour le temps du dernier déplacement
        lastMoveTime = std::chrono::steady_clock::now();
    }
}

// Fonction de déplacement à Droite
void moveRight(Voiture& voiture, bool& rightPressed, std::chrono::steady_clock::time_point& lastMoveTime, const float maxX) {
    if (voiture.getX() < maxX && !rightPressed) {
        // déplacement d'une tuile vers la droite du véhicule
        voiture.move(64.f, 0.f);
        // déplacement autorisé
        rightPressed = true;
        // mise à jour le temps du dernier déplacement
        lastMoveTime = std::chrono::steady_clock::now();
    }

    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastMoveTime);

    // on attend un quart de seconde (0.25 s) avant chaque déplacement
    if (duration.count() >= 250 && voiture.getX() < maxX) {
        // déplacement d'une tuile vers la droite du véhicule
        voiture.move(64.f, 0.f);
        // mise à jour le temps du dernier déplacement
        lastMoveTime = std::chrono::steady_clock::now();
    }
}

class InputManager {
public:
    static void handleInput(sf::Keyboard::Key key, Voiture& voiture, bool& leftPressed, bool& rightPressed, std::chrono::steady_clock::time_point& lastMoveTime, const float minX, const float maxX) {
        if (key == sf::Keyboard::Left) {
            moveLeft(voiture,leftPressed, lastMoveTime, minX);
        } else if (key == sf::Keyboard::Right) {
            moveRight(voiture, rightPressed, lastMoveTime, maxX);
        }
    }
};