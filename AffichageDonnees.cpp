#include "AffichageDonnees.hh"

// Constructeur de la classe AffichageDonnees pour l'affichage et l'actualisation des données en temps réel 
AffichageDonnees::AffichageDonnees(Voiture& v) : initialMapPositionY(0.f), distanceParcourue(0.f), voitureTrack(v) {
    // Chargement de la police d'écriture pour le texte des données
    if (!font.loadFromFile("fonts/chrono_pixel/nuvel.ttf")) {
        std::cerr << "Erreur pour la police" << std::endl;
    }

    // Paramétrage des données quantitatives
    chronoText = parametrage_chrono(chronoText);
    distanceText = parametrage_distance(distanceText);
    vitesseText = parametrage_vitesse(vitesseText);
    vitesseMaxReachedText = parametrage_vitesseMax(vitesseMaxReachedText);
    tempsReaction = parametrage_reacted_time(tempsReaction);

    // Logo vitesse Max Reached
    CompteurSpeed = logo_speed(CompteurSpeed);
    // Logo Oil tank 
    OilTank = logo_tank(OilTank);

    // Chargement de l'image pour le logo des points de vie
    if(!HpTexture.loadFromFile("assets/Hp_logo.png", sf::IntRect(0, 0, 64*v.getMaxHp(), 64))){
        std::cerr << "Erreur lors du chargement de l'image de la pompe" << std::endl;
        EXIT_FAILURE;
    }
    // Points de vie
    HpIcon.setPosition(hpPosX, hpPosY);
    HpTexture.setRepeated(true);
    HpIcon.setTexture(HpTexture);

    // Logo Feu de départ
    FeuSprite = logo_feu_dep(FeuSprite);
}

// Fonction paramétrage du texte pour le chronomètre
sf::Text AffichageDonnees::parametrage_chrono(sf::Text& textFont) {
    textFont.setFont(font);                     // Ajout de la police
    textFont.setCharacterSize(24);              // Taille de la police
    textFont.setFillColor(sf::Color::Black);    // Couleur du texte
    textFont.setPosition(32.f, 10.f);           // Position du texte
    textFont.setScale(2.f, 2.f);                // Mise à l'échelle

    return textFont;
}

// Fonction paramétrage du texte pour la distance
sf::Text AffichageDonnees::parametrage_distance(sf::Text& textFont) {
    textFont.setFont(font);                     // Ajout de la police
    textFont.setCharacterSize(18);              // Taille de la police
    textFont.setFillColor(sf::Color::White);    // Couleur du texte
    textFont.setPosition(416.f, 725.f);         // Position du texte
    textFont.setScale(2.f, 2.f);                // Mise à l'échelle

    return textFont;
}

// Fonction paramétrage du texte pour la vitesse
sf::Text AffichageDonnees::parametrage_vitesse(sf::Text& textFont) {
    textFont.setFont(font);                     // Ajout de la police
    textFont.setCharacterSize(24);              // Taille de la police
    textFont.setFillColor(sf::Color::Black);    // Couleur du texte
    textFont.setPosition(32.f, 120.f);          // Position du texte
    textFont.setScale(1.5f, 1.5f);              // Mise à l'échelle

    return textFont;
}

// Fonction paramétrage du texte pour la vitesse Max Reached
sf::Text AffichageDonnees::parametrage_vitesseMax(sf::Text& textFont) {
    textFont.setFont(font);                     // Ajout de la police
    textFont.setCharacterSize(18);              // Taille de la police
    textFont.setFillColor(sf::Color::Black);    // Couleur du texte
    textFont.setPosition(800.f,250.f);          // Position du texte
    textFont.setScale(1.5f,1.5f);               // Mise à l'échelle
    
    return textFont;
}

// Fonction paramétrage du texte pour le temps de réaction
sf::Text AffichageDonnees::parametrage_reacted_time(sf::Text& textFont) {
    textFont.setFont(font);                     // Ajout de la police
    textFont.setCharacterSize(18);              // Taille de la police
    textFont.setFillColor(sf::Color::Black);    // Couleur du texte
    textFont.setPosition(20.f,230.f);           // Position du texte
    textFont.setScale(1.5f,1.5f);               // Mise à l'échelle

    return textFont;
}

