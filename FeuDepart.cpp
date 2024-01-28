#include "FeuDepart.hh"

FeuDepart::FeuDepart() : currentState(0), readyToStart(false), _valeur(0) {
    tileset.loadFromFile("assets/tilesetFeu_all.png");
    setTexture(tileset);
    setTextureRect(sf::IntRect(0,0,300,140));
    setPosition(2.f, 200.f); // Position du feu de départ
    setScale(sf::Vector2f(0.8f, 0.8f));
}

void FeuDepart::updateFeuDepart() {
    static sf::Clock feuClock;
    int nextState = currentState;
    static int firstLoop;

    // Logique pour passer d'un état à l'autre toutes les 0.5 seconde
    if (feuClock.getElapsedTime().asSeconds() > 0.5f) {
        feuClock.restart();
        ++nextState;
        if (nextState > 5) {
            nextState = 0; // Revenir à l'état initial après l'état 5
            readyToStart = true;
            firstLoop++;
        }
        if(firstLoop == 0 || nextState == 0){
            currentState = nextState;
            setTextureRect(sf::IntRect(0,140*currentState,300,140));
        }
    }
}

bool FeuDepart::isReady() const {
    return readyToStart;
}

int FeuDepart::getCurrentState() const {
    return currentState;
}

void FeuDepart::reinitialiserFeu() {
    currentState = 0;
    readyToStart = false;
    setTextureRect(sf::IntRect(0,0,300,140)); // Utilisation de la première texture par défaut
}

void FeuDepart::gestionFeu(FeuDepart& feu, bool& fauxDepart, bool& enteringRace, int& firstLoop, float& first_time, sf::Clock& fauxDepartClock, sf::Clock& reactedTime) {
    if (feu.getCurrentState() != 0 && !enteringRace && !fauxDepart && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        fauxDepart = true;
        fauxDepartClock.restart();
    }

    if (fauxDepart) {
        // Affichage de l'image f1_feu_dep_faux_dep.png pendant 3 secondes
        if (fauxDepartClock.getElapsedTime().asSeconds() < 1.5f) {
            setTextureRect(sf::IntRect(0,980,300,140));
        } else {
            fauxDepart = false;
            feu.reinitialiserFeu();
        }
    }
    else {
        feu.updateFeuDepart();
    }
    if(feu.isReady() && firstLoop == 0){
        first_time = reactedTime.getElapsedTime().asSeconds();
        firstLoop++;
    }
}

int FeuDepart::getValue() const
{
    return _valeur;
}