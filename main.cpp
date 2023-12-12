#include <SFML/Graphics.hpp>
#include "tilemap.hh"

int main()
{
    // on crée la fenêtre
    sf::RenderWindow window(sf::VideoMode(720, 720), "Tilemap");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);

    // on définit le niveau à l'aide de numéro de tuiles
    int level[] =
    {
        2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
        2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
        2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
        2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
        2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
        2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
        2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
        2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
        2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
        2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
        2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
        2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
        2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
        2,2,2,2,1,3,0,3,0,0,1,2,2,2,2,
        2,2,2,2,1,0,3,0,3,0,1,2,2,2,2,
    };

    // on crée la tilemap avec le niveau précédemment défini
    // pour simuler une tilemap infini, on crée 2 tilemap
    TileMap map;
    TileMap map2;
    sf::View view = window.getView();
    map.setPosition(-120.f, 0.f);
    map2.setPosition(-120.f, -960.f);

    if (!map.load("tileset.png", sf::Vector2u(64, 64), level, 15, 15))
        return -1;
    
    if (!map2.load("tileset.png", sf::Vector2u(64, 64), level, 15, 15))
        return -1;

    // sprite
    sf::Sprite voiture;
    sf::Texture textureVoiture;
    if (!textureVoiture.loadFromFile("assets/voiture.png", sf::IntRect(0, 0, 64, 64)))
        return -1;
    voiture.setTexture(textureVoiture);
    voiture.setPosition(sf::Vector2f(320.f, 600.f));
    

    // on fait tourner la boucle principale
    while (window.isOpen())
    {
        // on gère les évènements
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        
        map.move(0.f,1.f);
        map2.move(0.f,1.f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            voiture.move(-3.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            voiture.move(3.f, 0.f);

        if  (map.getPosition().y > 480.f)
            map.setPosition(-120.f, 0.f);
        if  (map2.getPosition().y > 480.f)
            map2.setPosition(-120.f, 0.f);


        // on dessine le niveau
        window.clear();
        window.setView(view);
        window.draw(map);
        window.draw(map2);
        window.draw(voiture);
        window.display();
    }

    return 0;
}