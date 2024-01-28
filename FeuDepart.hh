#pragma once
#include "AffichageDonnees.hh"

class FeuDepart : public ElementDeJeu{
private:
    int currentState; // État actuel du feu de départ
    sf::Texture tileset;
    bool readyToStart; // Booléen pour indiquer si le jeu peut être démarré
    sf::Clock fauxDepartClock; // Chronomètre pour le faux départ
    int _valeur;
public:
    FeuDepart();
    int getValue() const;
    void updateFeuDepart(); // Met à jour l'état du feu de départ
    bool isReady() const; // Renvoie l'état du feu de départ pour démarrer le jeu
    int getCurrentState() const; // Renvoie l'état actuel du feu de départ
    void reinitialiserFeu(); // Reinitialisation du feu de départ
    // Gestion du comportement du Feu avant le lancement du jeu
    void gestionFeu(FeuDepart& feu, bool& fauxDepart, bool& enteringRace, int& firstLoop, float& first_time, sf::Clock& fauxDepartClock, sf::Clock& reactedTime);
};