#include "FeuDepart.hh"

// Constructeur de la classe FeuDepart
FeuDepart::FeuDepart() : currentState(0), readyToStart(false), _valeur(0) {
    tileset.loadFromFile("assets/tilesetFeu_all.png");      // Chargement des images pour les feux de départ
    setTexture(tileset);
    setTextureRect(sf::IntRect(0,0,300,140));               // Initialisation de la 1ère image
    setPosition(2.f, 200.f);                                // Position du feu de départ
    setScale(sf::Vector2f(0.8f, 0.8f));                     // Mise à l'échelle
}

//Fonction d'actualisation de FeuDepart
void FeuDepart::updateFeuDepart() {
    static sf::Clock feuClock;
    int nextState = currentState;
    static int firstLoop;

    // Logique pour passer d'un état à l'autre toutes les 0.5 seconde
    if (feuClock.getElapsedTime().asSeconds() > 0.5f) {
        feuClock.restart();     // Reinitialisation du chrono du feu affiché
        ++nextState;            // Nouvel état du feu
        if (nextState > 5) {
            nextState = 0; // Revenir à l'état initial après l'état 5
            readyToStart = true;    // Démarrage du jeu autorisé
            firstLoop++;
        }
        if(firstLoop == 0 || nextState == 0){       // Mise à jour de l'image du feu de départ
            currentState = nextState;               // Actualisation de l'état du feu
            setTextureRect(sf::IntRect(0,140*currentState,300,140));
        }
    }
}

// Fonction accesseur de l'état de lancement du jeu
bool FeuDepart::isReady() const {
    return readyToStart;
}

// Fonction accesseur de l'état actuel du feu 
int FeuDepart::getCurrentState() const {
    return currentState;
}

// Fonction réinitialisant le déroulement du démarrage du jeu
void FeuDepart::reinitialiserFeu() {
    currentState = 0;           // Etat initial
    readyToStart = false;       // Démarrage impossible
    setTextureRect(sf::IntRect(0,0,300,140)); // Utilisation de la première texture par défaut
}

// Fonction gérant les possibles faux départ et conditions pour le démarrage du jeu
void FeuDepart::gestionFeu(FeuDepart& feu, bool& fauxDepart, bool& enteringRace, int& firstLoop, float& first_time, sf::Clock& fauxDepartClock, sf::Clock& reactedTime) {
    // Tentative de démarrage non autorisée -> faux départ
    if (feu.getCurrentState() != 0 && !enteringRace && !fauxDepart && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        fauxDepart = true;
        fauxDepartClock.restart();      // Activation du temps en état de faux départ
    }
    // Réactualisation du feu après un faux départ (après 1.5 s)
    if (fauxDepart) {
        // Affichage de l'image f1_feu_dep_faux_dep.png pendant 1.5 secondes
        if (fauxDepartClock.getElapsedTime().asSeconds() < 1.5f) {
            setTextureRect(sf::IntRect(0,980,300,140));
        } else {        // Réinitialisation du feu et fin de l'état faux départ
            fauxDepart = false;
            feu.reinitialiserFeu();
        }
    }
    else {          // Actualisation de l'état du feu
        feu.updateFeuDepart();
    }
    if(feu.isReady() && firstLoop == 0){        // Initialisation du temps lorsque le démarrage est autorisé
        first_time = reactedTime.getElapsedTime().asSeconds();
        firstLoop++;
    }
}

// Fonction accesseur de valeur
int FeuDepart::getValue() const
{
    return _valeur;
}