#include <SFML/Graphics.hpp>

class Voiture {
    private:
        float _x,_y;
        float _speed;
        float _maxSpeed;
    public:
        Voiture(float x,float y, float speed, float maxSpeed);

        float getX() const;
        float getY() const;
        float getSpeed() const;
        float getMaxSpeed() const;

        void move(float sideStep);
        void startSpeedUp();
        void SpeedUp();
};