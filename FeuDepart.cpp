#include "FeuDepart.hh"

FeuDepart::FeuDepart() : currentState(0), readyToStart(false) {
    for (int i = 0; i < 6; ++i) {
        std::string texturePath = "assets/f1_feu_dep_" + std::to_string(i) + ".png";
        if (!feuTextures[i].loadFromFile(texturePath)) {
            std::cerr << "Erreur lors du chargement de la texture du feu de départ " << i << std::endl;
            // Gérer l'erreur si la texture n'est pas chargée correctement
        }
    }
    feuSprite.setTexture(feuTextures[0]); // Utilisation de la première texture par défaut
    feuSprite.setPosition(2.f, 200.f); // Position du feu de départ

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
    static int firstLoop = 0;

    // Logique pour passer d'un état à l'autre toutes les 1 seconde
    if (feuClock.getElapsedTime().asSeconds() > 1.0f) {
        feuClock.restart();
        ++nextState;
        if (nextState > 5) {
            nextState = 0; // Revenir à l'état initial après l'état 5
            readyToStart = true; // Le feu est prêt à démarrer le jeu
            firstLoop++;
        }
        if(firstLoop == 0 || nextState == 0){
            currentState = nextState;
            feuSprite.setTexture(feuTextures[currentState]);
        }
    }
}

void FeuDepart::draw(sf::RenderWindow& window) {
    window.draw(feuSprite);
    window.draw(FoulSprite);
}

bool FeuDepart::isReady() const {
    return readyToStart;
}

int FeuDepart::getCurrentState() const {
    return currentState;
}

void FeuDepart::hideFeuSprite() {
    feuSprite.setColor(sf::Color(0, 0, 0, 0)); // Masque le dessin du feu principal
}

void FeuDepart::hideFoulSprite() {
    FoulSprite.setColor(sf::Color(0, 0, 0, 0)); // Masque le dessin du faux départ
}

void FeuDepart::showFeuSprite() {
    feuSprite.setColor(sf::Color(255, 255, 255, 255)); // Réaffiche le dessin du feu principal
}

void FeuDepart::showFoulSprite() {
    FoulSprite.setColor(sf::Color(255, 255, 255, 255)); // Réaffiche le dessin du faux départ
}

void FeuDepart::reinitialiserFeu() {
    currentState = 0;
    readyToStart = false;
    feuSprite.setTexture(feuTextures[0]); // Utilisation de la première texture par défaut
    feuSprite.setPosition(2.f, 200.f); // Position du feu de départ
}