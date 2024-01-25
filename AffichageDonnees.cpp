#include "AffichageDonnees.hh"

AffichageDonnees::AffichageDonnees(Voiture& v) : initialMapPositionY(0.f), distanceParcourue(0.f), voitureTrack(v) {
    if (!font.loadFromFile("fonts/chrono_pixel/nuvel.ttf")) {
        std::cerr << "Erreur pour la police" << std::endl;
    }

    chronoText = parametrage_chrono(chronoText);
    distanceText = parametrage_distance(distanceText);
    vitesseText = parametrage_vitesse(vitesseText);
    vitesseMaxReachedText = parametrage_vitesseMax(vitesseMaxReachedText);
    tempsReaction = parametrage_reacted_time(tempsReaction);

    // Logo vitesse
    CompteurSpeed = logo_speed(CompteurSpeed);
    // Oil tank texture
    OilTank = logo_tank(OilTank);

    if(!HpTexture.loadFromFile("assets/Hp_logo.png", sf::IntRect(0, 0, 64*v.getMaxHp(), 64))){
        std::cerr << "Erreur lors du chargement de l'image de la pompe" << std::endl;
        EXIT_FAILURE;
    }
    // Points de vie
    HpIcon.setPosition(hpPosX, hpPosY);
    HpTexture.setRepeated(true);
    HpIcon.setTexture(HpTexture);

    // Feu de départ
    FeuSprite = logo_feu_dep(FeuSprite);
}

sf::Text AffichageDonnees::parametrage_chrono(sf::Text textFont) {
    textFont.setFont(font);
    textFont.setCharacterSize(24);
    textFont.setFillColor(sf::Color::Black);
    textFont.setPosition(32.f, 10.f);
    textFont.setScale(2.f, 2.f);

    return textFont;
}

sf::Text AffichageDonnees::parametrage_distance(sf::Text textFont) {
    textFont.setFont(font);
    textFont.setCharacterSize(18);
    textFont.setFillColor(sf::Color::White);
    textFont.setPosition(416.f, 725.f);
    textFont.setScale(2.f, 2.f);

    return textFont;
}


sf::Text AffichageDonnees::parametrage_vitesse(sf::Text textFont) {
    textFont.setFont(font);
    textFont.setCharacterSize(24);
    textFont.setFillColor(sf::Color::Black);
    textFont.setPosition(32.f, 120.f);
    textFont.setScale(1.5f, 1.5f);

    return textFont;
}

sf::Text AffichageDonnees::parametrage_vitesseMax(sf::Text textFont) {
    textFont.setFont(font);
    textFont.setCharacterSize(18);
    textFont.setFillColor(sf::Color::Black);
    textFont.setPosition(800.f,250.f);
    textFont.setScale(1.5f,1.5f);
    
    return textFont;
}

sf::Text AffichageDonnees::parametrage_reacted_time(sf::Text textFont) {
    textFont.setFont(font);
    textFont.setCharacterSize(18);
    textFont.setFillColor(sf::Color::Black);
    textFont.setPosition(20.f,230.f);
    textFont.setScale(1.5f,1.5f);

    return textFont;
}

sf::Sprite AffichageDonnees::logo_speed(sf::Sprite SpeedSprite) {
    if(!SpeedPicture.loadFromFile("assets/max_speed.png")){
        std::cerr << "Erreur lors du chargement de l'image du compteur" << std::endl;
        EXIT_FAILURE;
    }
    SpeedSprite.setTexture(SpeedPicture);
    SpeedSprite.setPosition(logoPosX,logoPosY);
    SpeedSprite.setScale(1.25f,1.25f);

    return SpeedSprite;
}

sf::Sprite AffichageDonnees::logo_tank(sf::Sprite OilSprite) {
    if(!TankPicture.loadFromFile("assets/pompe_car.png")){
        std::cerr << "Erreur lors du chargement de l'image de la pompe" << std::endl;
        EXIT_FAILURE;
    }
    OilSprite.setTexture(TankPicture);
    OilSprite.setPosition(imagPosX,imagPosY);

    return OilSprite;
}

sf::Sprite AffichageDonnees::logo_feu_dep(sf::Sprite FeuDepartSprite) {
    if(!FeuTexture.loadFromFile("assets/f1_feu_dep_tmp_rec.png")){
        std::cerr << "Erreur lors du chargement de l'image du feu" << std::endl;
        EXIT_FAILURE;
    }
    FeuDepartSprite.setTexture(FeuTexture);
    FeuDepartSprite.setPosition(feuPosX,feuPosY);
    FeuDepartSprite.setScale(0.35f,0.35f);

    return FeuDepartSprite;
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
    target.draw(tempsReaction);

    // pts de vie
    HpIcon.setTextureRect(sf::IntRect(0,0,64*voitureTrack.getHp(), 64));
    target.draw(HpIcon);
}

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

    sf::RectangleShape speedBar(sf::Vector2f(width * speedRatio, height));
    speedBar.setPosition(posX_vit, posY_vit);
    // utilisation de la couleur déterminée
    speedBar.setFillColor(barColor);
    window.draw(speedBar);
}

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

    // -----
    window.draw(OilTank);
    sf::RectangleShape OilBar(sf::Vector2f(width * OilRatio, height));
    OilBar.setPosition(posX_oil, posY_oil);
    // utilisation de la couleur déterminée
    OilBar.setFillColor(barColor);
    window.draw(OilBar);
}

void AffichageDonnees::gameOverNotice(sf::RenderWindow& window){
    centralText.setFont(font);
    centralText.setString("Game over");
    centralText.setPosition(416.f, 360.f);
    centralText.setCharacterSize(24);
    centralText.setFillColor(sf::Color::White);
    window.draw(centralText);  
}

void AffichageDonnees::ReactedTime(sf::RenderWindow& window, float first_time, float second_time){
    float elapsedTimeReact = second_time - first_time;

    window.draw(FeuSprite);

    std::ostringstream TempsReact;
    TempsReact << std::fixed << std::setprecision(3) << elapsedTimeReact << " s";
    std::string TempsStr = TempsReact.str();
    tempsReaction.setString(TempsStr);
}