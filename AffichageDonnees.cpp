#include "AffichageDonnees.hh"

AffichageDonnees::AffichageDonnees() : initialMapPositionY(0.f), distanceParcourue(0.f) {
    if (!font.loadFromFile("fonts/chrono_pixel/nuvel.ttf")) {
        std::cerr << "Erreur pour la police" << std::endl;
    }

    chronoText.setFont(font);
    chronoText.setCharacterSize(24);
    chronoText.setFillColor(sf::Color::Black);
    chronoText.setPosition(32.f, 10.f);
    chronoText.setScale(2.f, 2.f);

    distanceText.setFont(font);
    distanceText.setCharacterSize(18);
    distanceText.setFillColor(sf::Color::White);
    distanceText.setPosition(416.f, 725.f);
    distanceText.setScale(2.f, 2.f);

    vitesseText.setFont(font);
    vitesseText.setCharacterSize(24);
    vitesseText.setFillColor(sf::Color::Black);
    vitesseText.setPosition(32.f, 120.f);
    vitesseText.setScale(1.5f, 1.5f);

    vitesseMaxReachedText.setFont(font);
    vitesseMaxReachedText.setCharacterSize(18);
    vitesseMaxReachedText.setFillColor(sf::Color::Black);
    vitesseMaxReachedText.setPosition(800.f,250.f);
    vitesseMaxReachedText.setScale(1.5f,1.5f);

    if(!SpeedPicture.loadFromFile("assets/max_speed.png")){
        std::cerr << "Erreur lors du chargement de l'image du compteur" << std::endl;
        EXIT_FAILURE;
    }
    // logo vitesse
    CompteurSpeed.setTexture(SpeedPicture);
    CompteurSpeed.setPosition(logoPosX,logoPosY);
    CompteurSpeed.setScale(1.25f,1.25f);

    // initialisation des textures pour l'affichage
    if(!TankPicture.loadFromFile("assets/pompe_car.png")){
        std::cerr << "Erreur lors du chargement de l'image de la pompe" << std::endl;
        EXIT_FAILURE;
    }
    // tank
    OilTank.setTexture(TankPicture);
    OilTank.setPosition(imagPosX,imagPosY);
}

void AffichageDonnees::startChrono() {
    startTime.restart();
}

void AffichageDonnees::updateChronoDistance(float mapPosY) {
    static sf::Clock clock;
    static float lastMapPosY = mapPosY;

    if (mapPosY > lastMapPosY) {
        distanceParcourue += mapPosY - lastMapPosY;
        lastMapPosY = mapPosY;
    }
    else if (mapPosY < lastMapPosY) {
        distanceParcourue += lastMapPosY - mapPosY;
        lastMapPosY = mapPosY;
    }

    float distanceParcourueMetres = distanceParcourue / (64.f / 1.5f);

    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << distanceParcourueMetres;
    std::string distanceStr = stream.str();
    distanceText.setString(distanceStr + " m");

    sf::Time elapsedTime = clock.getElapsedTime();

    int totalSeconds = static_cast<int>(elapsedTime.asMilliseconds() / 1000);
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    int milliseconds = static_cast<int>(elapsedTime.asMilliseconds() % 1000);

    std::string minutesStr = (minutes < 10) ? "0" + std::to_string(minutes) : std::to_string(minutes);
    std::string secondsStr = (seconds < 10) ? "0" + std::to_string(seconds) : std::to_string(seconds);

    std::string timeStr = minutesStr + " : " +
                        secondsStr + " : " +
                        std::to_string(milliseconds);
    chronoText.setString(timeStr);

    updateVitesse(distanceParcourueMetres);
}

void AffichageDonnees::updateVitesse(float distance) {
    static sf::Clock speedUpdateClock;
    static float lastDistance = distance;
    static float vitesseMaxReached = 0.0;

    sf::Time elapsedTime = speedUpdateClock.getElapsedTime();

    if (elapsedTime.asMilliseconds() >= 25) {

        float distanceDiff = distance - lastDistance;

        float vitesseMS = distanceDiff / elapsedTime.asSeconds();
        float vitesse_KmH = vitesseMS * 3.6f;
        lastDistance = distance;
        speedUpdateClock.restart();

        if (vitesse_KmH > 750)
            vitesse_KmH = 0.0;

        std::ostringstream stream_speed;
        stream_speed << std::fixed << std::setprecision(1) << vitesse_KmH;
        std::string vitesseStr = stream_speed.str();
        vitesseText.setString(vitesseStr + " Km/h");

        if(vitesse_KmH > vitesseMaxReached)
            vitesseMaxReached = vitesse_KmH;
        std::ostringstream max_speed_reach;
        max_speed_reach << std::fixed << std::setprecision(1) << vitesseMaxReached;
        std::string vitesseMaxStr = max_speed_reach.str();
        vitesseMaxReachedText.setString(vitesseMaxStr + " Km/h");
    }
}


void AffichageDonnees::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    target.draw(chronoText);
    target.draw(distanceText);
    target.draw(vitesseText);
    target.draw(vitesseMaxReachedText);
}

void AffichageDonnees::drawSpeedometer(sf::RenderWindow& window, float currentSpeed, float maxSpeed) {
    // calcule de la proportion actuelle de la vitesse par rapport à la vitesse maximale
    float speedRatio = currentSpeed / maxSpeed;
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

    sf::RectangleShape speedBar(sf::Vector2f(width * speedRatio, height));
    speedBar.setPosition(posX_vit, posY_vit);
    // utilisation de la couleur déterminée
    speedBar.setFillColor(barColor);
    window.draw(speedBar);
}

void AffichageDonnees::drawOilLevelBar(sf::RenderWindow& window, float currentOil, float maxOil) {
    // calcule de la proportion actuelle du carburant actuel par rapport au niveau de carburant maximal
    float OilRatio = currentOil / maxOil;
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

    sf::RectangleShape OilBar(sf::Vector2f(width * OilRatio, height));
    OilBar.setPosition(posX_oil, posY_oil);
    // utilisation de la couleur déterminée
    OilBar.setFillColor(barColor);
    window.draw(OilBar);
}

void AffichageDonnees::drawHpDot(sf::RenderWindow& window, float numberHp, sf::Sprite& HpIconImage) {
    HpIconImage.setPosition(iconPosX, iconPosY);

    // Boucle pour dessiner le nombre de points de vie avec l'icône spécifiée et le nombre de points de vie adéquat
    for (int i = 0; i < numberHp; ++i) {
        if (i < 3)
            HpIconImage.setPosition(iconPosX - (i + 1) * (HpIconImage.getGlobalBounds().width + 10.0f), iconPosY);
        else 
            HpIconImage.setPosition(iconPosX_2nd - (i - 3 + 1) * ( HpIconImage.getGlobalBounds().width + 10.0f), iconPosY_2nd);
        window.draw(HpIconImage);
    }
}