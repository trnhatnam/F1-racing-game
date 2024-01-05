#pragma once
#include <SFML/Graphics.hpp>
#include <iomanip>
#include <sstream>
#include <iostream>
#include "voiture.hpp"

class AffichageDonnees : public sf::Drawable, public sf::Transformable{
private:
    sf::Clock startTime;
    float initialMapPositionY;
    float distanceParcourue;
    sf::Text chronoText;
    sf::Text distanceText;
    sf::Text vitesseText;
    sf::Text vitesseMaxReachedText;
    sf::Text tempsReaction;
    sf::Text centralText;
    sf::Font font;
    Voiture& voitureTrack;

    // Positionnement et taille de la jauge
    inline static float width = 200.f; // Largeur de la jauge
    inline static float height = 20.f; // Hauteur de la jauge
    inline static float posX_vit = 20.f;   // Position X de la jauge
    inline static float posY_vit = 100.f;  // Position Y de la jauge

    // Texture logo max speed
    inline static sf::Texture SpeedPicture;
    inline static sf::Sprite CompteurSpeed;
    inline static float logoPosX = 880.f;
    inline static float logoPosY = 180.f;

    // Texture oil tank
    inline static sf::Texture TankPicture;
    inline static sf::Sprite OilTank;
    inline static float imagPosX = 20.f;
    inline static float imagPosY = 625.f;
    inline static float posX_oil = 20.f;   // Position X de la jauge oil
    inline static float posY_oil = 750.f;  // Position Y de la jauge oil

    // on place les points de vie en haut à droite de la fenetre
    inline static float hpPosX = 750.f;
    inline static float hpPosY = 20.0f;
    inline static sf::Sprite HpIcon;
    inline static sf::Texture HpTexture;

    // on place le temps de réaction au milieu à gauche
    inline static float feuPosX = 20.f;
    inline static float feuPosY = 180.f;
    inline static sf::Sprite FeuSprite;
    inline static sf::Texture FeuTexture;

public:
    AffichageDonnees(Voiture &v);
    void startChrono();
    void updateChronoDistance(float mapPosY);
    void updateVitesse(float distance);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void drawSpeedometer(sf::RenderWindow& target);
    void drawOilLevelBar(sf::RenderWindow& target);
    void ReactedTime(sf::RenderWindow& target, float appearanceState, float enterPressed);
    void gameOverNotice(sf::RenderWindow& window);
    void checkpointNotice(sf::RenderWindow& window);
};