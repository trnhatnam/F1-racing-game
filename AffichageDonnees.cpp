#include "AffichageDonnees.hh"

AffichageDonnees::AffichageDonnees() : initialMapPositionY(0.f), distanceParcourue(0.f) {
    if (!this->font.loadFromFile("fonts/chrono_pixel/nuvel.ttf")) {
        std::cerr << "Erreur pour la police" << std::endl;
    }

    this->chronoText.setFont(this->font);
    this->chronoText.setCharacterSize(24);
    this->chronoText.setFillColor(sf::Color::Black);
    this->chronoText.setPosition(32.f, 10.f);
    this->chronoText.setScale(2.f, 2.f);

    this->distanceText.setFont(this->font);
    this->distanceText.setCharacterSize(18);
    this->distanceText.setFillColor(sf::Color::White);
    this->distanceText.setPosition(416.f, 700.f);
    this->distanceText.setScale(2.f, 2.f);

    this->vitesseText.setFont(this->font);
    this->vitesseText.setCharacterSize(24);
    this->vitesseText.setFillColor(sf::Color::Black);
    this->vitesseText.setPosition(32.f, 150.f);
    this->vitesseText.setScale(1.5f, 1.5f);
}

void AffichageDonnees::startChrono() {
    startTime.restart();
}

void AffichageDonnees::updateChronoDistance(float mapPosY, float vitesse) {
    if (mapPosY > this->initialMapPositionY) {
        this->distanceParcourue += mapPosY - this->initialMapPositionY;
        this->initialMapPositionY = mapPosY;
    }
    else if (mapPosY < this->initialMapPositionY) {
        this->distanceParcourue += this->initialMapPositionY - mapPosY;
        this->initialMapPositionY = mapPosY;
    }

    float distanceParcourueMetres = this->distanceParcourue / (64.f / 1.5f);

    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << distanceParcourueMetres;
    std::string distanceStr = stream.str();
    this->distanceText.setString(distanceStr + " m");

    this->updateVitesse(distanceParcourueMetres);
}

void AffichageDonnees::updateVitesse(float distance) {
    sf::Time elapsedTime = this->startTime.getElapsedTime();

    int totalSeconds = static_cast<int>(elapsedTime.asMilliseconds() / 1000);
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    int milliseconds = static_cast<int>(elapsedTime.asMilliseconds() % 1000);

    std::string minutesStr = (minutes < 10) ? "0" + std::to_string(minutes) : std::to_string(minutes);
    std::string secondsStr = (seconds < 10) ? "0" + std::to_string(seconds) : std::to_string(seconds);

    std::string timeStr = minutesStr + " : " +
                        secondsStr + " : " +
                        std::to_string(milliseconds);
    this->chronoText.setString(timeStr);

    float tempsSeconde = elapsedTime.asSeconds();
    float vitesseMS = distance / tempsSeconde;
    float vitesse_KmH = vitesseMS * 3.6f;

    std::ostringstream stream_speed;
    stream_speed << std::fixed << std::setprecision(2) << vitesse_KmH;
    std::string vitesseStr = stream_speed.str();
    this->vitesseText.setString(vitesseStr + " Km/h");
}


void AffichageDonnees::draw(sf::RenderWindow& window) {
    window.draw(this->chronoText);
    window.draw(this->distanceText);
    window.draw(this->vitesseText);
}

void AffichageDonnees::drawSpeedometer(sf::RenderWindow& window, float currentSpeed, float maxSpeed) {
    // Positionnement et taille de la jauge
    float width = 200.f; // Largeur de la jauge
    float height = 20.f; // Hauteur de la jauge
    float posX = 20.f;   // Position X de la jauge
    float posY = 200.f;  // Position Y de la jauge

    // calcule de la proportion actuelle de la vitesse par rapport à la vitesse maximale
    float speedRatio = currentSpeed / maxSpeed;
    if (speedRatio > 1.0f) speedRatio = 1.0f; // limitation de la jauge avec la valeur à 1 si la vitesse dépasse maxSpeed

    // on dessine la forme de la jauge (background)
    sf::RectangleShape background(sf::Vector2f(width, height));
    background.setPosition(posX, posY);
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

    sf::RectangleShape speedBar(sf::Vector2f(width * speedRatio, height));
    speedBar.setPosition(posX, posY);
    // utilisation de la couleur déterminée
    speedBar.setFillColor(barColor);
    window.draw(speedBar);
}

void AffichageDonnees::drawOilLevelBar(sf::RenderWindow& window, float actualOil, float maxOil) {
    // Positionnement et taille de la jauge
    float width = 200.f; // Largeur de la jauge
    float height = 20.f; // Hauteur de la jauge
    float posX = 20.f;   // Position X de la jauge
    float posY = 700.f;  // Position Y de la jauge

    // calcule de la proportion actuelle du carburant actuel par rapport au niveau de carburant maximal
    float OilRatio = actualOil / maxOil;
    if (OilRatio < 0.0f) OilRatio = 0.0f; // limitation de la jauge avec la valeur à 0 si le carburant est négatif

    // on dessine la forme de la jauge (background)
    sf::RectangleShape background(sf::Vector2f(width, height));
    background.setPosition(posX, posY);
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

    sf::Texture TankPicture;
    if(!TankPicture.loadFromFile("assets/pompe_car.png")){
        std::cerr << "Erreur lors du chargement de l'image de la pompe" << std::endl;
        EXIT_FAILURE;
    }
    sf::Sprite OilTank(TankPicture);
    float imagPosX = 20.f;
    float imagPosY = 575.f;
    OilTank.setPosition(imagPosX,imagPosY);
    window.draw(OilTank);

    sf::RectangleShape OilBar(sf::Vector2f(width * OilRatio, height));
    OilBar.setPosition(posX, posY);
    // utilisation de la couleur déterminée
    OilBar.setFillColor(barColor);
    window.draw(OilBar);
}
