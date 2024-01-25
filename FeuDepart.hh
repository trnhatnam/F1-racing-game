#pragma once
#include "AffichageDonnees.hh"

class FeuDepart : public ElementDeJeu {
private:
    int currentState; // État actuel du feu de départ
    sf::Texture feuTextureFoul; // Texture pour afficher l'image du feu de faux départ
    sf::Sprite FoulSprite; // Sprite pour afficher la texture du faux départ
    sf::Texture feuTextures[6]; // Tableau de textures pour les différentes images du feu de départ
    sf::Sprite feuSprite; // Sprite pour afficher les différentes textures
    bool readyToStart; // Booléen pour indiquer si le jeu peut être démarré
    sf::Clock fauxDepartClock; // Chronomètre pour le faux départ

public:
    FeuDepart();

    void updateFeuDepart(); // Met à jour l'état du feu de départ
    void draw(sf::RenderWindow& window); // Redéfinition de la méthode draw pour dessiner le feu de départ
    bool isReady() const; // Renvoie l'état du feu de départ pour démarrer le jeu
    int getCurrentState() const; // Renvoie l'état actuel du feu de départ
    void hideFeuSprite(); // Cache le dessin du feu principal
    void hideFoulSprite(); // Cache le dessin du faux départ
    void showFeuSprite(); // Réaffiche le dessin du feu principal
    void showFoulSprite(); // Réaffiche le dessin du faux départ
    void reinitialiserFeu(); // Reinitialisation du feu de départ
    // Gestion du comportement du Feu avant le lancement du jeu
    void gestionFeu(FeuDepart& feu, bool& fauxDepart, bool& enteringRace, int& firstLoop, float& first_time, sf::Clock& fauxDepartClock, sf::Clock& reactedTime);
};