// Fonction initialisation du logo de vitesse
sf::Sprite AffichageDonnees::logo_speed(sf::Sprite& SpeedSprite) {
    // Chargement de l'image pour le logo de vitesse Max Reached
    if(!SpeedPicture.loadFromFile("assets/max_speed.png")){
        std::cerr << "Erreur lors du chargement de l'image du compteur" << std::endl;
        EXIT_FAILURE;
    }
    SpeedSprite.setTexture(SpeedPicture);               // Initialisation de la texture
    SpeedSprite.setPosition(logoPosX,logoPosY);         // Position du sprite à l'affichage
    SpeedSprite.setScale(1.25f,1.25f);                  // Mise à l'échelle

    return SpeedSprite;
}

// Fonction initialisation du logo du carburant
sf::Sprite AffichageDonnees::logo_tank(sf::Sprite& OilSprite) {
    // Chargement de l'image pour le logo du réservoir d'essence
    if(!TankPicture.loadFromFile("assets/pompe_car.png")){
        std::cerr << "Erreur lors du chargement de l'image de la pompe" << std::endl;
        EXIT_FAILURE;
    }
    OilSprite.setTexture(TankPicture);                  // Initialisation de la texture
    OilSprite.setPosition(imagPosX,imagPosY);           // Position du sprite à l'affichage

    return OilSprite;
}

// Fonction initialisation du logo Feu pour le temps de réaction
sf::Sprite AffichageDonnees::logo_feu_dep(sf::Sprite& FeuDepartSprite) {
    // Chargement de l'image pour le logo du feu pour le temps de réaction
    if(!FeuTexture.loadFromFile("assets/f1_feu_dep_tmp_rec.png")){
        std::cerr << "Erreur lors du chargement de l'image du feu" << std::endl;
        EXIT_FAILURE;
    }
    FeuDepartSprite.setTexture(FeuTexture);             // Initialisation de la texture
    FeuDepartSprite.setPosition(feuPosX,feuPosY);       // Position du sprite à l'affichage
    FeuDepartSprite.setScale(0.35f,0.35f);              // Mise à l'échelle

    return FeuDepartSprite;
}

// Fonction (re-)démarrage de chrono pour les données affichées
void AffichageDonnees::startChrono() {
    startTime.restart();
}

// Fonction permettant l'affichage et le calcul de la distance parcourue et du temps écoulé (chrono)
AffichageDonnees& operator+=(AffichageDonnees& dashboard, float mapPosY)
{
    // Chrono de la durée de jeu
    static sf::Clock clock;
    // Variable de position de la map selon l'axe Y, étant actualisé après chaque appel
    static float lastMapPosY = mapPosY;

    // Distance parcourue entre 2 appels 2 la fonction (en pixel)
    if (mapPosY > lastMapPosY) {                                  // déplacement vers l'avant
        dashboard.distanceParcourue += mapPosY - lastMapPosY;     // Actualisation de la distance total parcourue
        lastMapPosY = mapPosY;                                    // Nouvelle position de la map
    }
    else if (mapPosY < lastMapPosY) {                             // déplacement vers l'arrière 
        dashboard.distanceParcourue += lastMapPosY - mapPosY;     // Actualisation de la distance total parcourue
        lastMapPosY = mapPosY;                                    // Nouvelle position de la map
    }
    // Mise à l'échelle de la distance parcourue (pixels -> mètres)
    float distanceParcourueMetres = dashboard.distanceParcourue / (64.f / 1.5f);
    
    // Stockage et écriture de la distance parcourue dans le texte associé
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << distanceParcourueMetres;
    std::string distanceStr = stream.str();
    dashboard.distanceText.setString(distanceStr + " m");

    // Récupération du temps écoulé depuis le lancement du jeu
    sf::Time elapsedTime = clock.getElapsedTime();

    // Configuation des données du chrono
    int totalSeconds = static_cast<int>(elapsedTime.asMilliseconds() / 1000);
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    int milliseconds = static_cast<int>(elapsedTime.asMilliseconds() % 1000);

    // Ecriture spécifique des minutes et des secondes
    std::string minutesStr = (minutes < 10) ? "0" + std::to_string(minutes) : std::to_string(minutes);
    std::string secondsStr = (seconds < 10) ? "0" + std::to_string(seconds) : std::to_string(seconds);

    // Stockage et écriture du chrono
    std::string timeStr = minutesStr + " : " +
                        secondsStr + " : " +
                        std::to_string(milliseconds);
    dashboard.chronoText.setString(timeStr);

    // Fonction de calcul de la vitesse (et vitesse Max Reached)
    dashboard.updateVitesse(distanceParcourueMetres);
    return dashboard;
}

