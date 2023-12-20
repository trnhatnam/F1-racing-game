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
    distanceText.setPosition(416.f, 700.f);
    distanceText.setScale(2.f, 2.f);

    vitesseText.setFont(font);
    vitesseText.setCharacterSize(24);
    vitesseText.setFillColor(sf::Color::Black);
    vitesseText.setPosition(32.f, 150.f);
    vitesseText.setScale(1.5f, 1.5f);
}

void AffichageDonnees::startChrono() {
    startTime = std::chrono::steady_clock::now();
}

void AffichageDonnees::updateChronoDistance(float mapPosY, float vitesse) {
    if (mapPosY > initialMapPositionY) {
        distanceParcourue += mapPosY - initialMapPositionY;
        initialMapPositionY = mapPosY;
    }
    else if (mapPosY < initialMapPositionY) {
        distanceParcourue += initialMapPositionY - mapPosY;
        initialMapPositionY = mapPosY;
    }

    float distanceParcourueMetres = distanceParcourue / (64.f / 1.5f);

    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << distanceParcourueMetres;
    std::string distanceStr = stream.str();
    distanceText.setString(distanceStr + " m");

    updateVitesse(distanceParcourueMetres);
}

void AffichageDonnees::updateVitesse(float distance) {
    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    std::chrono::milliseconds elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime);

    int totalSeconds = static_cast<int>(elapsedMs.count() / 1000);
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    int milliseconds = static_cast<int>(elapsedMs.count() % 1000);

    std::string minutesStr = (minutes < 10) ? "0" + std::to_string(minutes) : std::to_string(minutes);
    std::string secondsStr = (seconds < 10) ? "0" + std::to_string(seconds) : std::to_string(seconds);

    std::string timeStr = minutesStr + " : " +
                        secondsStr + " : " +
                        std::to_string(milliseconds);
    chronoText.setString(timeStr);

    float tempsSeconde = elapsedMs.count() / 1000.f;
    float vitesseMS = distance / tempsSeconde;
    float vitesse_KmH = vitesseMS * 3.6f;

    std::ostringstream stream_speed;
    stream_speed << std::fixed << std::setprecision(2) << vitesse_KmH;
    std::string vitesseStr = stream_speed.str();
    vitesseText.setString(vitesseStr + " Km/h");
}

void AffichageDonnees::draw(sf::RenderWindow& window) {
    window.draw(chronoText);
    window.draw(distanceText);
    window.draw(vitesseText);
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
