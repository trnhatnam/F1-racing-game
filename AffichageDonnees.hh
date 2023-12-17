#ifndef CHRONO_DISTANCE_CALCULATOR_H
#define CHRONO_DISTANCE_CALCULATOR_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>

class AffichageDonnees {
private:
    std::chrono::steady_clock::time_point startTime;
    float initialMapPositionY;
    float distanceParcourue;
    sf::Text chronoText;
    sf::Text distanceText;
    sf::Text vitesseText;
    sf::Font font;

public:
    AffichageDonnees();
    void startChrono();
    void updateChronoDistance(float mapPosY, float vitesse);
    void updateVitesse(float distance);
    void draw(sf::RenderWindow& window);
};

#endif // CHRONO_DISTANCE_CALCULATOR_H