// Fonction affichant et calculant la vitesse actuelle et max Reached 
void AffichageDonnees::updateVitesse(float distance) {
    // Chrono concernant l'actualisation de la vitesse Max Reached
    static sf::Clock speedUpdateClock;
    // Variable de la distance parcourue après la dernière actualisation de la vitesse (et vitesse Max Reached)
    static float lastDistance = distance;
    // Initialisation de la vitesse Max Reached
    static float vitesseMaxReached = 0.0;
    // Récupération du temps écoulé après la réinitialisation de speedUpdateClock
    sf::Time elapsedTime = speedUpdateClock.getElapsedTime();

    if (elapsedTime.asMilliseconds() >= 25) {       // Intervalle de temps avant chaque actualisation

        float distanceDiff = distance - lastDistance;               // Distance parcourue entre chaque actualisation

        float vitesseMS = distanceDiff / elapsedTime.asSeconds();   // Vitesse en m/s de la voiture actualisée entre chaque actualisation
        float vitesse_KmH = vitesseMS * 3.6f;                       // Conversion en Km/h
        lastDistance = distance;                                    // Actualisation de la variable distance parcourue
        speedUpdateClock.restart();                                 // Réinitialisation du chrono d'actualisation

        if (vitesse_KmH > 750)              // Si le seuil de vitesse dépasse le seuil du réel
            vitesse_KmH = 0.0;

        // Ecriture et stockage de la vitesse 
        std::ostringstream stream_speed;
        stream_speed << std::fixed << std::setprecision(1) << vitesse_KmH;
        std::string vitesseStr = stream_speed.str();
        vitesseText.setString(vitesseStr + " Km/h");

        if(vitesse_KmH > vitesseMaxReached)     // Actualisation de la vitesse Max Reached
            vitesseMaxReached = vitesse_KmH;
        // Ecriture et stockage de la vitesse Max Reached
        std::ostringstream max_speed_reach;
        max_speed_reach << std::fixed << std::setprecision(1) << vitesseMaxReached;
        std::string vitesseMaxStr = max_speed_reach.str();
        vitesseMaxReachedText.setString(vitesseMaxStr + " Km/h");
    }
}

// Fonction réalisant l'affichage de tous les attributs de la classe AffichageDonnees
void AffichageDonnees::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    target.draw(chronoText);
    target.draw(distanceText);
    target.draw(vitesseText);
    target.draw(vitesseMaxReachedText);
    target.draw(tempsReaction);

    // pts de vie
    HpIcon.setTextureRect(sf::IntRect(0,0,64*voitureTrack.getHp(), 64));
    target.draw(HpIcon);
}

