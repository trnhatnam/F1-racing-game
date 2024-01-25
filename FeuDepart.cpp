#include "FeuDepart.hh"

FeuDepart::FeuDepart() : currentState(0), readyToStart(false) {
    for (int i = 0; i < 6; ++i) {
        std::string texturePath = "assets/f1_feu_dep_" + std::to_string(i) + ".png";
        if (!feuTextures[i].loadFromFile(texturePath)) {
            std::cerr << "Erreur lors du chargement de la texture du feu de départ " << i << std::endl;
            // Gérer l'erreur si la texture n'est pas chargée correctement
        }
    }
    setTexture(feuTextures[0]); // Utilisation de la première texture par défaut
    setPosition(2.f, 200.f); // Position du feu de départ

    if (!feuTextureFoul.loadFromFile("assets/f1_feu_dep_faux_dep.png")){
        std::cerr << "Erreur lors du chargement de la texture du feu de départ " << std::endl;
        // Gérer l'erreur si la texture n'est pas chargée correctement
    }
    FoulSprite.setTexture(feuTextureFoul);
    FoulSprite.setPosition(2.f,200.f);
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
            setTexture(feuTextures[currentState]);
        }
    }
}

void FeuDepart::draw(sf::RenderWindow& window) {
    window.draw(*this);
    window.draw(FoulSprite);
}

bool FeuDepart::isReady() const {
    return readyToStart;
}

int FeuDepart::getCurrentState() const {
    return currentState;
}

void FeuDepart::hideFeuSprite() {
    setColor(sf::Color(0, 0, 0, 0)); // Masque le dessin du feu principal
}

void FeuDepart::hideFoulSprite() {
    FoulSprite.setColor(sf::Color(0, 0, 0, 0)); // Masque le dessin du faux départ
}

void FeuDepart::showFeuSprite() {
    setColor(sf::Color(255, 255, 255, 255)); // Réaffiche le dessin du feu principal
}

void FeuDepart::showFoulSprite() {
    FoulSprite.setColor(sf::Color(255, 255, 255, 255)); // Réaffiche le dessin du faux départ
}

void FeuDepart::reinitialiserFeu() {
    currentState = 0;
    readyToStart = false;
    setTexture(feuTextures[0]); // Utilisation de la première texture par défaut
    setPosition(2.f, 200.f); // Position du feu de départ
}

void FeuDepart::gestionFeu(FeuDepart& feu, bool& fauxDepart, bool& enteringRace, int& firstLoop, float& first_time, sf::Clock& fauxDepartClock, sf::Clock& reactedTime) {
    if (feu.getCurrentState() != 0 && !enteringRace && !fauxDepart && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        fauxDepart = true;
        fauxDepartClock.restart();
    }

    if (fauxDepart) {
        // Affichage de l'image f1_feu_dep_faux_dep.png pendant 3 secondes
        if (fauxDepartClock.getElapsedTime().asSeconds() < 1.5f) {
            feu.hideFeuSprite();
            feu.showFoulSprite();
        } else {
            fauxDepart = false;
            feu.reinitialiserFeu();
        }
    }
    else {
        feu.hideFoulSprite();
        feu.showFeuSprite();
        feu.updateFeuDepart();
    }
    if(feu.isReady() && firstLoop == 0){
        first_time = reactedTime.getElapsedTime().asSeconds();
        firstLoop++;
    }
}