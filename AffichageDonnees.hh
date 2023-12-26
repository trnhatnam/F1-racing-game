#ifndef CHRONO_DISTANCE_CALCULATOR_H
#define CHRONO_DISTANCE_CALCULATOR_H

#include <SFML/Graphics.hpp>
#include <iomanip>
#include <sstream>
#include <iostream>

class AffichageDonnees {
private:
    sf::Clock startTime;
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
    void drawSpeedometer(sf::RenderWindow& window, float currentSpeed, float maxSpeed);
};

#endif // CHRONO_DISTANCE_CALCULATOR_H