// Fonction dessinant une barre de vitesse visualisant la vitesse actuelle par rapport à la vitesse Max
void AffichageDonnees::drawSpeedometer(sf::RenderWindow& window) {
    // calcule de la proportion actuelle de la vitesse par rapport à la vitesse maximale
    float speedRatio = voitureTrack.getSpeed() / voitureTrack.getMaxSpeed();
    if (speedRatio > 1.0f) speedRatio = 1.0f; // limitation de la jauge avec la valeur à 1 si la vitesse dépasse maxSpeed

    // on dessine la forme de la jauge (background)
    sf::RectangleShape background(sf::Vector2f(width, height));
    background.setPosition(posX_vit, posY_vit);
    // on détermine la couleur en fonction de la vitesse actuelle
    sf::Color barColor;
    if (speedRatio < 0.4f) {
        // Pour les vitesses basses (inférieures à 40% de la vitesse maximale)
        barColor = sf::Color(0, 255, 0); // Vert
    } else if (speedRatio < 0.65f) {
        // Pour les vitesses moyennes (entre 40% et 65% de la vitesse maximale)
        barColor = sf::Color(255, 255, 0); // Jaune
    } else if (speedRatio < 0.85f) {
        // Pour les vitesses moyennes (entre 65% et 85% de la vitesse maximale)
        barColor = sf::Color(255, 165, 0); // Orange
    } else {
        // Pour les vitesses élevées (au-dessus de 85% de la vitesse maximale)
        barColor = sf::Color(255, 0, 0); // Rouge
    }
    window.draw(background);
    window.draw(CompteurSpeed);
    // Implémentation des paramètres de la barre de vitesse
    sf::RectangleShape speedBar(sf::Vector2f(width * speedRatio, height));
    speedBar.setPosition(posX_vit, posY_vit);
    // utilisation de la couleur déterminée
    speedBar.setFillColor(barColor);
    window.draw(speedBar);
}

// Fonction dessinant une barre de carburant visualisant le niveau de carburant de la voiture par rapport à la capacité Max de celui-ci
void AffichageDonnees::drawOilLevelBar(sf::RenderWindow& window) {
    // calcule de la proportion actuelle du carburant actuel par rapport au niveau de carburant maximal
    float OilRatio = voitureTrack.getfuel() / voitureTrack.getMaxFuel();
    if (OilRatio < 0.0f) OilRatio = 0.0f; // limitation de la jauge avec la valeur à 0 si le carburant est négatif

    // on dessine la forme de la jauge (background)
    sf::RectangleShape background(sf::Vector2f(width, height));
    background.setPosition(posX_oil, posY_oil);
    // on détermine la couleur en fonction de la vitesse actuelle
    sf::Color barColor;
    if (OilRatio < 0.4f) {
        // Pour le niveau bas (inférieures à 40% du niveau maximal)
        barColor = sf::Color(255, 0, 0); // Rouge
    } else if (OilRatio < 0.65f) {
        // Pour les vitesses moyennes (entre 40% et 65% du niveau maximal)
        barColor = sf::Color(255, 165, 0); // Orange
    } else if (OilRatio < 0.85f) {
        // Pour les vitesses moyennes (entre 65% et 85% du niveau maximal)
        barColor = sf::Color(255, 255, 0); // Jaune
    } else {
        // Pour les vitesses élevées (au-dessus de 85% du niveau maximal)
        barColor = sf::Color(0, 255, 0); // Vert
    }
    window.draw(background);
    window.draw(OilTank);
    // Implémentation des paramètres de la barre de carburant
    sf::RectangleShape OilBar(sf::Vector2f(width * OilRatio, height));
    OilBar.setPosition(posX_oil, posY_oil);
    // utilisation de la couleur déterminée
    OilBar.setFillColor(barColor);
    window.draw(OilBar);
}

// Fonction permettant l'affichage du "GameOver"
void AffichageDonnees::gameOverNotice(sf::RenderWindow& window){
    centralText.setFont(font);                      // Ajout de la police
    centralText.setString("Game over");             // Chaîne de caractères du texte
    centralText.setPosition(416.f, 360.f);          // Position du texte
    centralText.setCharacterSize(24);               // Taille de la police
    centralText.setFillColor(sf::Color::White);     // Couleur du texte
    window.draw(centralText);  
}

// Fonction affichant et calculant le temps de réaction pour les feux de départ
void AffichageDonnees::ReactedTime(sf::RenderWindow& window, float first_time, float second_time){
    // Temps écoulé entre le départ autorisé et le départ réel
    float elapsedTimeReact = second_time - first_time;      
    // Affichage du logo du Feu de départ pour le temps de réaction
    window.draw(FeuSprite);

    // Ecriture et stockage du temps de réaction
    std::ostringstream TempsReact;
    TempsReact << std::fixed << std::setprecision(3) << elapsedTimeReact << " s";
    std::string TempsStr = TempsReact.str();
    tempsReaction.setString(TempsStr);
}