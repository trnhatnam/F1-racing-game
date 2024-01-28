#pragma once
#include <SFML/Graphics.hpp>
#include <iomanip>
#include <sstream>
#include <iostream>
#include "voiture.hpp"

class AffichageDonnees : public sf::Drawable, public sf::Transformable{
private:
    // Attributs de la classe
    sf::Clock startTime;
    float initialMapPositionY;          // Position de la map
    float distanceParcourue;            // Distance parcourue dans le jeu
    sf::Text chronoText;                // Texte du chrono
    sf::Text distanceText;              // Texte de la distance
    sf::Text vitesseText;               // Texte de la vitesse 
    sf::Text vitesseMaxReachedText;     // Texte de la vitesse Max reached
    sf::Text tempsReaction;             // Texte du temps de réaction
    sf::Text centralText;               // Texte du "GameOver"
    sf::Font font;                      // Police d'écriture
    Voiture& voitureTrack;              // Voiture de l'utilisateur

    // Positionnement et taille de la jauge
    inline static float width = 200.f; // Largeur de la jauge
    inline static float height = 20.f; // Hauteur de la jauge
    inline static float posX_vit = 20.f;    // Position X de la jauge
    inline static float posY_vit = 100.f;   // Position Y de la jauge

    // Texture logo max speed
    inline static sf::Texture SpeedPicture; // Texture du logo
    inline static sf::Sprite CompteurSpeed; // Sprite du logo
    inline static float logoPosX = 880.f;   // Position X du logo
    inline static float logoPosY = 180.f;   // Position Y du logo 

    // Texture oil tank
    inline static sf::Texture TankPicture;  // Texture du logo
    inline static sf::Sprite OilTank;       // Sprite du logo
    inline static float imagPosX = 20.f;    // Position X du logo
    inline static float imagPosY = 625.f;   // Position Y du logo
    inline static float posX_oil = 20.f;    // Position X de la jauge oil
    inline static float posY_oil = 750.f;   // Position Y de la jauge oil

    // on place les points de vie en haut à droite de la fenetre
    inline static float hpPosX = 750.f;     // Position X du logo
    inline static float hpPosY = 20.0f;     // Position Y du logo
    inline static sf::Sprite HpIcon;        // Sprite du logo
    inline static sf::Texture HpTexture;    // Texture du logo

    // on place le temps de réaction au milieu à gauche
    inline static float feuPosX = 20.f;     // Position X du logo
    inline static float feuPosY = 180.f;    // Position Y du logo
    inline static sf::Sprite FeuSprite;     // Sprite du logo
    inline static sf::Texture FeuTexture;   // Texture du logo

public:
    // Constructeur de la classe AffichageDonnees
    AffichageDonnees(Voiture &v);
    
    // Méthodes de la classe AffichageDonnees
    void startChrono();
    //void updateChronoDistance(float mapPosY);
    friend AffichageDonnees& operator+=(AffichageDonnees& dashboard, float mapPosY);
    void updateVitesse(float distance);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void drawSpeedometer(sf::RenderWindow& target);
    void drawOilLevelBar(sf::RenderWindow& target);
    void ReactedTime(sf::RenderWindow& target, float appearanceState, float enterPressed);
    void gameOverNotice(sf::RenderWindow& window);

    sf::Text parametrage_chrono(sf::Text& textFont);
    sf::Text parametrage_vitesse(sf::Text& textFont);
    sf::Text parametrage_distance(sf::Text& textFont);
    sf::Text parametrage_vitesseMax(sf::Text& textFont);
    sf::Text parametrage_reacted_time(sf::Text& textFont);
    sf::Sprite logo_speed(sf::Sprite& SpeedSprite);
    sf::Sprite logo_tank(sf::Sprite& OilSprite);
    sf::Sprite logo_feu_dep(sf::Sprite& FeuDepartSprite);
};