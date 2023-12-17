#include <SFML/Graphics.hpp>

class Voiture : public sf::Drawable, public sf::Transformable {
private:
    sf::Sprite sprite; // Déclaration du sprite dans la classe Voiture
    float _speed;
    float _maxSpeed;

public:
    Voiture(float x, float y, float speed, float maxSpeed, const sf::Texture& texture);

    // Implémentez ces fonctions pour éviter que Voiture soit considérée comme une classe abstraite
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void move(float offsetX, float offsetY);

    float getSpeed() const;
    float getX() const;
    float getY() const;
    float getMaxSpeed() const;

    void startSpeedUp();
    void SpeedUp();
};